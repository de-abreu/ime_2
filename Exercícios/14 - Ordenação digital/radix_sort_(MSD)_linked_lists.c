#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define array int *

typedef struct node {
    int key;
    struct node *next;
} List;

List *newList(int key, List *next) {
    List *new = malloc(sizeof(List));
    new->key = key;
    new->next = next;
    return new;
}

List *read() {
    int key;
    char c;
    List *HEAD, *current, *prev;

    if (!scanf(" %d", &key))
        return NULL;
    HEAD = newList(key, NULL);
    prev = HEAD;
    current = NULL;

    while ((c = getchar()) != EOF && c != '\n' && scanf("%d", &key)) {
        current = newList(key, NULL);
        prev->next = current;
        prev = current;
    }

    if (current)
        current->next = NULL;
    else
        HEAD->next = NULL;
    return HEAD;
}

void printList(List *n) {
    printf("\nNew sequence:\n");
    while (n) {
        printf("%d ", n->key);
        n = n->next;
    }
    printf("\n");
}

int max(List *l) {
    int max = l->key;
    for (l = l->next; l; l = l->next)
        if (l->key > max)
            max = l->key;
    return max;
}

int bits(int n) { return (n >>= 1) ? 1 + bits(n) : 0; }

List *append(List *a, List *b) {
    while (a->next)
        a = a->next;
    a->next = b;
    return a;
}

List *headless(List *l) {
    List *next = l->next;
    free(l);
    return next;
}

void partition(List *l, List *zeroes, List *ones, int mask) {
    while (l) {
        if (l->key & mask) {
            ones->next = l;
            ones = ones->next;
        } else {
            zeroes->next = l;
            zeroes = zeroes->next;
        }
        l = l->next;
    }
    zeroes->next = ones->next = NULL;
}

List *radixSort(List *l, unsigned int mask) {
    List *zeroes, *ones;

    if (!l->next || !mask)
        return l;
    zeroes = newList(0, NULL);
    ones = newList(1, NULL);
    partition(l, zeroes, ones, mask);
    zeroes = headless(zeroes);
    ones = headless(ones);

    if (!zeroes || !ones)
        return l;

    zeroes = radixSort(zeroes, mask >> 1);
    ones = radixSort(ones, mask >> 1);
    return append(zeroes, ones);
}

int main() {
    List *l;
    printf("This program sorts a linked list based on its nodes' keys values."
           "\nType in a sequence of integer values separated by spaces and "
           "press ENTER: ");
    l = read();
    printList(radixSort(l, 1 << bits(max(l))));

    return 0;
}
