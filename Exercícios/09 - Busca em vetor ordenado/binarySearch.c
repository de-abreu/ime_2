#include <stdio.h>
#include <stdlib.h>

// Return an index x from an array a such that for a given value v the following
// condition is satisfied: a[x - 1] < v ≤ a[x]. As such, if we consider *(array
// + size) = ∞ (or INT_MAX for that matter) and *(array - 1) = -∞ (or INT_MIN)
// it is true for each interaction of this function that *array < value ≤
// *(array + size).

int binarySearch(int value, int *array, int size) {
    int index;

    if (size <= 0)
        return 0;
    index = size / 2;
    if (array[index] >= value)
        return binarySearch(value, array, index);
    index++;
    return index + binarySearch(value, array + index, size - index);
}

int *char2int(char *args[], int size) {
    int i, *array = malloc(size * sizeof(int));

    for (i = 0; i < size; i++)
        array[i] = atoi(args[i + 2]);
    return array;
}

int main(int argc, char *argv[]) {
    int size = argc - 2;
    printf("Index: %d\n",
           binarySearch(atoi(argv[1]), char2int(argv, size), size));
    return 0;
}
