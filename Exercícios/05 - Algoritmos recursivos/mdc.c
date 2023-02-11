#include <stdio.h>
#include <stdlib.h>

int mdc(int a, int b) {
    int r = a % b;
    return r ? mdc(b, r) : b;
}

int main(int argc, char *argv[]) {
    printf("%d\n", mdc(atoi(argv[1]), atoi(argv[2])));
    return 0;
}
