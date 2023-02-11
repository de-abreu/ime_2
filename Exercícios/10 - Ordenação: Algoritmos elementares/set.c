#include <malloc.h>

int *set(int *orderedArray, int size, int *count) {
    int i, *result = malloc(size * sizeof(int));
    *result = *orderedArray;

    for (i = *count = 1; i < size; i++)
        if (orderedArray[i] != orderedArray[i - 1])
            result[*count++] = orderedArray[i];
    return result;
}
