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
    Matrix *originMatrix = NULL;
    Matrix *resultMatrix = NULL;
    int originMatrixRowsCount = 0;
    int resultMatrixRowsCount = 0;

    do
    {
        printf("Pls enter matrix rows count: ");
        scanf("%d", &originMatrixRowsCount);
    } while (originMatrixRowsCount <= 0);

    originMatrix = createMatrix(originMatrixRowsCount);

    for (int i = 0; i < originMatrixRowsCount; i++)
    {
        int rowSize = 0;
        Vector *vector = NULL;

        do
        {
            printf("\nEnter size of [%d] row: ", i);
            scanf("%d", &rowSize);
        } while (rowSize <= 0);

        vector = createVector(rowSize);

        char includeRowToResult = 0;

        for (int j = 0; j < rowSize; j++)
        {
            int value = 0;

            printf("Value for [%d] element: ", j);
            scanf("%d", &value);

            vector->items[j] = value;

            if (value != 0)
                includeRowToResult = 1;
        }

        originMatrix->rows[i] = vector;

        if (includeRowToResult)
            resultMatrixRowsCount++;
    }

    printf("\nOrigin matrix: ");
    printMatrix(originMatrix);

    resultMatrix = createMatrix(resultMatrixRowsCount);
    int resultRowIndex = 0;

    for (int i = 0; i < originMatrix->length; i++)
    {
        int positiveElementIndex = -1, negativeElementIndex = -1;
        Vector *row = originMatrix->rows[i];

        for (int j = 0; j < row->length; j++)
        {

            if (positiveElementIndex == -1 && row->items[j] > 0)
                positiveElementIndex = j;

            if (negativeElementIndex == -1 && row->items[j] < 0)
                negativeElementIndex = j;
        }

        if (positiveElementIndex == negativeElementIndex)
            continue;

        Vector *resultRow = NULL;

        if (positiveElementIndex == -1 || negativeElementIndex == -1)
        {
            resultRow = copyVector(row);
        }
        else
        {
            resultRow = sliceVector(
                row,
                min(positiveElementIndex, negativeElementIndex),
                max(positiveElementIndex, negativeElementIndex));
        }

        resultMatrix->rows[resultRowIndex] = resultRow;
        resultRowIndex++;
    }

    printf("\nResult matrix: ");
    printMatrix(resultMatrix);

    freeMatrix(originMatrix);
    freeMatrix(resultMatrix);

    return 0;
}
