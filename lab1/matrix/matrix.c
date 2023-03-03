#include <stdlib.h>
#include <stdio.h>
#include "./matrix.h"

int *copyVector(int *sourceVector, int vectorSize)
{
    int *newVector = calloc(vectorSize, sizeof(int));

    for (int i = 0; i < vectorSize; i++)
    {
        newVector[i] = sourceVector[i];
    }

    return newVector;
}

int *sliceVector(int *sourceVector, int vectorSize, int startIndex, int endIndex)
{
    if (endIndex + 1 > vectorSize)
        return NULL;

    if (startIndex < 0)
        return NULL;

    if (endIndex < startIndex)
        return NULL;

    int newVectorSize = endIndex - startIndex + 1;
    int *newVector = calloc(newVectorSize, sizeof(int));

    for (int i = 0; i < newVectorSize; i++)
        newVector[i] = sourceVector[i + startIndex];

    return newVector;
}

void printMatrix(int **matrix, int rowsCount, int *rowsSizes)
{
    printf("[\n");

    for (int i = 0; i < rowsCount; i++)
    {
        printf("  [");

        for (int j = 0, rowSize = rowsSizes[i]; j < rowSize; j++)
        {
            if (j == (rowSize - 1))
                printf("%d", matrix[i][j]);
            else
                printf("%d, ", matrix[i][j]);
        }

        if (matrix[i + 1] != '\0')
            printf("],\n");
        else
            printf("]\n");
    }
    printf("]\n");
}

void freeMatrix(int **matrix, int rowsCount)
{
    for (int i = 0; i < rowsCount; i++)
    {
        free(matrix[i]);
    }

    free(matrix);
}