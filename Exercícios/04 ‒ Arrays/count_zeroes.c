#include <stdio.h>

int countZeroes(long number, int currentCount) {
    if (number == 0)
        return currentCount;
    return countZeroes(number / 10, currentCount) + ((number % 10) ? 0 : 1);
}

void printMostZeroes(long max, int maxCount) {
    long current;
    int currentCount = 0;

    if (!scanf(" %ld", &current)) {
        if (!maxCount)
            printf("There are no numbers containing zeroes in the sequence "
                   "provided.\n");
        else
            printf(
                "The number with the longest sequence of zeroes is %ld, with "
                "%d zeroes in total.\n",
                max, maxCount);
        return;
    }

    currentCount = (!current) ? 1 : countZeroes(current, currentCount);
    if (currentCount > maxCount)
        printMostZeroes(current, currentCount);
    else
        printMostZeroes(max, maxCount);
}

int main() {
    printf("This program counts the number of following zeroes in an array of "
           "numbers and yields a number with the greatest number of them. "
           "Type in a series of numbers ended with '.' and press ENTER:\n");
    printMostZeroes(0, 0);
    return 0;
}
