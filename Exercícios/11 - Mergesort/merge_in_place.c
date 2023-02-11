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

void interleave(Array A, int pivot, int size) {
    int i, tmp = A[pivot];

    if (pivot == size)
        return;
    for (i = pivot; i > 0 && A[i - 1] > tmp; i--)
        A[i] = A[i - 1];
    A[i] = tmp;
    interleave(A, pivot + 1, size);
}

void mergeSort(Array A, int size) {
    int pivot;

    if (size <= 1)
        return;
    pivot = size / 2;
    mergeSort(A, pivot);
    mergeSort(A + pivot, size - pivot);
    interleave(A, pivot, size);
}

int main() {
    Array A;
    int i, size;

    printf("This program performs an in-place merge sort.\nType in a sequence "
           "of values separated by spaces and press ENTER: ");
    A = readArray(&size);
    mergeSort(A, size);

    printf("New sequence:\n");
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
    return 0;
}
