#include <stdio.h>
#include <stdlib.h>

void flushInput() {
    int c;
    if ((c = getchar()) != '\n' && c != EOF)
        flushInput();
}

int *resizeArray(int *array, int *buffer) {
    *buffer *= 2;
    return realloc(array, *buffer * sizeof(int));
}

int *readInput(int *size, int *buffer) {
    int i, value, *array = NULL;
    *buffer = 1;

    for (i = 0; scanf(" %d", &value); array[i++] = value)
        if (i == *buffer - 1)
            array = resizeArray(array, buffer);
    flushInput();
    *size = i;
    return array;
}

void shift(int *array, int start, int end, int increment) {
    if (start == end)
        return;
    array[start] = array[start + increment];
    shift(array, start + increment, end, increment);
}

int pop(int **array, int index, int *size) {
    int value;

    if (index >= *size || index < 0)
        return EOF;
    value = (*array)[index];
    if (index > *size - index)
        shift(*array, index, *size - 1, 1);
    else
        shift((*array)++, index, 0, -1);
    (*size)--;
    return value;
}

int *insert(int value, int index, int *array, int *size, int *buffer) {
    if (index > *size) {
        printf("Invalid index: index not in range 0 to %d", *size);
    } else {
        if (*size == *buffer - 1)
            array = resizeArray(array, buffer);
        shift(array, (*size)++, index, -1);
        array[index] = value;
    }
    return array;
}

int iteractiveRemoveZeroes(int *array, int size) {
    int i, j;
    for (i = j = 0; j < size; j++)
        if (array[j] != 0)
            array[i++] = array[j];
    return i;
}

int removeZeroes(int *array, int size) {
    int pivot;

    if (size == 0)
        return 0;
    pivot = removeZeroes(array, --size);
    if (array[size] != 0)
        array[pivot++] = array[size];
    return pivot;
}

void printArray(int *array, int size) {
    int i;

    for (i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int main() {
    int value, index, size, buffer, *array;

    printf("This program tests the functionality of functions to insert and "
           "remove content of an array. Type in a sequence of numbers ended "
           "with \".\" and press enter: ");
    array = readInput(&size, &buffer);

    printf("Select an index to insert a value: ");
    scanf(" %d", &index);
    printf("Select a value to be inserted: ");
    scanf(" %d", &value);
    array = insert(value, index, array, &size, &buffer);
    printf("Resulting array: ");
    printArray(array, size);

    printf("Select an index to remove a value: ");
    scanf(" %d", &index);
    printf("Value removed: %d\nResulting array:", pop(&array, index, &size));
    printArray(array, size);

    size = removeZeroes(array, size);
    printf("With all null elements removed, the resulting array is:\n");
    printArray(array, size);

    return 0;
}
