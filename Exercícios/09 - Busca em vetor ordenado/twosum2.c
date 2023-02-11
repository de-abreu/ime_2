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
    int pivot, first, last = binarySearch(sum, array, size);
    if (last == size)
        last--;
    pivot = first = 0;

    while (first < last) {
        if (array[first] + array[last] == sum)
            printf("%d + %d = %d\n", array[first++], array[last--], sum);
        else if (pivot == first) {
            first +=
                binarySearch(sum - array[last], array + first, last - first);
            pivot = last;
        } else {
            last = first + binarySearch(sum - array[first], array + first,
                                        last - first);
            pivot = first;
        }
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
