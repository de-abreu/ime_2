#include <stdlib.h>
#include <string.h>

int binarySearch(char *string, char **array, int size) {
    int index;

    if (size <= 0)
        return 0;
    index = size / 2;
    if (strcmp(string, array[index]) <= 0)
        return binarySearch(string, array, index);
    index++;
    return index + binarySearch(string, array + index, size - index);
}
