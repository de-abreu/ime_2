#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key;
    struct node *next;
} Node;

Node * read() {
    int key;
    char c;
    Node *HEAD, *current, *prev;

    if (!scanf(" %d", &key))
        return NULL;
    HEAD = malloc(sizeof(Node));
    HEAD->key = key;
    prev = HEAD;
    current = NULL;

    while ((c = getchar()) != EOF && c != '\n') {
        if (!scanf("%d", &key))
            break;
        current = malloc(sizeof(Node));
        current->key = key;
        prev->next = current;
        prev = current;
    }

    if (current)
        current->next = NULL;
    else
        HEAD->next = NULL;
    return HEAD;
}

Node * minimalValue(Node *HEAD, Node **prev) {
    Node *current, *min;

    *prev = NULL;
    for (current = min = HEAD; current->next; current = current->next) {
        if (current->next->key >= min->key)
            continue;
        min = current->next;
        *prev = current;
    }
    return min;
}

Node * swap (Node *HEAD, Node *prev, Node *min) {
    Node *next;

    if (HEAD != min) {
        next = min->next;
        prev->next = HEAD;
        min->next = HEAD->next;
        HEAD->next = next;
    }
    return min;
}

Node * selectionSort (Node *HEAD) {
    Node *prev;

    if (HEAD){
        HEAD = swap(HEAD, prev, minimalValue(HEAD, &prev));
        HEAD->next = selectionSort(HEAD->next);
    }
    return HEAD;
}

void printList(Node *n) {
    printf("\nNew sequence:\n");
    while (n) {
        printf("%d ", n->key);
        n = n->next;
    }
    printf("\n");
}

int main () {
    printf("This program sorts a linked list based on its nodes' keys "
           "values.\nType in a sequence of integer values and press ENTER: ");
    printList(selectionSort(read()));

    return 0;
}
