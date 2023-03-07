typedef struct Vector
{
    int *items;
    int length;
} Vector;

typedef struct Matrix
{
    Vector **rows;
    int length;
} Matrix;

Vector *createVector(int length);
Matrix *createMatrix(int length);
void freeMatrix(Matrix *matrix);

Vector *copyVector(Vector *sourceVector);
Vector *sliceVector(Vector *sourceVector, int startIndex, int endIndex);

void printMatrix(Matrix *matrix);
