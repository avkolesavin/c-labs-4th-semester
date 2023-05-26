#include <stdint.h>
#include "table.h"
#include "table-utils.h"

uint32_t hash(key_t key1, key_t key2, uint32_t tableSize)
{
    return ((key1 << 16) ^ key2) % tableSize;
}
