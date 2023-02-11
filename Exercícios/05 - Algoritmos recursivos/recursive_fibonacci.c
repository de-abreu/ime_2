#include <stdio.h>

void printNext(int a, int b, int n) {
    if (n <= 0)
        return;
    printf("%d ", b);
    printNext(b, a + b, n - 1);
}

void fibonacci(int n) {
    printf("Sequência Fibonacci até o %dº elemento: 0 ", n);
    printNext(0, 1, n - 1);
    printf("\n");
}

int main() {
    int n;

    printf("Este programa calcula os valores até o enésimo número na sequência "
           "Fibonacci.\nDigite um valor inteiro n tal que n < 47: ");
    if (!scanf(" %d", &n) || n < 0 || n > 47) {
        printf("Valor inválido.\n");
        return 1;
    }
    fibonacci(n);
    return 0;
}
