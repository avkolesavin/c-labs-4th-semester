#include <stdlib.h>
#include <stdio.h>
#include "strings.h"
#include "common.c"

void *scanString()
{
    char *string = calloc(STRING_MAX_SIZE, sizeof(char));

    scanf("%1024[^\r]", string);

    return string;
}

void freeString(void *string)
{
    if (string != NULL)
    {
        free(string);
    }
}

void printString(void *string)
{
    printf("\e[0;32m\"%s\"\e[0m\n", string);
}

void *getFormattedString(void *string)
{
    if (string == NULL)
        return NULL;

    char *formattedString = calloc(STRING_MAX_SIZE, sizeof(char));
    int i = 0, wordStartIndex = -1, wordLength = 0;
    char currentChar = ((char *)string)[i];
    int seek = 0;

    for (; currentChar != '\0'; i++, currentChar = ((char *)string)[i])
    {
        if (isLetter(currentChar))
        {
            if (wordStartIndex == -1)
            {
                wordStartIndex = i;
                wordLength = 1;
            }
            else
            {
                wordLength++;
            }
        }

        if (isSpaceChar(currentChar))
        {
            if (wordLength == WORDS_MAX_LENGTH)
            {
                for (int j = wordStartIndex; j < (wordStartIndex + wordLength); j++, seek++)
                    formattedString[seek] = ((char *)string)[j];

                formattedString[seek++] = ' ';
            }

            wordStartIndex = -1;
            wordLength = 0;
        }
    }

    return formattedString;
}