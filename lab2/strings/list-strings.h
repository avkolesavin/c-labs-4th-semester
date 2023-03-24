typedef struct __sChar
{
    char value;
    struct __sChar *next;
} Char;

typedef struct __sString
{
    struct __sChar *head;
    struct __sChar *tail;
    int length;
} String;
