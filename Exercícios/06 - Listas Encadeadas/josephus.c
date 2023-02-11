#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int i;
    struct node *next;
} List;

List *newList(int i, List *next) {
    List *l = malloc(sizeof(List));

    l->i = i;
    l->next = next;
    return l;
}

List *insert(int total, int left, List **end) {
    if (left > 0)
        return newList(total - left, insert(total, left - 1, end));
    return (*end = newList(total - left, NULL));
}

List *createCircle(int n) {
    List *start, *end;
    start = insert(n, n - 1, &end);
    end->next = start;
    return start;
}

List *pull(List *l) {
    List *next = l->next;
    free(l);
    return next;
}

List *josephus(List *l, int interval) {
    int skip = interval;

    while (l != l->next) {
        while (skip-- > 0)
            l = l->next;
        l->next = pull(l->next);
        skip = interval;
    }
    return l;
}

List *push(List *l, int value) {
    if (!l)
        l = newList(value, l);
    else
        l->next = push(l->next, value);
    return l;
}

int main(int argc, char *argv[]) {
    printf("%d\n", josephus(createCircle(atoi(argv[1])), atoi(argv[2]))->i);
    return 0;
}
