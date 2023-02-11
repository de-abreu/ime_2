#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *c;
    int top, size;
} Stack;

Stack *newStack(int size) {
    Stack *s = malloc(sizeof(Stack));

    s->c = malloc(size * sizeof(char));
    s->size = size;
    s->top = 0;
    return s;
}

bool isFull(Stack *s) { return s->top == s->size; }

bool isEmpty(Stack *s) { return !s->top; }

void resize(Stack *s) {
    s->size *= 2;
    s->c = realloc(s->c, s->size * sizeof(char));
}

void push(Stack *s, char c) {
    if (isFull(s))
        resize(s);
    s->c[(s->top)++] = c;
}

char pop(Stack *s) { return (isEmpty(s)) ? '\0' : s->c[--(s->top)]; }
