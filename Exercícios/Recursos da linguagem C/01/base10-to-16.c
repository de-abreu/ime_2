#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * toChar(int n) {
    char * str;
    str = malloc(sizeof(str));
    str[0] = (char) (n < 10) ? '0' + n : 'A' + n - 10;
    str[1] = '\0';
    return str;
}

char * toHex(long long int n) {
    int r = n % 16;
    if (n - r == 0)
        return toChar(n);
    return strcat(toHex((n - r) / 16), toChar(r));
}

int main () {
    long long int n;
    char div;

    printf("Este programa lê inteiros positivos em notação decimal e os converte à notação hexacedimal. Digite quaisquer números naturais separados entre si por espaço e pressione ENTER para tê-los convertidos:\n");

    do {
        if (!(scanf("%lld%c", &n, &div)) || n < 0) {
            printf("Valor inválido lido.\n");
            return 1;
        }
        printf("%lld → 0x%s\n", n, toHex(n));
    } while(div != '\n');
    return 0;
}
