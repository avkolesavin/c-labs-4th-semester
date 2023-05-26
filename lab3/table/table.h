#include <stdint.h>

#ifndef TABLE_H
#define TABLE_H

typedef uint32_t key_t;

typedef enum TABLE_ERRORS
{
    OK,
    CREATE_ERROR,
    INSERT_ERROR,
    UPDATE_ERROR,
    DELETE_ERROR,
    TABLE_FULL,
    NOT_FOUND,
} TABLE_ERRORS;

typedef struct Item
{
    key_t key1;
    key_t key2;
    void *data;
} Item;

typedef struct Table
{
    uint32_t size;
    // uint32_t fullness;
    int step;
    Item *items;

    void (*print)(struct Table *);
    char *(*stringifyData)(void *);

    TABLE_ERRORS(*insert)
    (struct Table *table, uint32_t key1, uint32_t key2, void *data);

    TABLE_ERRORS(*update)
    (struct Table *table, uint32_t key1, uint32_t key2, void *newData);

    TABLE_ERRORS(*delete)
    (struct Table *table, uint32_t key1, uint32_t key2);

    TABLE_ERRORS(*find)
    (struct Table *table, uint32_t key1, uint32_t key2, void **data);
} Table;

#endif
