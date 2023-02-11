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

Node * insert (Node *HEAD) {
    Node *tmp = HEAD, *prev = tmp->next, *next;

    HEAD = prev;
    for (next = prev->next; next && tmp->key > next->key; next = next->next)
        prev = next;

    prev->next = tmp;
    tmp->next = next;
    return HEAD;
}

Node * insertionSort (Node *HEAD) {
    if (HEAD) {
        HEAD->next = insertionSort(HEAD->next);
        if (HEAD->next && HEAD->key > HEAD->next->key)
            return insert(HEAD);
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
    printf("This program sorts a linked list based on its nodes' keys values."
           "\nType in a sequence of integer values separated by spaces and "
           "press ENTER: ");
    printList(insertionSort(read()));

    return 0;
}
