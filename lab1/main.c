#include <stdlib.h>
#include <stdio.h>
#include "./matrix/matrix.h"

/*
Вариант 22
Из входного потока вводится непрямоугольная матрица целых чисел a[ij],
i=1,...,m, j=1,...,n. Значения m и n заранее не известны и вводятся из
входного потока.
Сформировать новую матрицу, поместив в ее i-ю строку элементы из
i-й строки исходной матрицы, размещенные между первым элементом > 0 и
первым элементом < 0 (порядок расположения элементов произволен).
Если в строке нет элемента, удовлетворяющего какому-либо одному условию,
то выбираются элементы до конца строки исходной матрицы.
Если строка исходной матрицы содержит только нули (т.е. не выполняются
оба условия), то в результирующую матрицу новая строка не включаеся.
Исходную и полученую матрицы вывести в выходной поток с необходимыми
комментариями.

*/

int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    int **originMatrix = NULL;
    int **resultMatrix = NULL;
    int originMatrixRowsCount = 0;
    int resultMatrixRowsCount = 0;
    int *originMatrixRowsSizes = NULL;
    int *resultMatrixRowsSizes = NULL;

    do
    {
        printf("Pls enter matrix rows count: ");
        scanf("%d", &originMatrixRowsCount);
    } while (originMatrixRowsCount <= 0);

    originMatrix = calloc(originMatrixRowsCount, sizeof(int *));
    originMatrixRowsSizes = calloc(originMatrixRowsCount, sizeof(int));

    for (int i = 0; i < originMatrixRowsCount; i++)
    {
        int rowSize = 0;
        int *row = NULL;

        do
        {
            printf("\nEnter size of [%d] row: ", i);
            scanf("%d", &rowSize);
        } while (rowSize <= 0);

        row = calloc(rowSize, sizeof(int *));
        originMatrixRowsSizes[i] = rowSize;

        char includeRowToResult = 0;

        for (int j = 0; j < rowSize; j++)
        {
            int value = 0;

            printf("Value for [%d] element: ", j);
            scanf("%d", &value);

            row[j] = value;

            if (value != 0)
                includeRowToResult = 1;
        }

        originMatrix[i] = row;

        if (includeRowToResult)
            resultMatrixRowsCount++;
    }

    printf("\nOrigin matrix: ");
    printMatrix(originMatrix, originMatrixRowsCount, originMatrixRowsSizes);

    resultMatrix = calloc(resultMatrixRowsCount, sizeof(int *));
    resultMatrixRowsSizes = calloc(resultMatrixRowsCount, sizeof(int));
    int resultRowIndex = 0;

    for (int i = 0; i < originMatrixRowsCount; i++)
    {
        int positiveElementIndex = -1, negativeElementIndex = -1;

        for (int j = 0, rowSize = originMatrixRowsSizes[i]; j < rowSize; j++)
        {

            if (positiveElementIndex == -1 && originMatrix[i][j] > 0)
                positiveElementIndex = j;

            if (negativeElementIndex == -1 && originMatrix[i][j] < 0)
                negativeElementIndex = j;
        }

        if (positiveElementIndex == negativeElementIndex)
            continue;

        int *row = NULL;

        if (positiveElementIndex == -1 || negativeElementIndex == -1)
        {
            row = copyVector(originMatrix[i], originMatrixRowsSizes[i]);
            resultMatrixRowsSizes[resultRowIndex] = originMatrixRowsSizes[i];
        }
        else
        {
            row = sliceVector(
                originMatrix[i],
                originMatrixRowsSizes[i],
                min(positiveElementIndex, negativeElementIndex),
                max(positiveElementIndex, negativeElementIndex));

            resultMatrixRowsSizes[resultRowIndex] = abs(positiveElementIndex - negativeElementIndex) + 1;
        }

        resultMatrix[resultRowIndex] = row;
        resultRowIndex++;
    }

    printf("\nResult matrix: ");
    printMatrix(resultMatrix, resultMatrixRowsCount, resultMatrixRowsSizes);

    freeMatrix(originMatrix, originMatrixRowsCount);
    freeMatrix(resultMatrix, resultMatrixRowsCount);
    free(originMatrixRowsSizes);
    free(resultMatrixRowsSizes);

    return 0;
}
