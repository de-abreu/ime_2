#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

int main () {
    int i, a, b, size = 1;
    wchar_t c, * str;
    str = malloc(sizeof(str));

    setlocale(LC_CTYPE, "pt_BR.UTF-8");
    wprintf(L"Este programa lê duas sequências de texto terminada com ENTER e conta quantas vezes a segunda sequência de texto ocorre na primeira.\n");

    wprintf(L"\nEscreva algo: ");
    for (i = 0; (c = getwchar()) != WEOF && c != '\n'; i++) {
        if (i == size - 1) {
            size *= 2;
            str = realloc(str, size * sizeof(str));
        }
        str[i] = c;
    }
    str[i] = '\0';

    wprintf(L"\nDigite dois valores inteiros e positivos a e b separados por espaço, onde 0 <= a <= b <= %d, para demarcar a seleção da sequência de texto: ", i - 1);
    wscanf(L"%d %d", &a, &b);
    if (!(a >= 0 && b >= a && b < i)) {
        wprintf(L"Valores inválidos passados.\n");
        return 1;
    }

    wprintf(L"\nTexto selecionado:\n%ls\n", substr(str, a, b));
    return 0;
}
