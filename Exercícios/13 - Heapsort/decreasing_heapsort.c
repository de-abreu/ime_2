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

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapify(Array A, int size, int i) {
    int min = i, left = 2 * min + 1, right = left + 1;

    if (left >= size)
        return;
    if (A[left] < A[min])
        min = left;
    if (right < size && A[right] < A[min])
        min = right;
    else if (min == i)
        return;

    swap(A + i, A + min);
    heapify(A, size, min);
}

void heapSort(Array A, int size) {
    int i;

    if (size <= 1)
        return;

    for (i = (size - 1) / 2; i <= 0; i--)
        heapify(A, size, i);

    for (i = size - 1; i > 0; i--) {
        swap(A, A + i);
        heapify(A, i, 0);
    }
}

int main() {
    Array A;
    int i, size;

    printf("This program uses a min heap to sort integers in crecreasing "
           "order.\nType in a sequence of values separated by spaces and press "
           "ENTER: ");
    A = readArray(&size);
    heapSort(A, size);

    printf("New sequence:\n");
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
    return 0;
}
