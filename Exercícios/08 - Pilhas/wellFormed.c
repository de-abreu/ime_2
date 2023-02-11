#include <stdbool.h>
#include <stdio.h>
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

bool close(Stack **s, char c) {
    if (!*s || (c == '}' && (*s)->c != '{') || (c == ']' && (*s)->c != '[') ||
        (c == ')' && (*s)->c != '('))
        return false;
    *s = freeNode(*s);
    return true;
}

bool wellFormed(Stack *s, char *string) {
    if (!*string)
        return !s;
    if (strchr("([{", *string))
        s = push(s, *string);
    else if (strchr("}])", *string) && !close(&s, *string))
        return false;
    return wellFormed(s, string + 1);
}

int main(int argc, char *argv[]) {
    int i;
    Stack *s = NULL;

    for (i = 1; i < argc; i++)
        if (!wellFormed(s, argv[i]))
            return 1;
    return 0;
}
