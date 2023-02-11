#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *string;
    int length, count;
    struct node *next;
} List;

List *addWord(char *string, List *next) {
    List *l = malloc(sizeof(List));
    l->length = strlen(string);
    l->string = malloc((l->length + 1) * sizeof(char));

    strcpy(l->string, string);
    l->count = 1;
    l->next = next;
    return l;
}

void freeList(List *l) {
    if (!l)
        return;
    freeList(l->next);
    free(l->string);
    free(l);
}

List *push(List *l, char *string) {
    int order;

    if (!l || (order = strcmp(string, l->string)) < 0)
        return addWord(string, l);
    if (order > 0)
        l->next = push(l->next, string);
    else
        l->count++;
    return l;
}

void printList(List *l) {
    if (l) {
        if (l->length > 35)
            printf("%-36.36s... %d\n", l->string, l->count);
        else
            printf("%-40.40s%d\n", l->string, l->count);
        printList(l->next);
    }
}

List *readFile(FILE *f, List *l) {
    char string[64];
    while (fscanf(f, " %s", string) != EOF)
        l = push(l, string);
    return l;
}

int main(int argc, char *argv[]) {
    List *l = NULL;
    FILE *f = fopen(argv[1], "r");
    if (!f)
        return 1;
    l = readFile(f, l);
    fclose(f);
    printList(l);
    freeList(l);
    return 0;
}
