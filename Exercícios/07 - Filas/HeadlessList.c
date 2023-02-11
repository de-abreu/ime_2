#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} Node;

typedef struct {
    Node *start, *end;
} List;

List *createList() {
    List *l = malloc(sizeof(List));
    l->start = l->end = NULL;
    return l;
}

bool isEmpty(List *l) { return !l->start; }

Node *createNode(int value) {
    Node *n = malloc(sizeof(Node));
    n->value = value;
    n->next = NULL;
    return n;
}

Node *freeNode(Node *n) {
    Node *next = n->next;
    free(n);
    return next;
}

void freeList(List *l) {
    Node *n = l->start;

    while (n)
        n = freeNode(n);
    free(l);
}

void insert(List *l, int value) {
    Node *new = createNode(value);

    if (l->end)
        l->end->next = new;
    if (!l->start)
        l->start = new;
    l->end = new;
}

int pull(List *l) {
    int value;

    if (!l->start)
        return EOF;
    value = l->start->value;
    if (!(l->start = freeNode(l->start)))
        l->end = l->start;
    return value;
}
