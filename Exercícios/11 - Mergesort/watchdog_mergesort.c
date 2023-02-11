#include <stdio.h>
#include <stdlib.h>
#define array int *

void merge(array A, int pivot, int size) {
    int i = 0, j = size - 1, k;
    array tmp = malloc(size * sizeof(int));

    while (i < pivot) {
        tmp[i] = A[i];
        i++;
    }
    while (i < size) {
        tmp[i] = A[j - (i - pivot)];
        i++;
    }
    for (i = k = 0; k < size; k++)
        A[k] = (tmp[i] <= tmp[j]) ? tmp[i++] : tmp[j--];
    free(tmp);
}

void mergeSort(array A, int size) {
    int pivot;

    if (size <= 1)
        return;
    pivot = size / 2;
    mergeSort(A, pivot);
    mergeSort(A + pivot, size - pivot);
    merge(A, pivot, size);
}

array readArray(int *size) {
    int i = 0;
    char c;
    array A;

    *size = 1;
    A = malloc(sizeof(int));
    do {
        if (!scanf("%d", A + i))
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

int main() {
    array A;
    int i, size;

    printf("This program performs a merge sort.\nType in a sequence of values "
           "separated by spaces and press ENTER: ");
    A = readArray(&size);
    mergeSort(A, size);

    printf("New sequence:\n");
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
    return 0;
}
