#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void clearJunk(char *c) {
    *c = getchar();
    if (!isdigit(*c))
        clearJunk(c);
}

char *readNumber(int *n) {
    int i = 0, size = 1;
    char c, *number = malloc(sizeof(char));
    errno = INT_MAX;

    clearJunk(&c);
    while (isdigit(c)) {
        if (i == size - 1) {
            size *= 2;
            number = realloc(number, size * sizeof(char));
        }
        number[i++] = c;
        c = getchar();
    }
    number[i] = '\0';
    *n = strtoimax(number, NULL, 10);
    return number;
}

int main() {
    char *number;
    int n;

    printf("This piece of code detects if the square power of a number "
           "produces an overflow, otherwise it is printed normaly.\nType in a "
           "number to test it: ");
    number = readNumber(&n);
    if (n > INT_MAX / n)
        printf("%s ⨉ %s produces an overflow.\n", number, number);
    else
        printf("%d ⨉ %d = %d\n", n, n, n * n);
    return 0;
}
