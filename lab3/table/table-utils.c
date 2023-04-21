#include "table.h"
#include "table-utils.h"

int hash(int key1, int key2, int tableSize)
{
    return ((key1 << 16) ^ key2) % tableSize;
}
