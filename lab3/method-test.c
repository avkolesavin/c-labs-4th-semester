#include <stdio.h>
#include <stdlib.h>

typedef struct Object
{
    void (*foo)();
    int value;
} Object;

void foo(Object *obj)
{
    printf("Object [%p] value: %d\n", obj, obj->value);
}

void callFoo(void *obj)
{
    ((Object *)obj)->foo();
}

int main()
{
    Object *obj = malloc(sizeof(Object));
    obj->foo = foo;
    obj->value = 123;

    obj->foo(obj);
    callFoo(obj); // Works O_o

    // obj->foo() // Segmentation fault

    return 0;
}
