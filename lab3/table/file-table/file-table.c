#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../table.h"
#include "../table-utils.h"
#include "file-table.h"

#define ITEMS_OFFSET sizeof(uint32_t) + sizeof(int)
#define ITEM_SIZE (sizeof(key_t) * 2 + sizeof(size_t) + sizeof(long))

void updateItemInFile(FileTable *table, int index, key_t key1, key_t key2, void *data)
{
    FILE *file = fopen(table->fileName, "r+b");

    fseek(file, ITEMS_OFFSET + index * ITEM_SIZE, SEEK_SET);

    fwrite(&key1, sizeof(key_t), 1, file);
    fwrite(&key2, sizeof(key_t), 1, file);

    // Проверить можно ли записать данные в то же место.
    // Прочитать и сравнить размер с тем, что нужно записать
    size_t existDataSize = 0;
    fread(&existDataSize, sizeof(size_t), 1, file);

    fseek(file, -sizeof(size_t), SEEK_CUR);

    // Пока data строка
    size_t newDataSize = data == NULL ? 0 : strlen((char *)data);
    fwrite(&newDataSize, sizeof(size_t), 1, file);

    long dataFieldOffset = ftell(file);

    if (newDataSize == 0)
    {
        long newDataOffset = 0;
        fwrite(&newDataOffset, sizeof(long), 1, file);
    }
    else if (newDataSize > existDataSize)
    {
        // стереть старые данные ?
        // записать в конец файла

        fseek(file, 0, SEEK_END);

        long dataOffset = ftell(file);

        fputs((char *)data, file);
        fseek(file, dataFieldOffset, SEEK_SET);
        fwrite(&dataOffset, sizeof(long), 1, file);
    }
    else
    {
        // записать новые данные в то же место
        long dataOffset = 0;
        fread(&dataOffset, sizeof(long), 1, file);
        fseek(file, dataOffset, SEEK_SET);
        fputs((char *)data, file);
    }

    fclose(file);
}

void printFileTable(Table *table)
{
    printf("Print file table\n");

    if (table->size == 0 || table->items == NULL)
    {
        printf("Table is empty :(\n");
        return;
    }

    printf("\nTable size: %d\n\n", table->size);
    printf(" Index | Key1     | Key2     | Value      \n");
    printf("-------|----------|----------|-------------\n");

    for (int i = 0; i < table->size; i++)
    {
        Item item = table->items[i];

        printf(" %-5d | %-8d | %-8d | %-10s\n", i, item.key1, item.key2, table->stringifyData(item.data));
    }
}

TABLE_ERRORS fileTableInsertItem(Table *table, key_t key1, key_t key2, void *data)
{
    u_int32_t index = hash(key1, key2, table->size);
    u_int32_t startIndex = index;

    while (
        table->items[index].key1 != 0 &&
        table->items[index].key2 != 0)
    {
        if (table->items[index].data == NULL)
            break;

        if (table->items[index].key1 == key1 && table->items[index].key2 == key2)
            return INSERT_ERROR;

        index = (index + table->step) % table->size;

        if (startIndex == index)
            return TABLE_FULL;
    }

    updateItemInFile((FileTable *)table, index, key1, key2, data);

    table->items[index].key1 = key1;
    table->items[index].key2 = key2;
    table->items[index].data = data;

    return OK;
}

TABLE_ERRORS fileTableUpdateItem(Table *table, key_t key1, key_t key2, void *data)
{
    int index = hash(key1, key2, table->size);
    int startIndex = index;

    while (
        table->items[index].key1 != 0 &&
        table->items[index].key2 != 0)
    {
        if (table->items[index].key1 == key1 && table->items[index].key2 == key2)
        {
            if (table->items[index].data == NULL)
                return UPDATE_ERROR;

            updateItemInFile((FileTable *)table, index, key1, key2, data);

            // Не освобождает память перезаписанных данных, алярм!
            // Подумать в каком месте это контролировать
            table->items[index].data = data;

            return OK;
        }

        index = (index + table->step) % table->size;

        if (index == startIndex)
            return NOT_FOUND;
    }

    return UPDATE_ERROR;
}

TABLE_ERRORS fileTableDeleteItem(Table *table, key_t key1, key_t key2)
{
    int index = hash(key1, key2, table->size);
    int startIndex = index;

    while (
        table->items[index].key1 != 0 &&
        table->items[index].key2 != 0)
    {
        if (table->items[index].key1 == key1 && table->items[index].key2 == key2)
        {
            updateItemInFile((FileTable *)table, index, key1, key2, NULL);

            table->items[index].data = NULL;

            return OK;
        }

        index = (index + table->step) % table->size;

        if (index == startIndex)
            return NOT_FOUND;
    }

    return DELETE_ERROR;
}

