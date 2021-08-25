#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isBin (long long int n) {
    while (n != 0) {
        if (n % 10 > 1)
            return 0;
        n /= 10;
    }
    return 1;
}

long long int toDec (int n) {
    int decimal = 0, pot = 1;
    while (n > 0) {
        decimal += n % 10 * pot;
        n /= 10;
        pot *= 2;
    }
    return decimal;
}

char * toHex(long long int n) {
    long long int dec;
    char * hex, * string;
    string = malloc (19 * sizeof(string));
    hex = malloc (19 * sizeof(hex));
    string[0] = '\0';

    do {
        dec = toDec(n % 10000);
        hex[0] = (char) (dec < 10) ? '0' + dec : 'A' + dec - 10;
        hex[1] = '\0';
        hex = strcat(hex, string);
        string = strcpy (string, hex);
        n /= 10000;
    } while (n > 0);

    return string;
}

int main () {
    long long int n;
    char div;

    printf("Este programa lê inteiros positivos em notação binária e os converte à notação hexacedimal. Digite zeros e uns, separados ou não entre si por espaço, e pressione ENTER para tê-los covertidos em uma notação hexadecimal:\n");

    do {
        if (!(scanf("%lld%c", &n, &div)) || n < 0 || !(isBin(n))) {
            printf("Valor inválido lido.\n");
            return 1;
        }
        printf("%lld → 0x%s\n", n, toHex(n));
    } while(div != '\n');
    return 0;
}
