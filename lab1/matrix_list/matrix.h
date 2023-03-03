typedef struct IntItem
{
    int value;
    struct IntItem *next;
} IntItem;

typedef struct
{
    IntItem *root;
    int length;
} IntList;

typedef struct MatrixRow
{
    IntList *items;
    struct MatrixRow *next;
} MatrixRow;

typedef struct matrix
{
    MatrixRow *root;
    int length;
} Matrix;

IntList *createIntList();
void appendIntItem(IntList *list, int value);
int getIntValueAt(IntList *list, int index);
void freeIntList(IntList *list);

Matrix *createMatrix();
void appendRow(Matrix *matrix, IntList *items);
void freeMatrix(Matrix *matrix);
void printMatrix(Matrix *matrix);
