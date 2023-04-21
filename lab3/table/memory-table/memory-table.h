#include "../table.h"

#ifndef MEMORY_TABLE_H
#define MEMORY_TABLE_H

Table *newMemoryTable(int tableSize, int step, char *(*stringifyData)(void *));

#endif
