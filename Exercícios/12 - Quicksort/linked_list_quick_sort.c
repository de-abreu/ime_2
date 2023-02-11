#include <stdlib.h>
#include <stdio.h>

typedef struct node{
    int key;
    struct node *next;
} Node;

Node * newNode (int key) {
    Node * new = malloc(sizeof(Node));
    new->key = key;
    return new;
}

Node * read() {
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

Node * median (Node *start) {
    Node *slow = start->next, *fast = slow->next;

    if (!fast)
        return slow;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    if ((start->key > slow->key) ^ (start->key > fast->key))
        return start;
    if ((slow->key < start->key) ^ (slow->key < fast->key))
        return slow;
    return fast;
}

void partition (Node *n, Node *pivot, Node **le, Node **gt) {
    if (!n)
        *le = *gt = NULL;
    else if (n == pivot)
        partition(n->next, pivot, le, gt);
    else if (n->key <= pivot->key) {
        *le = n;
        partition(n->next, pivot, &n->next, gt);
    }
    else {
        *gt = n;
        partition(n->next, pivot, le, &n->next);
    }
}

Node * append (Node *le, Node *pivot, Node *gt) {
    if (le) {
        le->next = append(le->next, pivot, gt);
        return le;
    }
    pivot->next = gt;
    return pivot;
}

Node * quickSort (Node * HEAD) {
    Node *le, *gt, *pivot;

    if (!HEAD || !HEAD->next)
        return HEAD;
    pivot = median(HEAD);
    partition(HEAD, pivot, &le, &gt);
    return append(quickSort(le), pivot, quickSort(gt));
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
    printList(quickSort(read()));

    return 0;
}
