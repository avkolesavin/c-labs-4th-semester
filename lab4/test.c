#include <stdlib.h>
#include <stdio.h>

void changePtr(int **ptr)
{
    int *newPtr = malloc(sizeof(int));

    *newPtr = 123;

    *ptr = newPtr;
}

int main()
{
    int *myPtr = NULL;

    printf("myPtr: %p\n", myPtr);
    changePtr(&myPtr);
    printf("myPtr: %p\n", myPtr);

    return 0;
}