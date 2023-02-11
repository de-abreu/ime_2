#include <stdlib.h>
#include <stdio.h>
#define array int*

int findMax(array A, int size) {
    int i, max = A[0];

    for(i = 1; i < size; i++)
        if (A[i] > max)
            max = A[i];
    return max;
}

array cumulativeFreq (array A, int size, int exp) {
    int i, radix;
    array frequency = calloc(19, sizeof(int));

    for (i = 0; i < size; i++) {
        radix = A[i] / exp % 10;
		frequency[10 + radix]++;
    }
    for (i = 1; i < 18; i++)
		frequency[i] += frequency[i - 1];
    return frequency;
}

void countingSort (array *A, int size, int exp) {
    int i, radix;
    array count = cumulativeFreq(*A, size, exp);
	array sorted = malloc(size * sizeof(int));

    for (i = 0; i < size; i++) {
        radix = (*A)[i] / exp % 10;
        sorted[count[9 + radix]++] = (*A)[i];
    }
    free(*A);
    free(count);
    *A = sorted;
}

void radixSort(array *A, int size) {
    int exp, max = findMax(*A, size);

    for (exp = 1; max / exp > 0; exp *= 10)
        countingSort(A, size, exp);
}

array readArray (int *size) {
	int d, i = 0;
	char c;
	array A;

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

int main () {
    array A;
    int i, size;

    printf("This program performs an insertion sort.\nType in a sequence of values separated by spaces and press ENTER: ");
    A = readArray(&size);
    radixSort(&A, size);

    printf("New sequence:\n");
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
    return 0;
}
