#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/param.h>

typedef struct node{
    int key, height;
    struct node *lt, *gt;
} Node;

/* Tree balancing */

int height (Node *root) {
    return (root) ? root->height : -1;
}

int getBalance (Node *root) {
    return height(root->lt) - height(root->gt);
}

void updateHeight (Node *root) {
    root->height = MAX(height(root->lt), height(root->gt)) + 1;
}

Node * rotateLeft (Node *root) {
    Node *newRoot = root->gt, *child = newRoot->lt;

    newRoot->lt = root;
    root->gt = child;

    updateHeight(root);
    updateHeight(newRoot);
    return newRoot;
}

Node * rotateRight (Node *root) {
    Node *newRoot = root->lt, *child = newRoot->gt;

    newRoot->gt = root;
    root->lt = child;

    updateHeight(root);
    updateHeight(newRoot);
    return newRoot;
}

Node * balanceTree (Node *root) {
    int balance = getBalance(root);

    /* Left heavy */
    if (balance > 1) {
        if (getBalance(root->lt) < 0)
            root->lt = rotateLeft(root->lt);
        return rotateRight(root);
    }

    /* Right heavy */
    if (balance < -1) {
        if (getBalance(root->gt) > 0)
            root->gt = rotateRight(root->gt);
        return rotateLeft(root);
    }

    updateHeight(root);
    return root;
}

/* Node insertion */

Node * newNode(int key){
    Node *new = malloc(sizeof(Node));

    new->key = key;
    new->height = 0;
    new->lt = new->gt = NULL;
    return new;
}

bool insertNode(Node **root, int key) {
    Node **n;

    if (!*root) {
        *root = newNode(key);
        return true;
    }
    if (key == (*root)->key)
        return false;
    n = (key < (*root)->key) ? &(*root)->lt : &(*root)->gt;
    if (!insertNode(n, key))
        return false;
    *root = balanceTree(*root);
    return true;
}

Node * read() {
    int key;
    char c;
    Node *root = NULL;

    while ((c = getchar()) != EOF && c != '\n' && scanf("%d", &key))
        insertNode(&root, key);
    return root;
}

/* Find next */

Node * nextKey (Node * root, int key) {
    Node *n;

    if (!root)
        return root;
    n = nextKey((key < root->key) ? root->lt : root->gt, key);
    return (n && n->key > key) ? n : root;
}

/* Destroy tree after use */

void destroy (Node * root) {
    if (root->lt)
        destroy(root->lt);
    if (root->gt)
        destroy(root->gt);
    free(root);
}

bool destroyTree (Node **root) {
    if (!*root)
        return false;
    destroy(*root);
    *root = NULL;
    return true;
}

int main () {
    int key;
    Node *root;

    printf("This program allows for the creation of a Binary Search Tree "
    "(BST) and then finds the node with the smallest key that is greater than "
    "a given number.\nType in a sequence of integers separated by space to be "
    "added as keys in the BST and press ENTER to confirm:\n");
    root = read();

    printf("\nType in an integer to search for a key: ");
    if (!scanf("%d", &key)) {
        printf("Invalid input\n");
        return 1;
    }

    printf("\nNext smallest key: %d\n", nextKey(root, key)->key);
    destroyTree(&root);
}
