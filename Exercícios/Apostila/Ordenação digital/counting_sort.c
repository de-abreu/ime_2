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

array cumulativeFrequency(array A, int size, int max) {
    int i;
    array frequency = calloc((max + 1), sizeof(int));

    for (i = 0; i < size; i++)
        frequency[A[i] + 1]++;
    for (i = 1; i <= max; i++)
        frequency[i] += frequency[i - 1];
    return frequency;
}

void countingSort (array* A, int size, int max) {
    int i;
    array count = cumulativeFrequency(*A, size, max);
	array sorted = malloc(size * sizeof(int));

    for (i = 0; i < size; i++) {
        sorted[count[(*A)[i]]] = (*A)[i];
        count[(*A)[i]]++;
    }
    free(*A);
    free(count);
    *A = sorted;
}

int main () {
    int i, size, max;
	array A;

	printf("Este programa admite uma lista de valores inteiros x tais que %d ≤ x ≤ %d e os ordena em ordem crescente.\nDigite uma série de valores inteiros separadas entre si por espaço e pressione ENTER:\n", 0, INT_MAX);
	A = readArray(&size, &max);

	countingSort(&A, size, max);

	printf("Arranjo ordenado:\n");
	for (i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
	free(A);
    return 0;
}
