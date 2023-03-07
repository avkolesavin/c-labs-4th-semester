#include <stdlib.h>
#include <stdio.h>
#include "./matrix.h"

Vector *createVector(int length)
{
    if (length < 0)
    {
        return NULL;
    }

    Vector *vector = malloc(sizeof(Vector));
    vector->items = calloc(length, sizeof(int));

    vector->length = length;

    return vector;
}

void freeVector(Vector *vector)
{
    free(vector->items);
    free(vector);
}

Matrix *createMatrix(int length)
{
    if (length < 0)
    {
        return NULL;
    }

    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = calloc(length, sizeof(Vector *));

    matrix->length = length;

    return matrix;
}

void freeMatrix(Matrix *matrix)
{
    if (matrix == NULL)
        return;

    for (int i = 0; i < matrix->length; i++)
        freeVector(matrix->rows[i]);

    free(matrix->rows);
    free(matrix);
}

Vector *copyVector(Vector *sourceVector)
{
    if (sourceVector == NULL)
    {
        return NULL;
    }

    Vector *newVector = createVector(sourceVector->length);

    for (int i = 0; i < sourceVector->length; i++)
    {
        newVector->items[i] = sourceVector->items[i];
    }

    return newVector;
}

Vector *sliceVector(Vector *sourceVector, int startIndex, int endIndex)
{
    if (endIndex + 1 > sourceVector->length)
        return NULL;

    if (startIndex < 0)
        return NULL;

    if (endIndex < startIndex)
        return NULL;

    int newVectorSize = endIndex - startIndex + 1;
    Vector *newVector = createVector(newVectorSize);

    for (int i = 0; i < newVectorSize; i++)
        newVector->items[i] = sourceVector->items[startIndex + i];

    return newVector;
}

void printMatrix(Matrix *matrix)
{
    if (matrix == NULL)
    {
        printf("NULL\n");
        return;
    }

    printf("[\n");

    for (int i = 0; i < matrix->length; i++)
    {
        printf("  [");
        Vector *row = matrix->rows[i];

        for (int j = 0; j < row->length; j++)
        {
            if (j == (row->length - 1))
                printf("%d", row->items[j]);
            else
                printf("%d, ", row->items[j]);
        }

        if ((i + 1) < matrix->length)
            printf("],\n");
        else
            printf("]\n");
    }
    printf("]\n");
}
