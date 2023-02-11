#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int count, size;
    char **words;
} Array;

typedef struct node {
    char *word;
    struct node *next;
} Stack;

typedef struct {
    Stack **words, *max;
    int size, sets, maxCount, *count, *order;
} Dict;

/* Initializers */

Array *newArray() {
    Array *a = malloc(sizeof(Array));
    a->words = malloc(sizeof(char *));
    a->count = 0;
    a->size = 1;
    return a;
}

Stack *newStack(char *word, Stack *next) {
    Stack *s = malloc(sizeof(Stack));
    s->word = word;
    s->next = next;
    return s;
}

Dict *newDict(int size) {
    Dict *d = malloc(sizeof(Dict));

    d->words = calloc(size, sizeof(Stack *));
    d->count = malloc(size * sizeof(int));
    d->order = malloc(size * sizeof(int));
    d->maxCount = d->sets = 0;
    d->size = size;
    return d;
}

/* Freeing memory */

void freeArray(Array *a) {
    int i;

    for (i = 0; i < a->size; i++)
        free(a->words[i]);
    free(a->words);
    free(a);
}

void freeStack(Stack *s) {
    if (!s)
        return;
    freeStack(s->next);
    free(s);
}

void freeDict(Dict *d) {
    int i = 0;

    while (i < d->size)
        freeStack(d->words[i++]);
    free(d->words);
    free(d->count);
    free(d);
}

/* Array insertion functions */

void insert(Array *a, char *buffer, int size) {
    char *new = malloc((size + 1) * sizeof(char));
    if (a->count == a->size - 1) {
        a->size *= 2;
        a->words = realloc(a->words, a->size * sizeof(char *));
    }
    a->words[a->count++] = strcpy(new, buffer);
}

Array *readWords(FILE *f) {
    int size;
    char *buffer = malloc(64 * sizeof(char));
    Array *a = newArray();

    while ((size = fscanf(f, " %s", buffer)) != EOF)
        insert(a, buffer, size);
    free(buffer);
    return a;
}

/* Stack insertion algorithm */

void push(Stack *head, char *word) {
    Stack *s = newStack(word, head->next);
    head->next = s;
}

/* Sorting algorithms */

void insertionSort(char *word, int size) {
    int i, tmp;

    if (size-- <= 1)
        return;
    insertionSort(word, size);
    tmp = word[size];
    for (i = size; i > 0 && word[i - 1] > tmp; i--)
        word[i] = word[i - 1];
    word[i] = tmp;
}

/* Hash and rehash functions */

int key(char *word, int *i) {
    int k;
    for (*i = k = 0; word[*i]; (*i)++)
        k += word[*i];
    return k * (*i);
}

int bits(int n) {
    n >>= 1;
    return (n) ? 1 + bits(n) : 1;
}

int hash(int key, int mask, int b) {
    int index = key & mask;
    key >>= b;

    return (key) ? index ^ hash(key, mask, b) : index;
}

int rehash(int index, int i, int mask) { return (index + i * i) & mask; }

/* Dictionary insertion algorithm */

void add(Dict *d, char *word, int mask, int b) {
    int size, i, index = hash(key(word, &size), mask, b);
    char *charSet = malloc((size + 1) * sizeof(char));
    insertionSort(strcpy(charSet, word), size);

    //  Alternative:
    //  char *charSet = radixSort(strcpy(malloc((size + 1) * sizeof(char)),
    //  word), size, CHAR_BIT * sizeof(char));

    for (i = 1; d->words[index] && strcmp(d->words[index]->word, charSet) != 0;
         i += 2)
        index = hash(index + i * i, mask, b);

    if (!d->words[index]) {
        d->words[index] = newStack(charSet, NULL);
        d->order[d->sets++] = index;
        d->count[index] = 0;
    } else
        free(charSet);
    push(d->words[index], word);
    d->count[index]++;

    if (d->count[index] > d->maxCount) {
        d->maxCount = d->count[index];
        d->max = d->words[index];
    }
}

Dict *buildDict(Array *a) {
    int i, mask = a->size - 1, b = bits(mask);
    Dict *d = newDict(a->size);

    for (i = 0; i < a->count; i++)
        add(d, a->words[i], mask, b);
    return d;
}

/* Printing functions */

void printStack(Stack *s, char *terminator) {
    if (!s)
        return;
    printStack(s->next, ", ");
    printf("%s%s", s->word, terminator);
}

void printMax(Dict *d) {
    printf(
        "O conjunto de caracteres que possibilita o maior número de anagramas "
        "na lingua portuguesa é \"%s\", que permite formar %d anagramas: ",
        d->max->word, d->maxCount);
    printStack(d->max->next, ".\n");
}

void printSets(Dict *d) {
    int i;
    printf("\nOs conjuntos de anagramas com mais de um item são:\n");
    for (i = 0; i < d->sets; i++) {
        if (d->count[d->order[i]] < 2)
            continue;
        printf("Conjunto \"%s\", %d anagramas: ", d->words[d->order[i]]->word,
               d->count[d->order[i]]);
        printStack(d->words[d->order[i]]->next, ".\n");
    }
}

/* Main function */

int main(int argc, char *argv[]) {
    FILE *f = fopen(argv[1], "r");
    Array *a = readWords(f);
    Dict *d = buildDict(a);

    printMax(d);
    printSets(d);
    fclose(f);
    freeArray(a);
    freeDict(d);
    return 0;
}
