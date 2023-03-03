#include <stdlib.h>
#include <stdio.h>
#include "./matrix.h"

// ==== IntList ====

IntList *createIntList()
{
    IntList *list = malloc(sizeof(IntList));
    list->root = NULL;
    list->length = 0;

    return list;
}

IntItem *getLastIntItem(IntItem *item)
{
    if (item == NULL)
        return NULL;

    if (item->next == NULL)
        return item;

    return getLastIntItem(item->next);
}

void appendIntItem(IntList *list, int value)
{
    IntItem *newItem = malloc(sizeof(IntItem));
    newItem->next = NULL;
    newItem->value = value;

    if (list->root == NULL)
    {
        list->root = newItem;
    }
    else
    {
        IntItem *lastItem = getLastIntItem(list->root);
        lastItem->next = newItem;
    }

    list->length++;
}

int getIntValueAt(IntList *list, int index)
{
    if (index < 0)
        return INT32_MAX;
    if (list->root == NULL)
        return INT32_MAX;

    int counter = 0;
    IntItem *currentItem = list->root;

    while (counter != index)
    {
        if (currentItem->next == NULL)
            return INT32_MAX;

        counter++;
        currentItem = currentItem->next;
    }

    return currentItem->value;
}

void freeItem(IntItem *item)
{
    if (item->next != NULL)
        freeItem(item->next);

    free(item);
}

void freeIntList(IntList *list)
{
    if (list->root != NULL)
        freeItem(list->root);

    free(list);
}

// ==== Matrix ====

Matrix *createMatrix()
{
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->root = NULL;
    matrix->length = 0;

    return matrix;
}

MatrixRow *getLastRow(MatrixRow *row)
{
    if (row == NULL)
        return NULL;

    if (row->next == NULL)
        return row;

    return getLastRow(row->next);
}

void appendRow(Matrix *matrix, IntList *items)
{
    MatrixRow *newRow = malloc(sizeof(MatrixRow));
    newRow->next = NULL;
    newRow->items = items;

    if (matrix->root == NULL)
    {
        matrix->root = newRow;
    }
    else
    {
        MatrixRow *lastRow = getLastRow(matrix->root);
        lastRow->next = newRow;
    }

    matrix->length++;
}

void freeRow(MatrixRow *row)
{
    if (row->items != NULL)
        freeIntList(row->items);

    if (row->next != NULL)
        freeRow(row->next);

    free(row);
}

void freeMatrix(Matrix *matrix)
{
    if (matrix->root != NULL)
        freeRow(matrix->root);

    free(matrix);
}

int getMatrixValueAt(Matrix *matrix, int rowIndex, int columnIndex)
{
    // INT32_MAX - ошибка

    if (rowIndex < 0 || columnIndex < 0)
        return INT32_MAX;

    if (matrix->root == NULL)
        return INT32_MAX;

    MatrixRow *currentRow = matrix->root;
    int rowCounter = 0;

    while (rowCounter != rowIndex)
    {
        if (currentRow->next == NULL)
            return INT32_MAX;

        rowCounter++;
        currentRow = currentRow->next;
    }

    return getIntValueAt(currentRow->items, columnIndex);
}

void printMatrix(Matrix *matrix)
{
    printf("[\n");

    MatrixRow *row = matrix->root;
    for (int i = 0; i < matrix->length; i++, row = row->next)
    {
        printf("  [");
        for (int j = 0, rowLength = row->items->length; j < rowLength; j++)
        {
            if (j == (rowLength - 1))
                printf("%d", getMatrixValueAt(matrix, i, j));
            else
                printf("%d, ", getMatrixValueAt(matrix, i, j));
        }

        if (i != (matrix->length - 1))
            printf("],\n");
        else
            printf("]\n");
    }
    printf("]\n");
}