#include <stdio.h>
#include <stdlib.h>
#define array int *

typedef struct node {
    int key;
    struct node *next;
} Node;

Node *newNode(int key) {
    Node *new = malloc(sizeof(Node));
    new->key = key;
    return new;
}

Node *read() {
    int key;
    char c;
    Node *HEAD, *current, *prev;

    if (!scanf(" %d", &key))
        return NULL;
    HEAD = newNode(key);
    prev = HEAD;
    current = NULL;

    while ((c = getchar()) != EOF && c != '\n' && scanf("%d", &key)) {
        current = newNode(key);
        prev->next = current;
        prev = current;
    }

    if (current)
        current->next = NULL;
    else
        HEAD->next = NULL;
    return HEAD;
}

Node *mid(Node *slow) {
    Node *fast = slow->next;

    while (fast && (fast = fast->next)) {
        fast = fast->next;
        slow = slow->next;
    }
    fast = slow->next;
    slow->next = NULL;
    return fast;
}

Node *merge(Node *a, Node *b) {
    if (a) {
        if (!b)
            return a;
        if (a->key <= b->key) {
            a->next = merge(a->next, b);
            return a;
        }
        b->next = merge(a, b->next);
    }
    return b;
}

Node *mergeSort(Node *n) {
    return (n) ? merge(mergeSort(n), mergeSort(mid(n))) : n;
}

void printList(Node *n) {
    printf("\nNew sequence:\n");
    while (n) {
        printf("%d ", n->key);
        n = n->next;
    }
    printf("\n");
}

int main() {
    printf("This program sorts a linked list based on its nodes' keys values."
           "\nType in a sequence of integer values separated by spaces and "
           "press ENTER: ");
    printList(mergeSort(read()));

    return 0;
}
