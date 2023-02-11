#include <stdio.h>
#include <stdlib.h>
#define LENGTH 10

int *readNumbers(int size) {
    int i = 0, value, *v = calloc(size, sizeof(int));

    while (i < size && scanf(" %d", &value)) {
        if (value > 9 || value < 0) {
            printf("Value %d out of range: ignoring...\n", value);
            continue;
        }
        v[i++] = value;
    }
    return v;
}

void printNumbers(int *v, int size) {
    int i;

    printf("Array contents: ");
    for (i = 0; i < size; i++)
        printf("%d ", v[i]);
    printf("\n");
}

int *permutate(int *v, int size) {
    int i, *w = calloc(size, sizeof(int));

    for (i = 0; i < size; i++)
        w[v[i]] = i;
    return w;
}

int main() {
    int *v;
    printf("This program takes integers from 0 through 9 and stores it in an "
           "array v of length 10. Later, it swaps the number positions in such "
           "a way that for each v[i] = j there will be a v[j] = i after the "
           "numbers are swapped. Positions left unspecified will be set to "
           "0.\nType in a sequence of 10 numbers:\n");
    printNumbers(v = readNumbers(LENGTH), LENGTH);
    printf("Permutation.\n");
    printNumbers(permutate(v, LENGTH), LENGTH);
    return 0;
}
