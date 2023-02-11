#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int *array, int pivot, int size) {
    int i, j;

    swap(array + pivot, array + --size);
    for (i = j = 0; i < size; i++)
        if (array[i] <= array[size])
            swap(array + i, array + j++);
    swap(array + i, array + j);
    return j;
}

int quickSelect(int *array, int size, int i) {
    int pivot;

    if (size <= 1)
        return *array;
    pivot = partition(array, i, size);
    if (pivot == i)
        return array[i];
    if (i < pivot)
        return quickSelect(array, size, i);
    pivot++;
    return quickSelect(array + pivot, size - pivot, i - pivot);
}

int *createArray(int size) {
    int i, *array = malloc(size * sizeof(int));

    for (i = 0; i < size; i++)
        array[i] = rand();
    return array;
}

int max(int *array, int size) {
    int m;

    if (!size)
        return INT_MIN;
    m = max(array + 1, size - 1);
    return (m > *array) ? m : *array;
}

void printArray(int *array, int size) {
    int i;

    printf("Array's contents: ");
    for (i = 0; i < size; i++)
        printf(" %d", array[i]);
    printf("\n");
}

int main() {
    int *array, size;
    printf("This program evaluates the correctness of a function to get the "
           "maximum value in an array by using another function that is much "
           "more complex and prone to error in its implementation (albeit it "
           "executes much faster): the quick select. Let's see how that "
           "goes.\n\nFirst we generate an array containing randomly generated "
           "values. Choose a size for that array: ");
    scanf(" %d", &size);
    if (size < 0) {
        printf("Invalid size.\n");
        return 1;
    }
    array = createArray(size);
    printArray(array, size);
    printf("The maximum function indicates the maximum value is: %d\n",
           max(array, size));
    printf("While the quick select says it is: %d\n",
           quickSelect(array, size, size - 1));
    return 0;
}
