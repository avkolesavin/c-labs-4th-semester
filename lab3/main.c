// ---- Table ----

struct TableAdapter;

typedef struct Item
{
    int key;
    char *data;
} Item;

typedef struct Table
{
    Item *items;
    int length;

    struct TableAdapter *adapter;
} Table;

typedef struct TableAdapter
{
    void (*init)(Table *table);
} TableAdapter;

Table *newTable(TableAdapter *adapter)
{
    Table *table = malloc(sizeof(Table));
    table->adapter = adapter;

    return table;
}

void init(Table *table)
{
    table->adapter->init(table);
}

// ---------------

// ---- Memory Adapter ----

void memoryInit(Table *table)
{
}

TableAdapter memoryAdapter = {.init = memoryInit};

// -----------------------

int main(int argc, char *argv[])
{
    TableType *table = createTable(tableAdapter);
    table->init();
    return 0;
}
