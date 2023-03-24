#include <stdlib.h>
#include <stdio.h>
#include "strings.h"
#include "common.c"

String *__createString()
{
    String *listString = malloc(sizeof(String));
    listString->length = 0;
    listString->head = NULL;
    listString->tail = NULL;

    return listString;
}

Char *__createChar(char chr)
{
    Char *c = malloc(sizeof(Char));
    c->value = chr;
    c->next = NULL;

    return c;
}

void __freeChar(Char *chr)
{
    if (chr->next == NULL)
    {
        free(chr);
        return;
    }

    __freeChar(chr->next);
    free(chr);
}

void freeString(void *string)
{
    String *str = (String *)string;

    if (str->head != NULL)
    {
        __freeChar(str->head);
    }

    free(string);
}

void __appendChar(void *string, char chr)
{
    String *str = (String *)string;

    Char *c = __createChar(chr);

    if (str->length == 0)
    {
        str->head = c;
        str->tail = c;
        str->head->next = str->tail;
    }
    else
    {
        str->tail->next = c;
        str->tail = c;
    }

    str->length++;
}

void __clearString(String *str)
{
    if (str != NULL && str->head != NULL)
    {
        __freeChar(str->head);
        str->head = NULL;
        str->tail = NULL;
        str->length = 0;
    }
}

void *scanString()
{
    char *bufferString = calloc(STRING_MAX_SIZE, sizeof(char));
    String *listString = __createString();

    scanf("%1024[^\r]", bufferString);

    for (int i = 0; ((char *)bufferString)[i] != '\0'; i++)
        __appendChar(listString, ((char *)bufferString)[i]);

    free(bufferString);

    return listString;
}

void printString(void *string)
{
    if (((String *)string)->head == NULL)
    {
        return;
    }

    String *str = (String *)string;
    Char *currentChar = ((String *)string)->head;

    printf("\e[0;32m\"");

    while (currentChar != NULL)
    {
        printf("%c", currentChar->value);

        currentChar = currentChar->next;
    }

    printf("\"\e[0m\n");
}

void *getFormattedString(void *string)
{
    if (string == NULL || ((String *)string)->head == NULL)
        return NULL;

    String *formattedString = __createString();
    Char *currentChar = ((String *)string)->head;
    String *bufferString = __createString();
    int hasWordAlready = 0;

    while (currentChar != NULL)
    {
        if (isLetter(currentChar->value))
            __appendChar(bufferString, currentChar->value);

        if (isSpaceChar(currentChar->value))
        {
            // Concatenation
            if (bufferString->length == WORDS_MAX_LENGTH)
            {
                if (hasWordAlready)
                    __appendChar(formattedString, ' ');

                Char *currentBufferChar = bufferString->head;

                while (currentBufferChar != NULL)
                {
                    __appendChar(formattedString, currentBufferChar->value);
                    currentBufferChar = currentBufferChar->next;
                };

                hasWordAlready = 1;
            }

            __clearString(bufferString);
        }

        currentChar = currentChar->next;
    }

    freeString(bufferString);

    return formattedString;
}
