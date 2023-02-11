# Bytes, números e caracteres

## Exercícios 1

**1.** Mostre que todo número natural pode ser escrito em notação binária.

Por notação binária admitimos números compostos unicamente por dígitos 0 e 1, tal que o dígito 1 representa a ocorrência de uma distinta potência de 2 (a base, também denominada "base 2") em um somatório. Por exemplo:

$$
0101_2 \equiv 0 \times 2^3 + 1 \times 2^2 + 0 \times 2^1 + 1 \times 2^0 = 5_{10}
$$

Provemos por indução forte que para cada $n \in \mathbb N$ é possível sua representação em forma binária.

1. Base de indução

$0_2 = 0 \times 2^0 \equiv 0$ e $1 = 1 \times 2^0 \equiv 1_{10}$.

2. Hipótese de indução

Sejam $n, m \in \mathbb N$, $0 \le m < n$ números naturais que, tais quais aqueles em nossa base de indução, podem ser representados por números binários. Se $n$ pode ser representado enquanto número binário, $n + 1$ também deve poder.

3. Passo de indução

O número $n + 1$ pode ser par ou ímpar e, portanto, pode ser representado enquanto $2m$ ou $2m + 1$. Sabemos que $m$ é um número da forma $1 \times 2^k + \dots + 1 \times 2^0$ ou $1 \times 2^k + \dots + 0 \times 2^0$, $k \in \mathbb N$. Logo,

- se $n = 2m$: $n = 1 \times 2^{k + 1} + \dots + 1 \times 2^1 + 0 \times 2^0$, ou $n = 1 \times 2^{k + 1} + \dots + 0 \times 2^1 + 0 \times 2^0$, um número passível de representação binária. $\square$

- se $n = 2m + 1$: $n = 1 \times 2^{k + 1} + \dots + 1 \times 2^1 + 1 \times 2^0$, ou $n = 1 \times 2^{k + 1} + \dots + 0 \times 2^1 + 1 \times 2^0$, outro número passível de representação binária. $\blacksquare$

**2.** Mostre que $2^k + 2^{k − 1} + \dots + 2^1 + 2^0 = 2^{k + 1} −1$, qualquer que seja o número natural $k$.

1. Base de indução

Seja $k = 0$, então:

$\displaystyle \sum^k_{i = 0} 2^i = \sum^0_{i = 0} 2^i = 2^0 = 1 = 2^1 - 1$

2. Hipótese de indução:

Se $\displaystyle \sum^k_{i = 0} 2^i = 2^{k + 1} - 1$ para todo $k \in \mathbb N$, então também $\displaystyle \sum^{k + 1}_{i = 0} 2^i = 2^{k + 2} - 1$.

3. Passo de indução:

$\displaystyle \sum^{k + 1}_{i = 0} 2^i = \sum^k_{i = 0} 2^i + 2^{k + 1} = 2^{k + 1} - 1 + 2^{k + 1} = 2 \cdot 2^{k + 1} - 1 = 2^{k + 2} - 1\ \blacksquare$

**3.** Escreva os números $2^8$, $2^8 −1$, $2^{16}$, $2^{16} − 1$, $2^{32}$ e $2^{32} − 1$ em notação hexadecimal.

São os dígitos da base hexadecimal: 0 1 2 3 4 5 6 7 8 9 A B C D E F

- $2^8_{10} \equiv 10_{16}$
- $(2^8 - 1) \equiv \text F_{16}$
- $2^{16}_{10} \equiv 100_{16}$
- $(2^{16} - 1)_{10} \equiv \text{FF}_{16}$
- $2^{32}_{10} \equiv 1000_{16}$
- $(2^{32} - 1)_{10} \equiv \text{FFF}_{16}$

## Exercícios 2

**1.** Complemento de $n$.  Mostramos acima como a notação complemento-de-dois transforma em um inteiro negativo qualquer sequência de $s$ bytes que começa com um bit 1. Agora considere a operação inversa. Dado um inteiro n no intervalo $−2^{8s−1} \dots −1$, mostre que a sequência de $s$ bytes que representa $n$ em notação complemento-de-dois é a mesma sequência de bytes que representa $n + 2^{8s}$ em notação binária.

Seja $n$ um número inteiro negativo equivalente à $-m$. O número $m$ em notação binária de complemento-de-dois tem seu negativo com representação equivalente àquela de $m - 2^{8s}$. Logo, tem-se que:

$$
m_2 \equiv (m - 2^{8s}) \stackrel{\times -1}{\implies}
(-m)_2 \equiv (-m + 2^{8s}) \stackrel{n\ =\ -m}{\implies}
n_2 \equiv (n + 2^{8s})_2\ \blacksquare
$$

**2.** Complemento-de-dois.  A notação complemento-de-dois transforma qualquer sequência de $s$ bytes que começa com um bit 1 em um inteiro negativo. Agora considere a operação inversa. Suponha que $n$ é um inteiro no intervalo $−2^{8s−1} \dots −1$. Tome a sequência de bits que representa o valor absoluto de $n$ em notação binária, complemente todos os bits (ou seja, toque 0 por 1 e 1 por 0), e some 1, em binário, ao resultado. Mostre que essa operação produz a sequência de $s$ bits que representa n em notação complemento-de-dois.