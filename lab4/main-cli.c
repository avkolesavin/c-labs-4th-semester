#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

#include "tree/tree.h"

int main()
{
    Node *root = NULL;
    Node *last = NULL;

    char command[20];
    int key;
    char data[100];

    while (1)
    {
        printf("\nEnter command: ");
        scanf("%s", command);

        if (strcmp(command, "insert") == 0)
        {
            printf("Enter key: ");
            scanf("%d", &key);
            printf("Enter data: ");
            scanf("%s", data);
            char *dataCopy = malloc(strlen(data));
            insert(&root, &last, key, strcpy(dataCopy, data));
        }
        else if (strcmp(command, "delete") == 0)
        {
            printf("Enter key: ");
            scanf("%d", &key);
            deleteNode(&root, key);
        }
        else if (strcmp(command, "search") == 0)
        {
            printf("Enter key: ");
            scanf("%d", &key);
            char *result = search(root, key);
            if (result != NULL)
            {
                printf("Search result: %s\n", result);
            }
            else
            {
                printf("Key not found\n");
            }
        }
        else if (strcmp(command, "print") == 0)
        {
            scanf("%s", command);
            if (strcmp(command, "reverse") == 0)
            {
                printInReverseOrder(root);
            }
            else if (strcmp(command, "order") == 0)
            {
                printInOrder(root);
            }
            else if (strcmp(command, "insertion") == 0)
            {
                printInInsertionOrder(root);
            }
        }
        else if (strcmp(command, "save") == 0)
        {
            printf("File path: ");
            char filePath[100];
            scanf("%s", filePath);
            serialize(root, filePath);
        }
        else if (strcmp(command, "load") == 0)
        {
            printf("File path: ");
            char filePath[100];
            scanf("%s", filePath);
            deserialize(&root, &last, filePath);
        }
        else if (strcmp(command, "exit") == 0)
        {
            break;
        }
    }

    return 0;
}