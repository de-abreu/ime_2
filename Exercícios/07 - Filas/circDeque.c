#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *prev, *next;
} List;

List *newNode(int value) {
    List *l = malloc(sizeof(List));
    l->value = value;
    return l;
}

List *freeNode(List *l) {
    List *next = l->next;

    if (l->next == l)
        next = NULL;
    else {
        next->prev = l->prev;
        l->prev->next = next;
    }
    free(l);
    return next;
}

List *newList(int value) {
    List *l = newNode(value);
    l->prev = l->next = l;
    return l;
}

void push(List *l, int value) {
    List *prev = l->prev, *new = newNode(value);
    prev->next = new;
    new->prev = prev;
    new->next = l;
    l->prev = new;
}

int pull(List **l) {
    int value;

    if (!l)
        return EOF;
    value = (*l)->prev->value;
    *l = freeNode((*l)->prev);
    return value;
}

bool isEmpty(List *l) { return !l; }

void freeList(List **l) {
    while (*l)
        *l = freeNode(*l);
}
