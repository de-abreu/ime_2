#include <stdlib.h>
#include <stdio.h>
#define array int*

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

void swap (int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void shuffle(array A, int size) {
    if (--size < 1)
        return;
    swap(&A[rand() % size], &A[size]);
    shuffle(A, size);
}

int main () {
    array A;
    int i, size;

    printf("This program shuffles integer values according to the "
           "Fisher-Yates algorithm.\nType in a sequence of values separated "
           "by spaces and press ENTER:\n");
    A = readArray(&size);
    shuffle(A, size);

    printf("\nNew sequence:\n");
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
    return 0;
}
