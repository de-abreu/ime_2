#include <stdio.h>
#include <stdlib.h>

int indexIsValue(int *array, int size) {
    int first = 0, pivot = size / 2;

    while (first < size) {
        if (array[pivot] == pivot)
            return pivot;
        if (array[pivot] < pivot)
            first = pivot + 1;
        else
            size = pivot;
        pivot = first + (size - first) / 2;
    }
    return -1;
}

int *char2int(char *args[], int size) {
    int i, *array = malloc(size * sizeof(int));

    for (i = 0; i < size; i++)
        array[i] = atoi(args[i + 1]);
    return array;
}

int main(int argc, char *argv[]) {
    int size = argc - 1, *array = char2int(argv, size);
    printf("%d\n", indexIsValue(array, size));
    free(array);
    return 0;
}
