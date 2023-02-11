# Ordenação: algoritmos elementares

> Resolução dos exercícios propostos

## Exercícios 1

**1.** Vide arquivo `isSorted.c` nesta pasta.

**2.** O algoritmo proposto, descrito abaixo, é adequado a verificação da ordenação crescente.

```c
int verifica (int v[], int n) {
   if (n > 1) 
      for (int i = 1; i < n; i++) 
         if (v[i-1] > v[i]) return 0; 
   return 1; }
```

- Caso base: um ou nenhum elemento. Um arranjo nestas condições está trivialmente ordenado em ordem crescente, não há necessidade que comparações de valores sejam feitas. O algoritmo verifica se este é o caso na linha 2 e, este sendo, pula as comparações e retorna verdadeiro (1) na linha 5.

- Para $n > 1$: A repetição descrita na linha 3 faz com que na linha três cada valor do arranjo do segundo ao último seja comparado ao seu antecessor imediato, interrompendo a verificação e retornando falso (0) assim que um antecessor de maior valor é encontrado. Doutra forma o algoritmo procede e retorna verdadeiro na linha 5.

**3.** O algoritmo proposto, descrito abaixo, é inadequado a verificação da ordenação crescente.

```
int verifica (int v[], int n) {
   int sim;
   for (int i = 1; i < n; i++) 
      if (v[i-1] <= v[i]) sim = 1;
      else {
         sim = 0;
         break; }
   return sim; }
```

No caso base $n >= 1$, o que faz com que a repetição com a verificação nunca ocorra. Ora, mas apenas pela verificação a variável `sim` é designada um valor (1) verdadeiro ou (0) falso. Assim, ao executar este algoritmo com um arranjo trivialmente ordenado o seu resultado é imprevisível: ele retornará qualquer valor que esteja armazenado na posição de memória alocada para armazenar o valor da variável `sim`.
**4.** Vide arquivo `Sorts.c` na pasta da disciplina de Análise de Algoritmos e Estruturas de Dados I.

**5.** Vide arquivo `isSorted.c` nesta pasta.

## Exercícios 2
**1.** Vide arquivo `sorts.c` na pasta da disciplina de Análise de Algoritmos e Estruturas de Dados I.

**2.** Continua, entretanto a função perderá sua propriedade de _estabilidade_, isso é, os valores iguais não aparecerão na mesma ordem quem que foram inseridos (estes figurarão em ordem reversa). Para ordenar valores inteiros isso não é de maior consequência senão por mais algumas comparações desnecessárias, mas quando estes valores são chaves para a ordenação de estruturas de dados, isso pode ser indesejável.

**3.**

**a)** Esta modificação não alterará o resultado, apenas adicionará uma repetição do loop descrito na linha 3 onde o valor em `v[j]` é copiado à `x` e em seguida sobrescrito à `v[j]`, pois nestas condições $i + 1 = j$.

**b)** Esta modificação comprometerá a funcionalidade do algoritmo. Fazendo com que o valor em `v[j]` seja armazenado uma posição antes do que deveria, possivelmente extrapolando o limite inferior do arranjo.

**4.** As consequências para a alteração

```diff
6,7c5
<    v[i+1] = x;
< }
---
 >       v[i] = x; } }
\ No newline at end of file
 >   
```

São discutidas no item **b)** do exercício anterior.

**5.** Esta versão não alterará o resultado final do algoritmo, mas realizará um número maior de atribuições para alcançá-lo, o que prejudica seu desempenho.

**6.** Sim, a única diferença deste modelo com o algoritmo anteriormente descrito é o uso de um loop `while` em vez de um `for`. Assim, o invés de constar em uma única linha, temos que o contador é inicializado na linha 3, a condição de repetição na linha 4 e a incrementação do contador se dá na linha 6.

**7.** Vide o arquivo `backwards_insertion_sort.c`

**8.** Mas, isso pressupõe um vetor já ordenado. O resultado de se realizar esta operação terminaria por manter o vetor embaralhado.

**9.** O pior caso corresponde a qualquer instância em que os valores do vetor encontram-se ordenados em ordem decrescente. Assim, para um vetor de tamanho $n$ as comparações feitas ao final encontram-se em progressão aritmética:

$$1 + 2 + \dots + n - 1 = \dfrac{(n - 1)(n - 1 + 1)}2 = \dfrac{n^2 - n}2 \equiv O(n^2) $$

**10.** O melhor caso é aquele em que os valores já encontram-se em ordem crescente. Assimpara um vetor de tamanho $n$ cada valor desde o segundo ao último é comparado com seu antecessor uma única vez, um total de $n - 1 \equiv O(n)$ comparações realizadas .

**11.** No pior caso, todas as comparações levam à movimentação de dados, portanto, são $\frac{n^2 - n}2$ movimentações no total. No melhor caso, também. Neste os dados são copiados a uma variável temporária e em seguida sobrescritos sobre a posição donde advieram, totalizando $n - 1$ movimentações.

**12.** Vide o arquivo `backwards_insertion_sort.c`.

**13.**

**14.** Vide o arquivo `descrescent_insertion_sort.c`

## Exercícios 3

**1.** Vide arquivo `sorts.c` na pasta da disciplina de Análise de Algoritmos e Estruturas de Dados I.

**2.**

**a)** O primeiro elemento da lista não é ordenado.

**b)** Acrescenta-se uma repetição desnecessária, já que não à outro elemento com que comparar com o elemento final do vetor.

**3.** Sim, está correta, mas o algoritmo perde sua estabilidade. Elementos de mesmo valor são ordenados na ordem reversa daquela em que figuraram originalmente no vetor.

**4, 5 e 6.** Em ambos o melhor e o pior caso, o mesmo número de comparações são feitas, $\frac{n^2 - n}2$ o que diferencia estes dois casos é o número de movimentações feitas: respectivamente, $n - 1$ (os dados são copiados a uma variável temporária e em seguida sobrescritos sobre a posição donde advieram) e $\frac{n^2 - n}2$ (o último elemento vai para a primeira posição, o penúltimo a segunda, e assim por diante).

**7.** Vide o arquivo `descrescent_selection_sort.c`
## Exercícios 4
**1.** Vide o arquivo `string_insertion_sort.c`
**2.** Vide o arquivo `string_radix_sort.c`
**3 e 4.** Vide o arquivo `data_sort.c`


