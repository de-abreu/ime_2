#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

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

void twoSum(int sum, int *array, int size) {
    int i, j;
    int last = binarySearch(sum, array, size);
    int mid = binarySearch(sum / 2, array, last);
    if (last == size)
        last--;
    for (i = ++mid; i <= last; i++) {
        j = binarySearch(sum - array[i], array, mid);
        mid = j + 1;
        if (array[j] + array[i] == sum)
            printf("%d + %d = %d\n", array[j], array[i], sum);
    }
}

int *char2int(char *args[], int size) {
    int i, *array = malloc(size * sizeof(int));

    for (i = 0; i < size; i++)
        array[i] = atoi(args[i + 2]);
    return array;
}

int main(int argc, char *argv[]) {
    int size = argc - 2, *array = char2int(argv, size);

    twoSum(atoi(argv[1]), array, size);
    free(array);
    return 0;
}
