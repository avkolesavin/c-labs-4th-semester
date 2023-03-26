// #define DATA_TYPE char *

#include <stdio.h>
#include <stdlib.h>
// #include "table/table.h"

typedef struct S
{
    void (*hi)();
} S;

typedef struct S1
{
    char *name;
    void (*hi)();
} S1;

void S1_hi(S1 *this)
{
    printf("Hi! My name is %s.\n", this->name);
}

S1 *newS1(char *name)
{
    S1 *newS1 = malloc(sizeof(S1));
    newS1->name = name;
    newS1->hi = S1_hi;

    return newS1;
}

typedef struct S2
{
    void (*hi)();
    int age;
    char *n;
} S2;

void S2_hi(S2 *this)
{
    printf("Hi! My name is %s and i'm %d years old.\n", this->n, this->age);
}

S2 *newS2(char *name, int age)
{
    S2 *newS2 = malloc(sizeof(S2));
    newS2->n = name;
    newS2->hi = S2_hi;
    newS2->age = age;

    return newS2;
}

void hi(void *s)
{
    // Почему работает с S2_hi, если в hi() не передаётся this? О_о
    ((S *)s)->hi();
}

int main(int argc, char *argv[])
{
    S1 *s1 = newS1("Tom");
    S2 *s2 = newS2("Jack", 21);

    // hi(s1);
    hi(s2);

    return 0;
}

/*
Table *table = newTable(adapter_structure);
table.init();
table.print();
table.close();
*/
