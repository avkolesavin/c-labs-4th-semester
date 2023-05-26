#ifndef TREE_H
#define TREE_H

typedef struct Node
{
    int key;
    char *data;
    struct Node *left;
    struct Node *right;
    struct Node *next;
} Node;

Node *createNode(int key, char *data);
void insert(Node **root, Node **last, int key, char *data);
void deleteNode(Node **root, int key);
char *search(Node *root, int key);
void printInOrder(Node *node);
void printInReverseOrder(Node *node);
void printInInsertionOrder(Node *node);
void serialize(Node *node, char *filePath);
void deserialize(Node **root, Node **last, char *filePath);

#endif