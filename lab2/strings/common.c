#include "list-strings.h"

const int STRING_MAX_SIZE = 1024;
const int WORDS_MAX_LENGTH = 3;

int isLetter(char chr)
{
    return chr >= 'A' && chr <= 'z';
}

int isSpaceChar(char chr)
{
    return chr == ' ' || chr == '\t';
}
