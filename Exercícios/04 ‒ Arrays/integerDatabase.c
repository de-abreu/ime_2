#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} Node;

typedef struct {
    Node *start;
} List;

Node *newNode(int value, Node *next) {
    Node *n = malloc(sizeof(Node));

    n->value = value;
    n->next = next;
    return n;
}

Node *freeNode(Node *n) {
    Node *next = n->next;
    free(n);
    return next;
}

void freeAllNodes(Node *n) {
    if (!n)
        return;
    freeAllNodes(n->next);
    free(n);
}

List *newList() {
    List *l = malloc(sizeof(List));

    l->start = NULL;
    return l;
}

void freeList(List *l) {
    freeAllNodes(l->start);
    free(l);
}

bool push(Node *n, int value) {
    if (n->value == value)
        return false;
    if (!n->next || n->next->value > value) {
        n->next = newNode(value, n->next);
        return true;
    }
    return push(n->next, value);
}

Node *pull(Node *n, int value, bool *found) {
    if (n) {
        if (n->value == value) {
            *found = true;
            return freeNode(n);
        }
        if (n->value < value)
            n->next = pull(n->next, value, found);
    }
    return n;
}

bool insert(List *l, int value) {
    if (!l)
        return false;
    if (!l->start || l->start->value > value) {
        l->start = newNode(value, l->start);
        return true;
    }
    return push(l->start, value);
}

bool take(List *l, int value) {
    bool found = false;
    if (l)
        l->start = pull(l->start, value, &found);
    return found;
}

void printNodes(Node *n) {
    if (!n)
        printf("\n");
    else {
        printf("%d ", n->value);
        printNodes(n->next);
    }
}

void printList(List *l) {
    printf("List contents: ");
    printNodes(l->start);
}

void readCommands() {
    char option;
    int value;
    List *l = newList();

    while (scanf(" %[ir]", &option)) {
        if (option == 'i') {
            while (scanf(" %d", &value))
                if (!insert(l, value))
                    printf(
                        "Value %d already present in the list, ignoring...\n",
                        value);
        } else
            while (scanf(" %d", &value))
                if (!take(l, value))
                    printf("Value %d not present in the list, ignoring...\n",
                           value);
        printList(l);
    }
    printf("Terminating execution...\n");
    freeList(l);
}

int main() {
    printf("This program stores unique integer values in an ordered linked "
           "list. Let n be an integer or a set of integers separated by "
           "spaces, type i n to insert it in the list, r n to remove it from "
           "it, or type in any other character to stop the execution of the "
           "program. Don't forget to press ENTER after passing a command.\n");
    readCommands();
}
