#include <stdio.h>
#include <stdlib.h>
#define array int*

array readArray (int *size) {
	int i = 0;
	char c;
	array A;

	*size = 1;
	A = malloc(sizeof(int));
	do {
		if (!scanf(" %d", &A[i]))
			continue;
		if (i++ == *size - 1) {
			*size *= 2;
			A = realloc(A, *size * sizeof(int));
		}
	} while ((c = getchar()) != EOF && c != '\n');
	*size = i;
	return A;
}

void swap (int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void partition (array A, int size) {
    int i, j;

    for (i = j = 0; i < size; i++)
        if (A[i] < 0)
            swap(&A[i], &A[j++]);
}

int main () {
    array A;
    int i, size;

    printf("This program performs a partition of a list of integer values.\n"
    "Type in a sequence of values separated by spaces and press ENTER:\n");
    A = readArray(&size);
    partition(A, size);

    printf("New sequence:\n");
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
    return 0;
}
