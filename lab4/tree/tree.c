#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int key;
    char *data;
    struct Node *left;
    struct Node *right;
    struct Node *next;
} Node;

Node *createNode(int key, char *data)
{
    Node *node = malloc(sizeof(Node));

    node->key = key;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;

    return node;
}

void insert(Node **root, Node **last, int key, char *data)
{
    if (*root == NULL)
    {
        *root = createNode(key, data);

        if (*last != NULL)
            (*last)->next = *root;

        *last = *root;
        return;
    }

    if (key < (*root)->key)
        insert(&(*root)->left, last, key, data);
    else if (key > (*root)->key)
        insert(&(*root)->right, last, key, data);
    else
        printf("Error: duplicate key\n");
}

Node *findMin(Node *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

void deleteNode(Node **root, int key)
{
    if (*root == NULL)
        return;
    if (key < (*root)->key)
        deleteNode(&(*root)->left, key);
    else if (key > (*root)->key)
        deleteNode(&(*root)->right, key);
    else
    {
        if ((*root)->left == NULL && (*root)->right == NULL)
        {
            free((*root)->data);
            free(*root);

            *root = NULL;
        }
        else if ((*root)->left == NULL)
        {
            Node *temp = *root;
            *root = (*root)->right;

            free(temp->data);
            free(temp);
        }
        else if ((*root)->right == NULL)
        {
            Node *temp = *root;
            *root = (*root)->left;

            free(temp->data);
            free(temp);
        }
        else
        {
            Node *temp = findMin((*root)->right);
            (*root)->key = temp->key;
            (*root)->data = temp->data;
            deleteNode(&(*root)->right, temp->key);
        }
    }
}

char *search(Node *root, int key)
{
    while (root != NULL)
    {
        if (key < root->key)
            root = root->left;
        else if (key > root->key)
            root = root->right;
        else
            return root->data;
    }

    return NULL;
}

void printInOrder(Node *node)
{
    if (node == NULL)
        return;

    printInOrder(node->left);

    printf("%d: %s\n", node->key, node->data);

    printInOrder(node->right);
}

void printInReverseOrder(Node *node)
{
    if (node == NULL)
        return;

    printInReverseOrder(node->right);

    printf("%d: %s\n", node->key, node->data);

    printInReverseOrder(node->left);
}

void printInInsertionOrder(Node *node)
{
    while (node != NULL)
    {
        printf("%d: %s\n", node->key, node->data);
        node = node->next;
    }
}

void serialize(Node *node, char *filePath)
{
    FILE *file = fopen(filePath, "wb");

    while (node != NULL)
    {
        fwrite(&node->key, sizeof(node->key), 1, file);
        size_t dataLength = strlen(node->data);
        fwrite(&dataLength, sizeof(size_t), 1, file);
        fwrite(node->data, sizeof(char), dataLength, file);

        node = node->next;
    }

    fclose(file);
}

void deserialize(Node **root, Node **last, char *filePath)
{
    printf("[DEBUG] read file: %s\n", filePath);
    FILE *file = fopen(filePath, "rb");

    if (file == NULL)
        return;

    while (!feof(file))
    {
        int key = 0;
        size_t keyWasRead = fread(&key, sizeof(int), 1, file);
        // printf("[DEBUG] read key: %d\n", key);
        // printf("[DEBUG] keyWasRead: %lu\n", keyWasRead);

        if (!keyWasRead)
            break;

        size_t dataLength = 0;
        fread(&dataLength, sizeof(size_t), 1, file);
        // printf("[DEBUG] dataLength: %lu\n", dataLength);

        char *data = malloc(sizeof(char) * dataLength);
        fread(data, sizeof(char), dataLength, file);
        // printf("[DEBUG] read data: %s\n", data);

        insert(root, last, key, data);
        // printf("\n");
    }

    // printf("[DEBUG] deserialization done\n");

    fclose(file);
}