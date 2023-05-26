#include <stdint.h>
#include "../table.h"

#ifndef FILE_TABLE_H
#define FILE_TABLE_H

typedef struct FileTable
{
    Table table;
    char *fileName;
} FileTable;

Table *
newFileTable(u_int32_t tableSize, int step, char *fileName, char *(*stringifyData)(void *));

#endif
