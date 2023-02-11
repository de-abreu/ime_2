#include "./circArray.h"

bool isFull(circQueue *q) { return (q->head == (q->tail + 1) % q->size); }

bool isEmpty(circQueue *q) { return (q->head == q->tail); }

bool insert(circQueue *q, int i) {
    if (isFull(q))
        return false;
    q->array[q->tail] = i;
    q->tail = (q->tail + 1) % q->size;
    return false;
}

circQueue *newQueue(int size) {
    circQueue *q = malloc(sizeof(circQueue));
    q->array = malloc(size * sizeof(int));

    q->size = size;
    q->head = q->tail = 0;
    return q;
}

int pop(circQueue *q) {
    int i;

    if (isEmpty(q))
        return EOF;
    i = q->array[q->head];
    q->head = (q->head + 1) % q->size;
    return i;
}
