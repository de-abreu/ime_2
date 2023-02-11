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

List *append(List *a, List *pivot, List *b) {
    pivot->next = b;
    return a;
}

List *headless(List *l) {
    List *next = l->next;
    free(l);
    return next;
}

List *partition(List *l, List *zeroes, List *ones, int mask) {
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
    ones->next = NULL;
    return zeroes;
}

List *countingSort(List *l, int mask) {
    List *zeroes = newList(0, NULL), *ones = newList(1, NULL),
         *pivot = partition(l, zeroes, ones, mask);

    zeroes = headless(zeroes);
    ones = headless(ones);

    return (zeroes && ones) ? append(zeroes, pivot, ones) : l;
}

List *radixSort(List *l) {
    int mask;

    if (l)
        for (mask = 1; mask; mask <<= 1)
            l = countingSort(l, mask);
    return l;
}

int main() {
    printf("This program sorts a linked list based on its nodes' keys values."
           "\nType in a sequence of integer values separated by spaces and "
           "press ENTER: ");
    printList(radixSort(read()));

    return 0;
}
