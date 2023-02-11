#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct array{
    int *values;
    int size, buffer;
} Array;

Array * readArray () {
	int d, i = 0;
	char c;
	Array *A = malloc(sizeof(Array));

	A->buffer = 1;
	A->values = malloc(sizeof(int));
	do {
		if (!scanf(" %d", &d))
			continue;
		if (i == A->buffer - 1) {
			A->buffer *= 2;
			A->values = realloc(A->values, A->buffer * sizeof(int));
		}
		A->values[i++] = d;
	} while ((c = getchar()) != EOF && c != '\n');
	A->size = i;
	return A;
}

bool isSorted(int* A, int size) {
	if (size <= 1)
		return true;
	if (*A > *(A + 1))
		return false;
	return isSorted(A + 1, size - 1);
}

void insertIn (Array **A, int value) {
    int i;
    Array *B;

    if ((*A)->size + 1 > (*A)->buffer) {
        B = malloc(sizeof(Array));
        B->size = (*A)->size + 1;
        B->buffer = (*A)->buffer * 2;
        B->values = malloc(B->buffer * sizeof(int));

        for (i = 0; i < (*A)->size && (*A)->values[i] <= value; i++)
            B->values[i] = (*A)->values[i];
        B->values[i] = value;
        while(++i <= (*A)->size)
            B->values[i] = (*A)->values[i - 1];

        free(*A);
        *A = B;
    }
    else {
        for (i = (*A)->size - 1; i >= 0 && (*A)->values[i] > value; i--)
            (*A)->values[i + 1] = (*A)->values[i];
        (*A)->values[i + 1] = value;
        (*A)->size++;
    }
}

int main () {
    Array *A;
    int i, value;

    printf("This program evaluates if a sequence of integer values is sorted in crescent order and, if it is, allows for the insertion of a new integer value to it.\nType in a sequence of values separated by spaces and press ENTER: ");
    A = readArray();

    if (!isSorted(A->values, A->size)) {
        printf("Not sorted in crescent order.\n");
        return 1;
    }

    printf("Sorted in crescent order. Type a integer value to be added to it: ");
    if (!scanf(" %d", &value)) {
        printf("Not an integer\n");
        return 1;
    }

    insertIn(&A, value);

    printf("New sequence:\n");
    for (i = 0; i < A->size; i++)
        printf("%d ", A->values[i]);
    printf("\n");
    return 0;
}
