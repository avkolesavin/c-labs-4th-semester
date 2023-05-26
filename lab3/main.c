#include <stdio.h>
#include <stdlib.h>

#include "./table/table.h"
#include "./table/memory-table/memory-table.h"
#include "./table/file-table/file-table.h"

char *printData(void *data)
{
    if (data == NULL)
        return "(NULL)";

    return (char *)data;
}

int main()
{
    Table *memTable = newMemoryTable(10, 1, printData);
    Table *fileTable = newFileTable(10, 1, "./table-file", printData);

    if (fileTable == NULL)
        return 1;

    // printf("size: %u, fullness; %u, step: %d\n", fileTable->size, fileTable->fullness, fileTable->step);
    fileTable->print(fileTable);
    // fileTable->insert(fileTable, 2, 2, "Hello Table\0\0");
    fileTable->delete (fileTable, 2, 2);
    // fileTable->insert(fileTable, 6, 6, "Qwerty");
    // fileTable->insert(fileTable, 9, 9, "Some data");
    // fileTable->update(fileTable, 9, 9, "Test data");
    fileTable->print(fileTable);

    // memTable->insert(memTable, 1, 2, "Hello Table");
    // memTable->insert(memTable, 1, 4, "123");
    // memTable->insert(memTable, 1, 6, "Qwerty");
    // memTable->insert(memTable, 1, 16, "Some beautiful data");
    // memTable->insert(memTable, 1, 36, "1q2w3e4r");

    // memTable->print(memTable);

    // memTable->delete (memTable, 1, 16);
    // memTable->update(memTable, 1, 16, "Bla bla");

    // memTable->print(memTable);

    // memTable->find(memTable, 1, 36, (void **)&data);

    // printf("%s\n", data);
    printf("The end!\n");

    return 0;
}
