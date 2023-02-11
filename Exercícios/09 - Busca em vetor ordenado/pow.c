#include <stdio.h>
#include <stdlib.h>

int power(int base, int exp) {
    int sqrt;

    if (exp == 0)
        return 1;
    if (exp == 1)
        return base;
    sqrt = power(base, exp / 2);
    return sqrt * sqrt * (exp % 2 ? base : 1);
}

int main(int argc, char *argv[]) {
    printf("%d\n", power(atoi(argv[1]), atoi(argv[2])));
    return 0;
}
