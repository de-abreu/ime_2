#include <stdio.h>
#include <locale.h>
#include <wchar.h>

int main () {
    wchar_t a, b;

    setlocale(LC_CTYPE, "pt_BR.UTF-8");
    wprintf(L"Este programa lê dois caracteres e compara o valor destes na Tabela ASCII. Digite dois caracteres separados entre si por um espaço: ");
    wscanf(L"%lc %lc", &a, &b);
    if (a > b)
        wprintf(L"%lc (%d) > %lc (%d)\n", a, a, b, b);
    else if (a < b)
        wprintf(L"%lc (%d) > %lc (%d)\n", b, b, a, a);
    else
        wprintf(L"%lc (%d) = %lc (%d)\n", a, a, b, b);
    return 0;
}
