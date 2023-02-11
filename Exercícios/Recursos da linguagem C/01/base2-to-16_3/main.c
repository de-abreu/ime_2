#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

int main () {
    char * bin = NULL;

    printf("Este programa lê um número natural em notação binária e o converte em notação hexadecimal. Digite uma série de uns e zeros, separados ou não entre si por espaços, e pressione ENTER para realizar a conversão:\n");

    switch (readBin(&bin)) {
        case EOF:
            printf("Valor inválido detectado\n");
        case 0:
            return 1;
    }

    printf("\nNotação hexadecimal: 0x%s\n", toHex(bin));
    return 0;
}