TABLE_ERRORS fileTableFindItem(Table *table, key_t key1, key_t key2, void **data)
{
    int index = hash(key1, key2, table->size);
    int startIndex = index;

    while (table->items[index].key1 != 0 && table->items[index].key2 != 0)
    {
        if (table->items[index].key1 == key1 && table->items[index].key2 == key2)
            *data = table->items[index].data;

        index = (index + table->step) % table->size;

        if (index == startIndex)
            return NOT_FOUND;
    }

    return NOT_FOUND;
}

Table *newFileTable(u_int32_t tableSize, int step, char *fileName, char *(*stringifyData)(void *))
{
    FILE *file = fopen(fileName, "r+b");

    FileTable *fileTable = malloc(sizeof(FileTable));

    printf("[DEBUG] fileTable ptr: %p\n", fileTable);

    Table *table = (Table *)fileTable;

    fileTable->fileName = fileName;

    if (file == NULL)
    {
        printf("[DEBUG] File '%s' doesn't exists\n", fileName);
        fclose(file);

        file = fopen(fileName, "w+b");

        if (file == NULL)
        {
            printf("Error opening file '%s'\n", fileName);
            free(fileTable);

            return NULL;
        }

        table->size = tableSize;
        // table->fullness = 0;
        table->step = step;
        table->items = NULL;

        fwrite(&table->size, sizeof(uint32_t), 1, file);
        // fwrite(&table->fullness, sizeof(u_int32_t), 1, file);
        fwrite(&table->step, sizeof(int), 1, file);

        if (tableSize > 0)
        {
            Item *items = calloc(sizeof(Item), tableSize);

            for (int i = 0; i < tableSize; i++)
            {
                int itemSize = ITEM_SIZE;

                for (int j = 0; j < itemSize; j++)
                    fputc(0, file);
            }

            table->items = items;
        }
    }
    else
    {
        printf("[DEBUG] File '%s' exists\n", fileName);

        u_int32_t readSize = 0;
        fread(&readSize, sizeof(u_int32_t), 1, file);

        if (readSize != tableSize)
        {
            printf("Error: table size from file (%u) differ from argument (%u)\n", readSize, tableSize);
            free(fileTable);

            return NULL;
        }

        // u_int32_t readFullness = 0;
        // fread(&readFullness, sizeof(u_int32_t), 1, file);

        int readStep = 0;
        fread(&readStep, sizeof(int), 1, file);

        if (readStep != step)
        {
            printf("Error: table step from file (%d) differ from argument (%d)\n", readStep, step);
            free(fileTable);

            return NULL;
        }

        table->size = readSize;
        // table->fullness = readFullness;
        table->step = readStep;
        printf("[DEBUG] Item size: %lu\n", sizeof(Item));
        printf("[DEBUG] Table size: %d\n", tableSize);

        Item *readItems = malloc(sizeof(Item) * tableSize);

        for (int i = 0; i < tableSize; i++)
        {
            fread(&readItems[i].key1, sizeof(key_t), 1, file);
            fread(&readItems[i].key2, sizeof(key_t), 1, file);

            size_t dataSize = 0;
            fread(&dataSize, sizeof(size_t), 1, file);

            // printf("[DEBUG] Data size: %lu\n", dataSize);

            if (dataSize >= 1 << 10)
            {
                printf("[DEBUG] Error: data size is too big\n");
                return NULL;
            }

            if (dataSize > 0)
            {
                long dataFieldOffset = ftell(file);

                long dataOffset = 0;
                fread(&dataOffset, sizeof(long), 1, file);

                fseek(file, dataOffset, SEEK_SET);

                char *dataString = malloc(dataSize);
                fgets(dataString, dataSize + 1, file);
                readItems[i].data = dataString;

                fseek(file, dataFieldOffset + sizeof(long), SEEK_SET);
            }
            else
            {
                fseek(file, sizeof(long), SEEK_CUR);
            }
        }

        table->items = readItems;
    }

    table->print = printFileTable;
    table->insert = fileTableInsertItem;
    table->update = fileTableUpdateItem;
    table->delete = fileTableDeleteItem;
    table->find = fileTableFindItem;
    table->stringifyData = stringifyData;

    fclose(file);

    return table;
}
