#include <stdio.h>

#define MAX_ALTURA 100
#define MAX_LARGURA 100

int Valido(int Linha, int Coluna, int M, int N, char Campo[MAX_ALTURA][MAX_LARGURA] ) {
    if (Linha >= 0 && Linha < M && Coluna >= 0 && Coluna < N) {
        if (Campo[Linha][Coluna] == '*') {
            return 1;
        }
    }
    return 0;
}

int main() {
    char Campo[MAX_ALTURA][MAX_LARGURA] = {0};
    int M, N;
    int i, j;
    scanf("%d %d", &M, &N);

    for (i = 0; i < M; i++) {
        scanf("%s", Campo[i]);
    }
    
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            int Minas = 0;
            if (Campo[i][j] == '-') {
                // Cima
                if (Valido(i-1, j, M, N, Campo)) {
                    Minas++;
                }
                // Baixo
                if (Valido(i+1, j, M, N, Campo)) {
                    Minas++;
                }
                // Esquerda
                if (Valido(i, j-1, M, N, Campo)) {
                    Minas++;
                }
                // Direita
                if (Valido(i, j+1, M, N, Campo)) {
                    Minas++;
                }
                //Diagonais
                //Superior Esquerda
                if (Valido(i-1, j-1, M, N, Campo)) {
                    Minas++;
                }
                //Superior Direita
                if (Valido(i-1, j+1, M, N, Campo)) {
                    Minas++;
                }
                //Inferior Esquerda
                if (Valido(i+1, j-1, M, N, Campo)) {
                    Minas++;
                }
                //Inferior Direita
                if (Valido(i+1, j+1, M, N, Campo)) {
                    Minas++;
                }
            //Converter pra Char
            Campo[i][j] = Minas + '0';
            }
        }
    }
    for (i = 0; i < M; i++) {
        printf("%s\n", Campo[i]);
    }
    return 0;
}
