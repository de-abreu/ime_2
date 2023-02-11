**2.** Sim, em ambos os casos. Isso, em função dos loops redundantes nas linhas 8 e 9, respectivamente.

**3.** Não. Na eventualidade de haverem valores entre $q$ e $r$ os quais não foram transcritos ao vetor $w$ na linha 7, em função de a transcrição de $p$ a $q$ já ter sido encerrada ($i == q$), estes não serão incorporados deste ponto em diante.

**4.** A troca é sem efeito para o resultado final, mas o desempenho do algoritmo será pior em função da adição de uma comparação desnecessária (neste caso, a comparação $v[i] > v[j]$).

**5.** Sim, na verdade esse é o método de comparação do qual faço uso.

**6.** Não, deste modo será feita a inclusão de valores de $p$ à $q$, enquanto $v[i] <= v[j]$ e, em seguida, de $q$ à $r$, enquanto $v[j] <= v[i]$, sem que a inclusão destes se dê de forma intercalada, tal qual o problema exige.

**7.** Este while ocorre enquanto ambas as "metades" do vetor houverem valores a serem intercalados no vetor resultante $w$ os quais ainda não foram percorridos.

---

Feitos mas não salvos **8, 9, 10**

---

**12.** Sim, ela o é. O que não seria o caso fosse feita a alteração proposta, já que os valores repetidos posteriores (depositados nos endereços de $q$ a $r$, percorridos pelo contador $j$) seriam inseridos no vetor resultante antes de suas contrapartes anteriores (depositadas nos endereços $p$ a $q$, percorridas pelo contador $i$) em função da colocação da comparação "v[i] < v[j]" na linha 6.

**13.** Vide arquivo `merge_lists.c`

## Exercícios 3

**1.** Ao chegarmos a linha 2, necessariamente passamos pela verificação na linha 1, então temos:
$$
\begin{cases} p < r - 1\ (\text I)\\ \\\ q = \dfrac{p + r}2\ (\text{II}) \end{cases}
$$

Seja $f$ uma variável de "folga", $f \in \mathbb N, f \ge 1,$ tal que $p = r - 1 - f$, então

$$
q = \dfrac{p + p + f + 1}2 = p + \underbrace{\dfrac{f + 1}2}_{\ge 1} \implies q > p
$$

e

$$
q = \dfrac{r + r - f - 1}2 = r - \underbrace{\dfrac{f + 1}2}_{\ge 1} \implies q < r
$$

Logo, $p < q < r$. $\blacksquare$


**2.** Ao trocarmos `(p + r) / 2` por `(p + r - 1) / 2` o vetor ao ser recursivamente subdividido e eventualmente alcançar um tamanho $r - p = 2$ teremos, em função da divisão inteira:

$$
\displaystyle q = \frac{p + r - 1}2 = \frac{2p + 2 - 1}2 = p + \underbrace{\frac 12}_{= 0} = p
$$

Assim, nas duas próximas chamadas ao mergesort, teremos algo equivalente à `mergesort(p, p, v)` o que compreende nenhum elemento e `mergesort(p, r, v)`, o que compreende os mesmos dois elementos da atual invocação. Ou seja, temos uma recursão infinita. $\square$

A mesma situação não se observa para `(p + r + 1) / 2`. Seja $r = p + \text{tam}, \text{tam} \ge 2$ então

$$
\displaystyle q = \frac{p + r + 1}2 = \frac{2p + \text{tam} + 1}2 = p + \underbrace{\frac{\text{tam} + 1}2}_{\ge 1} \therefore p < q < r
$$

Assim, o vetor será sempre repartido em uma posição intermediária aos seus elementos, o que conduzirá o algoritmo a sua resolução. $\blacksquare$

**3.**
```c
mergesort(1,4, v)
	mergesort(1,2, v)
		mergesort(1,1, v)
		mergesort(2,2, v)
	mergesort(3,4, v)
		mergesort(3,3, v)
		mergesort(4,4, v)
```

**4.**
```c
void mergeSort (array A, int size) {
	int pivot;

	if (size <= 1)
		return;
	pivot = size / 2;
	mergeSort(A, pivot);
	mergeSort(A + pivot, size - pivot)
	merge(A, pivot, size);	
}
```

Temos que o tamanho do vetor é sempre maior que 1, e assim o pivô sempre assume um valor intermediário entre o tamanho do vetor (ou subvetor) e o início deste, subdividindo-o, (em porções menores até se alcançar o tamanho 1) e a intercalação de vetores é possível.

**5.** Sim ela o é tendo em vista que a comparação entre os elementos presentes no primeiro e segundo subvetores se dá por $A[i] <= A[j]$, onde $i < j$, o valor equivalente que se apresenta primeiro é inserido, também primeiramente, no vetor resultante.

**6.** Pode-se fazer uso da solução que apresentei anteriormente, no exercício quatro, fazendo-se uso de um único numerador.

**7.** Feito conforme exigência da disciplina de Introdução a Análise de Algoritmos.

## Exercícios 4

**1.** Não está correto pois o pivô foi deslocado em uma posição (`q + 1`) ao passá-lo a função intercala. Isso fará que o menor valor do segundo subvetor seja incluído no vetor resultante apenas após todos os valores do primeiro subvetor terem sido incluídos neste, o que pode incluir valores maiores que este. Por exemplo, para $1\ 3\ 5\ |\ 2\ 4\ 6$ teríamos um vetor resultante: $1\ 3\ 4\ 5\ 2\ 6$.

**2.** Não. Quando o subvetor alcança tamanho 1, este é subdivido em um subvetor de tamanho 0 e mais outro de tamanho 1, e assim indefinidamente.

**3.** Não, falamos sobre isso no exercício 2 do bloco anterior (3).

**4.** Não em ambos os casos. Para um vetor de tamanho 2 temos que $q = 0$, gerando dois vetores: um de tamanho nulo e outro de tamanho 2; e assim indefinidamente.

**5.** Definitivamente não. Podemos fazer uma demonstração de caso com o vetor $1\ 3\ 5\ 2\ 4\ 6$ para atestarmos isso. Este não será intercalado corretamente.

**6.** Sim, mas muito mais lentamente, em tempo quadrático.

**7, 8.** Feito.

## Exercícios 5

**1.**
```c
int c = 1							← T(1)
for (int i = 0; i < n; i *=2)		← T(n/2)
	for (int j = 1; j < n; j++)	← T(n)
		c += 1;						← T(1)
```

O tempo de execução em função de n é, portanto

$$
T \left(1 + n \cdot \frac n2 \cdot 1 \right) = T \left(\frac{n^2}2 + 1 \right)
$$

**2.** Feito no 

