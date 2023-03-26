#ifndef DATA_TYPE
#define DATA_TYPE int
#endif

enum TABLE_ERROR
{
    FULL,
    NOT_FOUND
};

typedef int TKey;

typedef struct Item
{
    TKey key;
    DATA_TYPE data;
} Item;

typedef struct Table
{
    Item *items;
    int size;
    int step;
} Table;

Table *createTable();
void destroyTable(Table *table);
