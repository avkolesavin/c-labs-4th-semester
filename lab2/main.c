#include <stdlib.h>
#include <stdio.h>
#include "strings/strings.h"

int main()
{
    printf("Pls, enter some text:\n");

    void *originalString = scanString();
    void *resultString = getFormattedString(originalString);

    printf("\nOriginal string: \n");
    printString(originalString);
    printf("\nResult string: \n");
    printString(resultString);

    freeString(originalString);
    freeString(resultString);
}