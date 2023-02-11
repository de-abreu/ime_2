#include <stdlib.h>
#include <stdio.h>
#define array int*

void merge (array A, array tmp, int pivot, int size) {
	int i, k, j = pivot;

	for (i = k = 0; k < size; k++)
		tmp[k] = (j == size || (i < pivot && A[i] <= A[j])) ?
		A[i++] : A[j++];
    for (k = 0; k < size; k++)
        A[k] = tmp[k];

}

void mergeSort (array A, array tmp, int size) {
	int pivot;

	if (size <= 1)
		return;
    pivot = size / 2;
    mergeSort(A, tmp, pivot);
    mergeSort(A + pivot, tmp + pivot, size - pivot);
    merge(A, tmp, pivot, size);
}

void sort (array A, int size) {
    array tmp = malloc(size * sizeof(int));
    mergeSort(A, tmp, size);
    free(tmp);
}

array readArray (int *size) {
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

int main () {
    array A;
    int i, size;

    printf("This program performs a merge sort.\nType in a sequence of values separated by spaces and press ENTER: ");
    A = readArray(&size);
    sort(A, size);

    printf("New sequence:\n");
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
    return 0;
}
