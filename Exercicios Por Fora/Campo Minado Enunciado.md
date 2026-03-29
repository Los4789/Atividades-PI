**O Desafio: O Radar do Campo Minado**
Você foi contratado para programar o sistema de dicas de um jogo de Campo Minado. O seu programa vai receber um mapa contendo bombas e espaços vazios. O seu objetivo é imprimir o mesmo mapa, mas substituindo os espaços vazios pela quantidade de bombas que existem ao redor daquele espaço (nas 8 direções: cima, baixo, esquerda, direita e as 4 diagonais).

**Entrada:**

A primeira linha contém dois números inteiros M e N (máximo de 100), representando as linhas e colunas do mapa.

As próximas M linhas contêm strings de tamanho N.

O caractere * (asterisco) representa uma bomba.

O caractere - (hífen) representa um espaço vazio.

**Saída:**

Imprima a matriz resultante. As bombas (*) devem continuar no mesmo lugar. Os espaços vazios (-) devem ser substituídos por um número de 0 a 8, indicando quantas bombas existem encostadas nele.

**Exemplo**

Entrada:

3 4
*---
--*-
*---

Saída:

*211
23*1
*211
(Dica visual do exemplo: O espaço na Linha 1, Coluna 1 resultou em 3 porque ele tem a bomba de cima-esquerda, a bomba de baixo-esquerda, e a bomba encostada na direita dele).
