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

List *push(List *l, int value) {
    if (!l || l->value > value)
        return newList(value, l);
    if (l->value < value)
        l->next = push(l->next, value);
    return l;
}

List *pull(List *l, int value) {
    if (l && l->value <= value) {
        if (l->value == value)
            return freeNode(l);
        l->next = pull(l->next, value);
    }
    return l;
}

List *concatenate(List *l1, List *l2) {
    if (!l1)
        return l2;
    if (!l2)
        return l1;
    if (l1->value <= l2->value) {
        l1->next = concatenate(l1->next, l2);
        return l1;
    }
    l2->next = concatenate(l1, l2->next);
    return l2;
}

int length(List *l) { return l ? length(l->next) + 1 : 0; }

void printList(List *l) {
    if (!l)
        printf("\n");
    else {
        printf("%d ", l->value);
        printList(l->next);
    }
}

void flushInput() {
    int c;
    if ((c = getchar()) != '\n' && c != EOF)
        flushInput();
}

List *readList() {
    int value;
    char c;
    List *l = NULL;

    while (scanf(" %d%c", &value, &c)) {
        l = push(l, value);
        if (c == '\n')
            break;
    }
    return l;
}

void readCommands() {
    char option, c;
    int value;
    List *l = NULL;

    while (scanf(" %[irc\n]", &option)) {
        if (option == '\n')
            break;
        if (option == 'i')
            l = readList();
        else if (option == 'r')
            while (scanf("%d%c", &value, &c) && c != '\n')
                l = pull(l, value);
        else
            l = concatenate(l, readList());
        printf("Resulting list: ");
        printList(l);
        printf("List length: %d\n", length(l));
    }
    printf("Terminating execution...\n");
    freeList(l);
}

int main() {
    printf(
        "This program stores unique integer values in an ordered linked "
        "list. Let n be an integer or a set of integers separated by "
        "spaces:\nType i n to insert it in the list;\nType r n to remove it "
        "from it;\nType c to concatenate it with another set of following "
        "integers;\n, or type in any other character to stop the execution of "
        "the program. Don't forget to press ENTER after passing a command.\n");
    readCommands();
}
