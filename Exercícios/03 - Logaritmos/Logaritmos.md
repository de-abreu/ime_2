# Logaritmos

## Exercícios 2

**1.** Prove os dois invariantes da primeira versão da função lg:

```c
int lg (int N)
{  
   int i, n;
   i = 0;
   n = 1;
   while (n <= N/2) {
      n = 2 * n;
      i += 1;
   }
   return i;    
}
```

Um invariante é uma propriedade a qual invariavelmente é verdadeira durante toda a execução de um *loop*, de tal forma que a corretude deste pode ser demonstrada se a invariante se mantêm verdadeira

- antes da iteração inicial ($i = 0$),

- para cada iteração subsequente (se verdadeira em $i = k$, também o é para $i = k + 1$)

- e ao término do *loop* ($i = n$, onde $n$ é o valor de parada)

Para o algoritmo acima, seja $N \in \N$, temos como invariantes que $n \le N$ e $i = \log_2n$.

**Prova**

Para $n$ temos:

- **Inicialização:** Para $N = 1$, $n_0 = 1$, então $n_0 \le N$.

- **Manutenção:** Para $N = k$ na iteração $x$, $x > 0$, assumimos $n_x \le k/2$. Ai para iteração $x + 1$ temos que o valor de $n_{x + 1} = 2n_x$. Como $n_x \le k/2$, tem-se que $n_{x + 1} \le k$, ou seja, $n_{x + 1} \le N$.

- **Término:** Para se encerrar na iteração $x$ tem-se que $n_x > N/2$ seja porque $n = N = 1$ ou, senão, porque $n_x > N \div 2$ quando $n_{x - 1} \le N/2$. No primeiro caso nada resta a demonstrar, mas no segundo caso segue que  $n_x = 2n_{x - 1}$, então

$$
n_{x - 1} \le N/2 \stackrel{\times 2}{\implies} 2n_{x - 1} \le N \implies n_x \le N
$$

Para $i$ temos:

- **Inicialização:** Para $N = 1$, $n_0 = 1$ e $i_0 = 0$, então $i_0 = \log_2 n_0$.

- **Manutenção:** Para $N = k$ na iteração $x$ assumimos que $n_x \le k/2$ e $i_x = \log n_x$, para a iteração $x + 1$ temos que o valor de $n_{x+1} = 2n_x$ e $i_{x+ 1} = i_x + 1$. Logo,
  
  $$
  \log_2n_{x + 1} = \log_22n_x = \log_2n_x + \log_22
= i_x + 1 = i_{x + 1}
  $$

- **Término:** Para se encerrar na iteração $x$ tem-se que $n_x > N/2$ seja porque $n = N = 1$ ou, senão, porque $n_x > N \div 2$ quando $n_{x - 1} \le N/2$. No primeiro caso $i = 0$  nada resta a demonstrar, mas no segundo caso segue que  $n_x = 2n_{x - 1}$ e $i_{x - 1} = \log_2n_{x - 1}$, então

$$
\log_2n_x = \log_22n_{x - 1} = \log_2n_{x - 1} + \log_22
= i_{x - 1} + 1 = i_x
$$

**2.** Invariantes: $1 \le n \le N$ e $i \le \log_2N$. A demonstração é análoga a anterior. Pode ser feita aqui subsequentemente havendo tempo.

**3.** Vide `lg.c`

**4.** O que faz a função abaixo? Escreva o invariante que explica a função.

```c
int tlg (int N) {  
   int i = 0, n = 1;
   while (n < N) {
      n *= 2;
      i += 1;
   }
   return i; 
}
```

Essa é a função que apresenta o resultado de $\lceil \log_2N \rceil$. Os invariantes são $n < 2N$ e $i = \log_2 n$.

**5.** O que é o *teto* de um número real $r$?  Se $R$ é um número estritamente positivo, qual a relação entre o teto de  $log_{10} R$  e  $R$?  Escreva uma função recursiva que receba um número inteiro estritamente positivo $N$ e devolva o teto de $log_{10} N$.

O menor número inteiro $i$ tal que $i \ge r$. O teto do $\log_{10}R$ fornece o número de dígitos necessários a representar a parte inteira de $R$ em números decimais. Vide `lg.c`.

## Exercícios 3

1. Sim.

2. Vide `overflow.c`

3. 


