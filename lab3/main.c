#include <stdio.h>

#include "./table/table.h"
#include "./table/memory-table/memory-table.h"
#include "./table/file-table/file-table.h"

typedef char *data_t;

data_t printData(void *data)
{
    return (data_t)data;
}

int main()
{
    Table *memTable = newMemoryTable(10, 1, printData);
    // Table *fileTable = newFileTable(10, 1, "table");
    data_t data = NULL;

    memTable->insert(memTable, 1, 2, "Hello Table");
    memTable->insert(memTable, 1, 4, "123");
    memTable->insert(memTable, 1, 6, "Qwerty");
    memTable->insert(memTable, 1, 16, "Some beautiful data");
    memTable->insert(memTable, 1, 36, "1q2w3e4r");

    memTable->print(memTable);

    memTable->delete (memTable, 1, 16);
    memTable->update(memTable, 1, 16, "Bla bla");

    memTable->print(memTable);

    memTable->find(memTable, 1, 36, (void **)&data);

    printf("%s\n", data);
    printf("The end!\n");

    return 0;
}
