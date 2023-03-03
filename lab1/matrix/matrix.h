int *copyVector(int *sourceVector, int vectorSize);
int *sliceVector(int *sourceVector, int vectorSize, int startIndex, int endIndex);

void printMatrix(int **matrix, int rowsCount, int *rowsSizes);
void freeMatrix(int **matrix, int rowsCount);