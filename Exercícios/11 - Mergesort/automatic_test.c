#include "./merge_shell_sort.c"
#include <limits.h>

int main () {
    int i = 0, size, index;
	array A;

	if (!scanf(" %d", &size) || size < 1 || size > INT_MAX) {
		printf("Tamanho inválido: não se encontra desde 1 a %d.\n", INT_MAX);
		return 1;
	}
	A = malloc(size * sizeof(int));
	while (i < size && scanf(" %d", A + i))
		i++;
	if (i < size) {
		printf("Lista mal formatada: apenas %d valores foram encontrados.\n", i);
		return 1;
	}
	if (!scanf(" %d", &index) || index < 1 || index >= size) {
		printf("Índice invalido: não se encontra desde 1 a %d.\n", size);
		return 1;
	}

	mergeSort(A, size);
	printf("O %dº elemento de menor valor: %d\n", index, A[index - 1]);
	free(A);
    return 0;
}
