#ifndef TABLE_H
#define TABLE_H

#define ERROR_MESSAGE_BUFFER 255

typedef int keyT;

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
    keyT key1;
    keyT key2;
    void *data;
} Item;

typedef struct Table
{
    int size;
    int fullness;
    int step;
    Item *items;

    char *(*stringifyData)(void *);
    void (*print)(struct Table *);

    TABLE_ERRORS(*insert)
    (struct Table *table, keyT key1, keyT key2, void *data /* , char errorMessage[ERROR_MESSAGE_BUFFER] */);
    TABLE_ERRORS(*update)
    (struct Table *table, keyT key1, keyT key2, void *newData /* , char errorMessage[ERROR_MESSAGE_BUFFER] */);
    TABLE_ERRORS(*delete)
    (struct Table *table, keyT key1, keyT key2 /* , char errorMessage[ERROR_MESSAGE_BUFFER] */);
    TABLE_ERRORS(*find)
    (struct Table *table, keyT key1, keyT key2, void **data /* , char errorMessage[ERROR_MESSAGE_BUFFER] */);
} Table;

#endif
