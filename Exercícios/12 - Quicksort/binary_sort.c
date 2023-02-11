#include <stdio.h>
#include <stdlib.h>

int *readArray(int *size) {
    int i = 0;
    char c;
    int *A;

    *size = 1;
    A = malloc(sizeof(int));
    do {
        if (!scanf(" %d", A + i))
            continue;
        if (i == *size - 1) {
            *size *= 2;
            A = realloc(A, *size * sizeof(int));
        }
        i++;
    } while ((c = getchar()) != EOF && c != '\n');
    *size = i;
    return A;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void partition(int *v, int size) {
    int i, j;

    for (i = j = 0; i < size; i++)
        if (v[i] == 0)
            swap(&v[i], &v[j++]);
}

int main() {
    int *A;
    int i, size;

    printf("This program sorts an array of 0s and 1s in crescent order.\nType "
           "in a sequence of values separated by spaces and press ENTER: ");
    A = readArray(&size);
    partition(A, size);

    printf("New sequence:\n");
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
    return 0;
}
