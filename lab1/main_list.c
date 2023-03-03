#include <stdio.h>
#include <stdlib.h>
#include "matrix_list/matrix.h"

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

// Matrix makeNewMatrix(Matrix originMatrix)
// {
// }

int main()
{
    int m = 0;

    printf("Введите количество строк матрицы (m): ");
    scanf("%d", &m);

    Matrix *originMatrix = createMatrix();

    for (int i = 0; i < m; i++)
    {
        int ni = 0;
        printf("\nКоличество элементов для %d-й строки (ni): \n", i + 1);
        scanf("%d", &ni);

        IntList *rowItems = createIntList();

        for (int j = 0; j < ni; j++)
        {
            int value = 0;

            printf("Значение для %d-го элемента %d-й строки: ", j + 1, i + 1);
            scanf("%d", &value);

            appendIntItem(rowItems, value);
        }

        appendRow(originMatrix, rowItems);
    }

    printMatrix(originMatrix);

    return 0;
}