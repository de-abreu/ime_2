#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int digit;
    struct node *next;
} Node;

Node *binary(Node *stack, int dec) {
    Node *n = malloc(sizeof(Node));

    n->digit = dec % 2;
    n->next = stack;
    return (dec == 0) ? n : binary(n, dec / 2);
}

bool twoComplement(Node *stack) {
    if (!stack)
        return false;
    stack->digit = (stack->digit == 0) ? 1 : 0;

    /* "false" indicates the recursive binary sum hasn't completed */
    if (!twoComplement(stack->next)) {
        if (stack->digit == 1) {
            stack->digit = 0;
            return false;
        }
        stack->digit = 1;
    }
    return true;
}

Node *base2(int dec) {
    Node *stack = binary(NULL, abs(dec));
    if (dec < 0)
        twoComplement(stack);
    return stack;
}

void printStack(Node *stack) {
    if (!stack)
        printf("\n");
    else {
        printf("%d", stack->digit);
        printStack(stack->next);
    }
}

int main() {
    int dec;

    printf("This program reads an integer number and converts it to its "
           "equivalent binary number using the two's complement model.\nType "
           "in a number: ");

    if (!scanf("%d", &dec)) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Binary equivalent: ");
    printStack(base2(dec));
    return 0;
}
