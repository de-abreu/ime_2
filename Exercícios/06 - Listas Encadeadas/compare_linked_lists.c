#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} List;

List *newList(int value, List *next) {
    List *l = malloc(sizeof(List));

    l->value = value;
    l->next = next;
    return l;
}

void freeList(List *l) {
    if (!l)
        return;
    freeList(l->next);
    free(l);
}

List *freeNode(List *l) {
    List *next = l->next;
    free(l);
    return next;
}

bool listCmp(List *l1, List *l2) {
    if (l1 == l2)
        return true;
    if (!(l1 && l2) || !listCmp(l1->next, l2->next))
        return false;
    return (l1->value == l2->value);
}

List *listCopy(List *l) { return l ? newList(l->value, listCopy(l->next)) : l; }

List *invert(List *current) {
    List *prev = NULL, *next;

    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

List *swap(List *prev, List *current) {
    List *HEAD;

    if (!current)
        return prev;
    HEAD = swap(current, current->next);
    current->next = prev;
    return HEAD;
}

List *recInvert(List *l) { return swap(NULL, l); }

List *recListCat(List *l1, List *l2) {
    if (!l1)
        return l2;
    l1->next = recListCat(l1->next, l2);
    return l1;
}

void listCat(List *l1, List *l2) {
    if (!l1)
        l1 = l2;
    else {
        while (l1->next)
            l1 = l1->next;
        l1->next = l2;
    }
}

bool isCrescent(List *l) {
    if (!l->next)
        return true;
    return (l->value <= l->next->value) ? isCrescent(l->next) : false;
}

List *minimum(List *l) {
    List *min;

    if (!l->next)
        return l;
    min = minimum(l->next);
    return (l->value <= min->value) ? l : min;
}

List *middle(List *l) {
    List *slow, *fast;
    slow = fast = l;

    while (fast) {
        fast = fast->next;
        if (!fast)
            break;
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}

List *push(List *l, int value) {
    if (!l)
        l = newList(value, l);
    else
        l->next = push(l->next, value);
    return l;
}

List *pull(List *l, int value) {
    if (l) {
        if (l->value == value)
            return freeNode(l);
        l->next = pull(l->next, value);
    }
    return l;
}

List *pullAll(List *l, int value) {
    if (l) {
        if (l->value == value)
            return pullAll(freeNode(l), value);
        l->next = pullAll(l->next, value);
    }
    return l;
}

void flushInput() {
    int c;
    if ((c = getchar()) != '\n' && c != EOF)
        flushInput();
}

List *readList() {
    int value;
    char c;
    if (scanf("%d%c", &value, &c))
        return newList(value, (c == '\n') ? NULL : readList());
    flushInput();
    return NULL;
}

List *insertAfter(List *l, int value, int n) {
    List *prev;

    if (!l || n <= 0)
        return newList(value, l);
    for (prev = l; prev->next && n > 0; n--)
        prev = prev->next;
    prev->next = newList(value, prev->next);
    return l;
}

List *recInsertAfter(List *l, int value, int n) {
    if (!l || n <= 0)
        return newList(value, l);
    l->next = insertAfter(l->next, value, n - 1);
    return l;
}

List *exchange(List *prev, List *next) {
    List *tmp = prev->next;
    prev->next = next->next->next;
    next->next->next = tmp;
    tmp = next->next;
    next->next = prev;
    return tmp;
}

List *findPair(List *prev, List *next, int offset) {
    if (offset > 1)
        return findPair(prev, next->next, offset - 1);
    return (offset == 1) ? exchange(prev, next) : prev;
}

List *moveByIndex(List *l, int index, int offset) {
    if (l) {
        if (index < 1)
            return findPair(l, l, offset);
        l->next = moveByIndex(l->next, index - 1, offset);
    }
    return l;
}

void printList(List *l) {
    if (!l)
        printf("\n");
    else {
        printf("%d ", l->value);
        printList(l->next);
    }
}

void listInfo(List *l) {
    printf("List's contents: ");
    printList(l);
    printf("Is crescent: %s; Minimum value: %d; Middle value: %d.\n",
           isCrescent(l) ? "Yes" : "No", minimum(l)->value, middle(l)->value);
}

int main() {
    List *l1, *l2, *l3;
    l1 = l2 = NULL;
    int i1, i2;

    printf("This program reads a couple of linked lists and compares them. For "
           "the first linked list, type in a sequence of numbers to store and "
           "press ENTER:\n");
    listInfo(l1 = readList());
    printf("Now for the contents of the second list:\n");
    listInfo(l2 = readList());
    printf("Is list 1 equal to list 1: %s; is list 1 equal to list 2: %s\n",
           listCmp(l1, l1) ? "Yes" : "No", listCmp(l1, l2) ? "Yes" : "No");
    printf("This list is a copy of the first list:");
    printList(l3 = listCopy(l1));
    printf(
        "As it can be seen in their different addresses: l1 -> %p; l3 -> %p\n",
        l1, l3);
    printf("This is a concatenation of lists 1 and 2:");
    listCat(l1, l2);
    printList(l1);
    l1 = recInvert(l1);
    printf("This the list inverted by a recursive function: ");
    printList(l1);
    printf("And inverted again by a iteractive function: ");
    printList(l1 = invert(l1));
    printf("Type a value to be inserted to that array and an index in which to "
           "put it: ");
    scanf(" %d %d", &i1, &i2);
    flushInput();
    l1 = recInsertAfter(l1, i1, i2);
    printf("Resulting linked list: ");
    printList(l1);
    printf("Again, to test the iteractive version: ");
    scanf(" %d %d", &i1, &i2);
    flushInput();
    l1 = insertAfter(l1, i1, i2);
    printf("Resulting linked list: ");
    printList(l1);
    printf("Now a function to change the position of two values based on their "
           "indexes. Choose to indexes to have their values swapped: ");
    scanf(" %d %d", &i1, &i2);
    l1 = moveByIndex(l1, i1, i2);
    printList(l1);
    printf("Test removing the first occurence of a value: ");
    scanf(" %d", &i1);
    l1 = pull(l1, i1);
    printList(l1);
    printf("Now test removing all occurences: ");
    scanf(" %d", &i1);
    l1 = pullAll(l1, i1);
    printList(l1);

    return 0;
}
