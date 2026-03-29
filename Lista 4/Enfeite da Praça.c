#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_ALTURA 200
#define MAX_LARGURA 200

int EspacoValido(int Linha, int Coluna, int m, int n, char Praca[MAX_ALTURA][MAX_LARGURA]) {
    if (Linha >= 0 && Linha < m && Coluna >= 0 && Coluna < n) {
        if (Praca[Linha][Coluna] == '-' || Praca[Linha][Coluna] == 'x') {
            return 1;
        }
    }
    return 0;
}

int main() {
    char Praca[MAX_ALTURA][MAX_LARGURA];
    int m, n;
    int i, j;
    scanf("%d %d", &m, &n);

    for (i = 0; i < m; i++) {
        scanf("%s", Praca[i]);
    }
    
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (Praca[i][j] == 'P') {
                // Cima
                if (EspacoValido(i - 1, j, m, n, Praca)) {
                    Praca[i - 1][j] = '+';
                }
                // Baixo
                if (EspacoValido(i + 1, j, m, n, Praca)) {
                    Praca[i + 1][j] = '+';
                }
                // Esquerda
                if (EspacoValido(i, j - 1, m, n, Praca)) {
                    Praca[i][j - 1] = '+';
                }
                // Direita
                if (EspacoValido(i, j + 1, m, n, Praca)) {
                    Praca[i][j + 1] = '+';
                }
                //Diagonais
                //Superior Esquerda
                if (EspacoValido(i - 1, j - 1, m, n, Praca)) {
                    Praca[i - 1][j - 1] = 'x';
                }
                //Superior Direita
                if (EspacoValido(i - 1, j + 1, m, n, Praca)) {
                    Praca[i - 1][j + 1] = 'x';
                }
                //Inferior Esquerda
                if (EspacoValido(i + 1, j - 1, m, n, Praca)) {
                    Praca[i + 1][j - 1] = 'x';
                }
                //Inferior Direita
                if (EspacoValido(i + 1, j + 1, m, n, Praca)) {
                    Praca[i + 1][j + 1] = 'x';
                }
            }
        }
    }
    for (i = 0; i < m; i++) {
        printf("%s\n", Praca[i]);
    }
    return 0;
}
