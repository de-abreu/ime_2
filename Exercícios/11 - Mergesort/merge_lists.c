#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *next;
} Node;

Node * readList() {
    int key;
    char c;
    Node *HEAD, *current, *prev;

    printf("\nType in a sequence of ascending integer values separated by spaces"
    "and press ENTER:\n");

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

Node * mergeLists (Node *a, Node *b) {
    if (!a && !b)
        return NULL;
    if (a) {
        if (!b)
            return a;
        if (a->key <= b->key) {
            a->next = mergeLists (a->next, b);
            return a;
        }
        b->next = mergeLists (a, b->next);
    }
    return b;
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
    printf("This program merges two linked lists with keys in ascending order."
           "\n");
    printList(mergeLists(readList(), readList()));

    return 0;
}
