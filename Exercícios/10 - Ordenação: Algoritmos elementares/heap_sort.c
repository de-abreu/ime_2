#include <stdlib.h>
#include <stdio.h>
#define array int*

void swap (int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void heapify (array A, int size, int i) {
	int max = i, left = 2 * max + 1, right = left + 1;

	if (left >= size)
	 	return;
	if (A[left] > A[max])
		max = left;
	if (right < size && A[right] > A[max])
		max = right;
	else if (max == i)
	 	return;

	swap(A + i, A + max);
	heapify(A, size, max);
}

void heapSort (array A, int size) {
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
    heapSort(A, size);

    printf("New sequence:\n");
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
    return 0;
}
