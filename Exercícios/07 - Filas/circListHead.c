#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} CircList;

CircList *newList() {
    CircList *c = malloc(sizeof(CircList));
    c->next = c;
    return c;
}

CircList *freeNode(CircList *c) {
    CircList *next = c->next;
    free(c);
    return next;
}

void freeList(CircList **c) {
    CircList *current = *c;

    while ((current = freeNode(current)) != *c) {
    }
    *c = NULL;
}

bool isEmpty(CircList *c) { return c->next == c; }

CircList *push(CircList *c, int value) {
    CircList *new = malloc(sizeof(CircList)), *next;

    c->value = value;
    next = c->next;
    c->next = new;
    new->next = next;
    return new;
}

int pull(CircList *c) {
    int value;

    if (isEmpty(c))
        return EOF;
    value = c->next->value;
    c->next = freeNode(c->next);
    return value;
}
