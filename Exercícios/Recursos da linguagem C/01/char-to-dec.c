#include <stdio.h>
#include <locale.h>
#include <wchar.h>

int main () {
    wchar_t c;

    setlocale(LC_CTYPE, "pt_BR.UTF-8");
    wprintf(L"Este programa lê um texto terminado com ENTER e mostra o valor de cada caractere neste na tabela ASCII. Escreva algo:\n");

    while ((c = getwchar()) != WEOF && c != '\n') {
        wprintf(L"%03d | %c\n", (int) c, c);
    }
    wprintf(L"%-03d | %s\n", 10, "ENTER");
    return 0;
}
