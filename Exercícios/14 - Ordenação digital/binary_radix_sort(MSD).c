#include <limits.h>
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

int max(Array a, int size) {
    int i, max = *a;

    for (i = 1; i < size; i++)
        if (a[i] > max)
            max = a[i];
    return max;
}

int bits(int n) { return (n >>= 1) ? 1 + bits(n) : 0; }

int pivot(Array A, int size, unsigned int mask) {
    int i, pivot;

    for (i = pivot = 0; i < size; i++)
        if ((A[i] & mask) == 0)
            pivot++;
    return pivot;
}

Array append(Array a, Array b, int p, int size) {
    int i, *result = malloc(size * sizeof(int));

    for (i = 0; i < p; i++)
        result[i] = a[i];
    while (i < size) {
        result[i] = b[i - p];
        i++;
    }
    free(a);
    free(b);
    return result;
}

void distribute(Array A, Array zeroes, Array ones, int mask, int size) {
    if (size <= 0)
        return;
    if (*A & mask) {
        *ones = *A;
        ones += 1;
    } else {
        *zeroes = *A;
        zeroes += 1;
    }
    distribute(A + 1, zeroes, ones, mask, size - 1);
}

Array radixSort(Array A, int size, unsigned int mask) {
    int p, *zeroes, *ones;

    if (!mask || size <= 1)
        return A;

    p = pivot(A, size, mask);

    if (!p || p == size)
        return radixSort(A, size, mask >> 1);

    zeroes = malloc(p * sizeof(int));
    ones = malloc((size - p) * sizeof(int));

    distribute(A, zeroes, ones, mask, size);
    free(A);

    zeroes = radixSort(zeroes, p, mask >> 1);
    ones = radixSort(ones, size - p, mask >> 1);
    return append(zeroes, ones, p, size);
}

int main() {
    Array A;
    int i, size;

    printf("This program performs a binary radix sort.\nType in a sequence "
           "of integer values separated by spaces and press ENTER: ");
    A = readArray(&size);
    A = radixSort(A, size, 1 << bits(max(A, size)));

    printf("New sequence:\n");
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
    return 0;
}
