#include "./circList.h"
// Implementation of a Circular Queue with no head node;

CircQueue *newQueue(int value) {
    CircQueue *c = malloc(sizeof(CircQueue));

    c->value = value;
    c->next = c;
    return c;
}

CircQueue *push(CircQueue *c, int value) {
    CircQueue *new = newQueue(value);

    if (c) {
        new->next = c->next;
        c->next = new;
    }
    return new;
}

bool isEmpty(CircQueue *c) { return c; }

int pull(CircQueue **c) {
    CircQueue *old;
    int value;

    if (!*c)
        return EOF;

    old = (*c)->next;
    value = old->value;
    if (*c == old)
        *c = NULL;
    else
        (*c)->next = old->next;
    free(old);

    return value;
}

void freeCircQueue(CircQueue **c) {
    if (!*c)
        return;
    freeQueue(*c, *c);
    *c = NULL;
}

void freeQueue(CircQueue *start, CircQueue *current) {
    CircQueue *next = current->next;
    free(current);

    if (next != start)
        freeQueue(start, next);
}
