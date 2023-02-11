#include <stdio.h>
#include <string.h>

int getValue(char *varName) {
    int i = -1;

    printf("Type in a value to %s: ", varName);
    scanf(" %d", &i);
    return i;
}

int flg(int n, int base) { return (n > 1) ? flg(n / base, base) + 1 : 0; }

int clg(int n, int base) {
    return flg(n, base) + ((n > base && n % base > 0) ? 1 : 0);
}

int main() {
    int n, b;
    char option[8];

    printf("This program calculates the floor or ceiling of the logarithm of n "
           "with a "
           "base of b, n and b being natural numbers, and b > 2.\n");

    if ((n = getValue("n")) < 1) {
        printf("Invalid value for n: not a natural number\n");
        return 1;
    }
    if ((b = getValue("b")) < 2) {
        printf("Invalid value for b: not a valid logarithm base\n");
        return 1;
    }

    printf("Which would you like to calculate? The [f]loor or [c]eiling? ");
    scanf("%7s", option);
    if (!strcmp("f", option) || !strcmp("floor", option))
        printf("%d\n", flg(n, b));
    else if (!strcmp("c", option) || !strcmp("ceiling", option))
        printf("%d\n", clg(n, b));
    else {
        printf("Invalid option: \"%s\"\n", option);
        return 1;
    }
    return 0;
}
