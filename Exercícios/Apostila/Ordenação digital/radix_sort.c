#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#define array int*

array readArray (int *size, int *max) {
	int d, i = 0;
	char c;
	array A;

    *max = 0;
	*size = 1;
	A = malloc(sizeof(int));
	do {
		if (!scanf(" %d", &d))
			continue;
		if (i == *size - 1) {
			*size *= 2;
			A = realloc(A, *size * sizeof(int));
		}
        if (d > *max)
            *max = d;
		A[i++] = d;
	} while ((c = getchar()) != EOF && c != '\n');
	*size = i;
	return A;
}

array cumulativeFrequency(array A, int size, int exp) {
    int i, radix;
    array frequency = calloc(11, sizeof(int));

    for (i = 0; i < size; i++) {
        radix = A[i] / exp % 10;
        frequency[radix + 1]++;
    }
    for (i = 1; i <= 10; i++)
        frequency[i] += frequency[i - 1];
    return frequency;
}

void countingSort (array *A, int size, int exp) {
    int i, radix;
    array count = cumulativeFrequency(*A, size, exp);
	array sorted = malloc(size * sizeof(int));

    for (i = 0; i < size; i++) {
        radix = (*A)[i] / exp % 10;
        sorted[count[radix]] = (*A)[i];
        count[radix]++;
    }
    free(*A);
    free(count);
    *A = sorted;
}

void radixSort(array *A, int size, int max) {
    int exp;

    for (exp = 1; max / exp > 0; exp *= 10)
        countingSort(A, size, exp);
}

int main () {
    int i, size, max;
	array A;

	printf("Este programa admite uma lista de valores inteiros x tais que %d ≤ x ≤ %d e os ordena em ordem crescente.\nDigite uma série de valores inteiros separadas entre si por espaço e pressione ENTER:\n", 0, INT_MAX);
	A = readArray(&size, &max);

	radixSort(&A, size, max);

	printf("Arranjo ordenado:\n");
	for (i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
	free(A);
    return 0;
}
