#include <stdlib.h>
#include <stdio.h>

#include "tree/tree.h"

int main()
{
    Node *root = NULL;
    Node *last = NULL;

    // insert(&root, &last, 5, "five");
    // insert(&root, &last, 3, "three");
    // insert(&root, &last, 7, "seven");
    // insert(&root, &last, 1, "one");
    // insert(&root, &last, 4, "four");
    // insert(&root, &last, 6, "six");
    // insert(&root, &last, 8, "eight");

    deserialize(&root, &last, "./tree-dump");

    printf("In order:\n");
    printInOrder(root);
    printf("\n");

    printf("In reverse order:\n");
    printInReverseOrder(root);
    printf("\n");

    printf("In insertion order:\n");
    printInInsertionOrder(root);
    printf("\n");

    // serialize(root, "./tree-dump");

    // char *result = search(root, 4);
    // if (result != NULL)
    // {
    //     printf("Search result: %s\n", result);
    // }
    // else
    // {
    //     printf("Key not found\n");
    // }

    // deleteNode(&root, 5);

    // printf("After deletion:\n");
    // printInOrder(root);
    // printf("\n");

    return 0;
}