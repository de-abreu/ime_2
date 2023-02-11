#include <stdio.h>
#include <stdlib.h>
#define Array int *

Array readArray(int *size) {
    int d, i = 0;
    char c;
    Array A;

    *size = 1;
    A = malloc(sizeof(int));
    do {
        if (!scanf(" %d", &d))
            continue;
        if (i == *size - 1) {
            *size *= 2;
            A = realloc(A, *size * sizeof(int));
        }
        A[i++] = d;
    } while ((c = getchar()) != EOF && c != '\n');
    *size = i;
    return A;
}

int pivot(Array A, int size, int mask) {
    int i, pivot;

    for (i = pivot = 0; i < size; i++)
        if ((A[i] & mask) == 0)
            pivot++;
    return pivot;
}

Array countingSort(Array A, int size, int mask) {
    int i, j = pivot(A, size, mask), k;
    Array sorted;

    if (!j || j == size)
        return A;

    sorted = malloc(size * sizeof(int));
    for (i = k = 0; k < size; k++)
        if (A[k] & mask)
            sorted[j++] = A[k];
        else
            sorted[i++] = A[k];
    free(A);
    return sorted;
}

Array radixSort(Array A, int size) {
    int mask;

    for (mask = 1; mask; mask <<= 1)
        A = countingSort(A, size, mask);
    return A;
}

int main() {
    Array A;
    int i, size;

    printf("This program performs a binary radix sort.\nType in a sequence "
           "of integer values separated by spaces and press ENTER: ");
    A = readArray(&size);
    A = radixSort(A, size);

    printf("New sequence:\n");
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
    return 0;
}
