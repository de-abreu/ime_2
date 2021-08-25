#include <stdio.h>
#include <locale.h>
#include <wchar.h>

int main () {
    wchar_t c, div;

    setlocale(LC_CTYPE, "pt_BR.UTF-8");
    wprintf(L"Este programa lê uma sequência de números inteiros positivos, maiores que 31 e menores que 256, separados por espaço, e os corresponde a caracteres na tabela ASCII. Liste-os e pressione ENTER:\n");

    do {
        scanf("%d%lc", &c, &div);
        wprintf(L"%03d | %c\n", (int) c, c );
    } while(div != '\n');
    return 0;
}
