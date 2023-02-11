#include <malloc.h>

typedef struct {
    int low, high;
} Interval;

Interval *newInterval(int low, int high) {
    Interval *i = malloc(sizeof(Interval));
    i->low = low;
    i->high = high;
    return i;
}

int binarySearch(int value, Interval **i, int size) {
    int index;

    if (size <= 0)
        return 0;
    index = size / 2;
    if (i[index]->low >= value)
        return binarySearch(value, i, index);
    index++;
    return index + binarySearch(value, i, size - index);
}

Interval *searchInterval(int value, Interval **i, int size) {
    int index = binarySearch(value, i, size);
    Interval *result = i[index];

    if (index >= size || value <= result->low || value >= result->high)
        return NULL;
    return result;
}
