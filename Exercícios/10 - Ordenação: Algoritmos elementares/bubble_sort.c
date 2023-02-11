#include <stdlib.h>
#include <stdio.h>
#define array int*

void swap (int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void bubbleSort (array A, int size) {
	int i;

	if (size-- <= 1)
		return;
	for (i = 0; i < size; i++)
		if (A[i] > A[i + 1])
			swap(&A[i], &A[i + 1]);
	bubbleSort(A, size);
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
    bubbleSort(A, size);

    printf("New sequence:\n");
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
    return 0;
}
