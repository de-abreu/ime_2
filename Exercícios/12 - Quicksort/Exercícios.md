# Respostas aos exercícios

## Exercícios 2

**4.** Conforme a seguinte implementação

```c
 01 | static int separa (int v[], int p, int r) {
 02 |	int c = v[r]; //pivô
 03 |	int t, j = p;
 04 |	for (int k = p; k < r; k++) {
 05 |		if (v[k] <= c) {
 06 |			t = v[j];
 07 | 			v[j] = v[k];
 08 |			v[k] = t;
 09 |			j++;
 10 |		}
 11 |		t = v[j];
 12 | 		v[j] = v[r];
 13 |		v[r] = t;
 14 |	}
 15 | }
```

Verifiquemos se os seguintes invariantes são verdadeiros:

1. $p \le j \le k$

O valor de $j$ é tido inicialmente na linha 03 como sendo igual a $p$, equivalente portanto também à $k$ tal qual este último é definido na linha 04. Para cada iteração da repetição `for` o valor de $k$ é incrementado, enquanto o valor de j neste mesmo loop é incrementado se, e somente se, a comparação posta pela linha 05 é tida verdadeira.

Sendo este o único ponto no algoritmo em que o valor de j é modificado tem-se que j pode assumir valores tais que $p \le j \le k$ apenas. $\blacksquare$

2. $v[p \dots j - 1] \le c$

Inicialmente, $j = p$, então $v[p \dots j - 1]$ compreende um conjunto vazio. Feita a primeira iteração, tem-se a manutenção do invariante para compreender o primeiro elemento da lista que, para a iteração seguinte, corresponde à posição `j - 1`. O mesmo processo se repete para cada repetição subsequente. $\blacksquare$

3. $v[j \dots k - 1] > c$

Inicialmente, $k = p$ e $j = p$, então $v[j \dots k - 1]$ compreende um conjunto vazio. Feita a primeira iteração, tem-se a manutenção do invariante para compreender o primeiro elemento da lista que, para a iteração seguinte, corresponde à posição `k - 1`. Se este for menor ou igual a $c$, $j = k$ e $v[j \dots k - 1]$ continua vazio. Senão, $j = k - 1$ e $v[j \dots k - 1]$ compreende mais este valor. O mesmo processo se repete para cada repetição subsequente. $\blacksquare$

4. $v[p \dots r]$ é uma permutação do vetor original.

O quickSort é um algoritmo de ordenação o qual não faz uso de memória auxiliar. Suas operações são feitas com base em substituições (linhas 6 à 13) sobre o vetor original. Assim o sendo, segue que o resultado desta operação produz, a cada etapa, uma permutação deste vetor.

**7.** Não. Isso pois o elemento aquele selecionado enquanto pivô é *sempre* posicionado no vetor ao final do processo de partição após valores maiores ou iguais a ele. Isso, ainda que ele possa ter figurado antes doutros elementos de mesmo valor.

## Exercícios 3

```
quicksort (v, 1, 6)
	quicksort (v, 1, 2)
		quicksort (v, 1, 0)
		quicksort (v, 2, 2)
	quicksort (v, 4, 6)
		quicksort (v, 4, 4)
		quicksort (v, 6, 6)
```
