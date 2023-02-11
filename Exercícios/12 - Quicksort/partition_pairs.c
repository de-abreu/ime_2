#include <stdlib.h>
#include <stdio.h>

typedef struct node{
    int key;
    struct node *next;
} Node;

Node * newNode (int key) {
    Node * new = malloc(sizeof(Node));
    new->key = key;
    return new;
}

Node * read() {
    int key;
    char c;
    Node *HEAD, *current, *prev;

    if (!scanf(" %d", &key))
        return NULL;
    HEAD = newNode(key);
    prev = HEAD;
    current = NULL;

    while ((c = getchar()) != EOF && c != '\n' && scanf("%d", &key)) {
        current = newNode(key);
        prev->next = current;
        prev = current;
    }

    if (current)
        current->next = NULL;
    else
        HEAD->next = NULL;
    return HEAD;
}

void partition (Node *n, Node **pairs, Node **odds) {
    if (!n)
        *pairs = *odds = NULL;
    else if (n->key % 2 == 0) {
        *pairs = n;
        partition(n->next, &n->next, odds);
    }
    else {
        *odds = n;
        partition(n->next, pairs, &n->next);
    }
}

void printList(Node *n) {
    while (n) {
        printf("%d ", n->key);
        n = n->next;
    }
    printf("\n");
}

int main () {
    Node *pairs, *odds;

    printf("This program partitions a linked list into two, onde containing "
           "all nodes with pair values and another containing other nodes.\n"
           "Type in a sequence of integer values separated by spaces and "
           "press ENTER:\n");

    partition(read(), &pairs, &odds);

    printf("\nPair values:\n");
    printList(pairs);

    printf("\nOdd values:\n");
    printList(odds);

    return 0;
}
