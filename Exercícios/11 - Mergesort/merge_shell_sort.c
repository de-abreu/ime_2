#include <stdlib.h>
#include <stdio.h>
#define array int*

/* Shell sort */

void insertionSort (array A, int size, int start, int gap) {
    int i = start + gap, tmp;

	if (i >= size)
		return;
	tmp = A[i];
	while (i >= gap && A[i - gap] > tmp) {
		A[i] = A[i - gap];
		i-= gap;
	}
	A[i] = tmp;
	insertionSort(A, size, start + gap, gap);
}

void shellSort (array A, int size) {
	int i, sublist_lenght;

	for (sublist_lenght = size /2; sublist_lenght > 0; sublist_lenght /= 2)
		for (i = 0; i < sublist_lenght; i++)
	    	insertionSort(A, size, i, sublist_lenght);
}

/* Merge Sort */

void merge (array A, int pivot, int size) {
	int i, k, j = pivot;
	array tmp = malloc(size * sizeof(int));

	for (i = k = 0; k < size; k++)
		tmp[k] = (j == size || (i < pivot && A[i] <= A[j])) ?
		A[i++] : A[j++];
	for (k = 0; k < size; k++)
	    A[k] = tmp[k];
	free(tmp);
}

void mergeSort (array A, int size) {
	int pivot;

	if (size <= 1)
		return;
    if (size <= 10)
        shellSort(A, size);
    else {
    	pivot = size / 2;
    	mergeSort(A, pivot);
    	mergeSort(A + pivot, size - pivot);
    	merge(A, pivot, size);
    }
}
