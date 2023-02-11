#include "./dynamicArray.h"

bool isEmpty(array *a) { return a->end == a->start; }

array *resize(array *a) {
    a->capacity *= 2;
    a->end -= a->start;
    a->start = 0;
    return realloc(a, a->capacity * sizeof(array));
}

void insert(array *a, int i) {
    a->end++;
    if (a->end == a->capacity)
        a = resize(a);
    a->values[a->end] = i;
}

int pop(array *a) { return isEmpty(a) ? EOF : a->values[a->start++]; }

void freeArray(array *a) {
    free(a->values);
    free(a);
}
