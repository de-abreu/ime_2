#include <stdio.h>

void invertWord(char *c) {
    if (!*c)
        return;
    invertWord(c + 1);
    printf("%c", *c);
}

int main(int argc, char *argv[]) {
    int i;

    for (i = 1; i < argc; i++) {
        invertWord(argv[i]);
        printf(" ");
    }
    printf("\n");
    return 0;
}
