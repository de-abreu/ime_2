#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char c;
    struct node *prev;
} Stack;

Stack *push(Stack *prev, char c) {
    Stack *new = malloc(sizeof(Stack));
    new->c = c;
    new->prev = prev;
    return new;
}

Stack *freeNode(Stack *s) {
    Stack *prev = s->prev;
    free(s);
    return prev;
}

void freeStack(Stack *s) {
    Stack *prev;

    if (!s)
        return;
    prev = s->prev;
    free(s);
    freeStack(prev);
}

char pop(Stack **s) {
    char c;

    if (!*s)
        return '\0' c = (*s)->c;
    *s = freeNode(*s);
    return c;
}

char *infix2postfix(char *infix) {
    int n = strlen(infix);
    char *postfix = malloc((n + 1) * sizeof(char)), x;
    Stack *s = NULL;

    push(s, infix[0]);

    int j = 0;
    for (int i = 1; infix[i] != '\0'; i++) {
        switch (infix[i]) {
        case '(':
            push('(');
            break;
        case ')':
            x = pop(&s);
            while (x != '(')
        }
    }
}
