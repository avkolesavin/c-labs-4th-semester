#include <stdlib.h>
#include <stdio.h>

#include "../table.h"
#include "../table-utils.h"
#include "memory-table.h"

void printMemoryTable(Table *table)
{
    if (table->size == 0 || table->items == NULL)
    {
        printf("Table is empty\n");
        return;
    }

    printf("\nSize of table: %d\n\n", table->size);
    printf(" Index | Key1     | Key2     | Value      \n");
    printf("-------|----------|----------|-------------\n");

    for (int i = 0; i < table->size; i++)
    {
        Item item = table->items[i];

        printf(" %-5d | %-8d | %-8d | %-10s\n", i, item.key1, item.key2, table->stringifyData(item.data));
    }
}

TABLE_ERRORS memoryTableInsertItem(Table *table, key_t key1, key_t key2, void *data)
{
    int index = hash(key1, key2, table->size);
    int startIndex = index;

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

    table->items[index].key1 = key1;
    table->items[index].key2 = key2;
    table->items[index].data = data;

    return OK;
}

TABLE_ERRORS memoryTableUpdateItem(Table *table, key_t key1, key_t key2, void *data)
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

TABLE_ERRORS memoryTableDeleteItem(Table *table, key_t key1, key_t key2)
{
    int index = hash(key1, key2, table->size);
    int startIndex = index;

    while (
        table->items[index].key1 != 0 &&
        table->items[index].key2 != 0)
    {
        if (table->items[index].key1 == key1 && table->items[index].key2 == key2)
        {
            table->items[index].data = NULL;

            return OK;
        }

        index = (index + table->step) % table->size;

        if (index == startIndex)
            return NOT_FOUND;
    }

    return DELETE_ERROR;
}

TABLE_ERRORS memoryTableFindItem(Table *table, key_t key1, key_t key2, void **data)
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

Table *newMemoryTable(int tableSize, int step, char *(*stringifyData)(void *))
{
    Table *table = malloc(sizeof(Table));
    Item *items = calloc(table->size, sizeof(Item));

    table->size = tableSize;
    table->items = items;
    table->step = step;

    table->stringifyData = stringifyData;
    table->print = printMemoryTable;
    table->insert = memoryTableInsertItem;
    table->update = memoryTableUpdateItem;
    table->delete = memoryTableDeleteItem;
    table->find = memoryTableFindItem;

    return table;
}
