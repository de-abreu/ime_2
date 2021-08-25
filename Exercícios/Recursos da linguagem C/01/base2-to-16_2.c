#include <stdio.h>
#include <stdlib.h>

typedef struct array {
    int i, size;
    char * index;
} number;

int main () {
    short int value, add;
    char c;
    number bin, hex;

    printf("Este programa lê um número natural em notação binária e o converte em notação hexadecimal. Digite uma série de uns e zeros, separados ou não entre si por espaços, e pressione ENTER para realizar a conversão:\n");

    /* Read binary number */
    bin.i = 0;
    bin.size = 4;
    bin.index = malloc(4 * sizeof(bin.index));
    while ((c = getchar()) != EOF && c != '\n') {
        if (c == ' ')
            continue;
        if (c != '0' && c != '1') {
            printf("Valor inválido detectado\n");
            return 1;
        }
        if ((bin.i + 1) == bin.size) {
            bin.size += 2;
            bin.index = realloc(bin.index, bin.size * sizeof(bin.index));
        }
        bin.index[bin.i] = c;
        bin.i++;
    }
    if (bin.i < 1)
        return 1;

    /* Conversion algorithm */
    hex.i = bin.i / 4;
    hex.i += (bin.i % 4 > 0) ? 1 : 0;
    hex.index = malloc(hex.i * sizeof(hex.index));
    hex.index[hex.i] = '\0';
    for (hex.i--; hex.i >= 0; hex.i--) {
        value = 0;
        for (add = 1; add < 9; add *= 2) {
            bin.i--;
            if (bin.index[bin.i] == '1')
                value += add;
            if (bin.i == 0)
                break;
        }
        hex.index[hex.i] = (char) (value < 10) ? '0' + value : 'A' + value - 10;
    }

    printf("\nNotação hexadecimal: 0x%s\n", hex.index);
    return 0;
}
