#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_ALTURA 100
#define MAX_LARGURA 100

int Valido(int Linha, int Coluna, int M, int N, char Campo[MAX_ALTURA][MAX_LARGURA]) {
    if (Linha >= 0 && Linha < M && Coluna >= 0 && Coluna < N && Campo[Linha][Coluna] != '#') {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    char Campo[MAX_ALTURA][MAX_LARGURA] = {0};
    int Distancia[MAX_ALTURA][MAX_LARGURA];
    int M, N;
    int i, j;
    int LinhaInicial, ColunaInicial;
    int FilaX[10000];
    int FilaY[10000];
    scanf("%dx%d", &M, &N);

    for (i = 0; i < M; i++) {
        scanf("%s", Campo[i]);
    }
    
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if (Campo[i][j] == 'o') {
                ColunaInicial = j;
                LinhaInicial = i;
            }
            Distancia[i][j] = -1;
        }
    }
   
    int InicioFila = 0;
    int FimFila = 0;
    
    FilaX[FimFila] = LinhaInicial;
    FilaY[FimFila] = ColunaInicial;
    FimFila++;
    
    Distancia[LinhaInicial][ColunaInicial] = 0; // A distância da origem até a origem é zero
    
    while (InicioFila < FimFila) {
        int LinhaAtual = FilaX[InicioFila];
        int ColunaAtual = FilaY[InicioFila];
        InicioFila++;
        
        if (Campo[LinhaAtual][ColunaAtual] == 'd') {
            printf("Apos correr %d metros e quase desistir por causa da distância, Rebeka conseguiu escapar!\n", Distancia[LinhaAtual][ColunaAtual]);
            return 0;
        }
        
        //Cima
        if (Valido(LinhaAtual - 1, ColunaAtual, M, N, Campo)) {
            if (Distancia[LinhaAtual-1][ColunaAtual] == -1) {
                FilaX[FimFila] = LinhaAtual-1;
                FilaY[FimFila] = ColunaAtual;
                FimFila++;
                Distancia[LinhaAtual-1][ColunaAtual] = Distancia[LinhaAtual][ColunaAtual] + 1;
            }
        }
        //Baixo
        if (Valido(LinhaAtual + 1, ColunaAtual, M, N, Campo)) {
            if (Distancia[LinhaAtual+1][ColunaAtual] == -1) {
                FilaX[FimFila] = LinhaAtual+1;
                FilaY[FimFila] = ColunaAtual;
                FimFila++;
                Distancia[LinhaAtual+1][ColunaAtual] = Distancia[LinhaAtual][ColunaAtual] + 1;
            }
        }
        //Esquerda
        if (Valido(LinhaAtual, ColunaAtual - 1, M, N, Campo)) {
            if (Distancia[LinhaAtual][ColunaAtual - 1] == -1) {
                FilaX[FimFila] = LinhaAtual;
                FilaY[FimFila] = ColunaAtual - 1;
                FimFila++;
                Distancia[LinhaAtual][ColunaAtual-1] = Distancia[LinhaAtual][ColunaAtual] + 1;
            }
        }
        //Direita
        if (Valido(LinhaAtual, ColunaAtual + 1, M, N, Campo)) {
            if (Distancia[LinhaAtual][ColunaAtual + 1] == -1) {
                FilaX[FimFila] = LinhaAtual;
                FilaY[FimFila] = ColunaAtual + 1;
                FimFila++;
                Distancia[LinhaAtual][ColunaAtual + 1] = Distancia[LinhaAtual][ColunaAtual] + 1;
            }
        }
    }
    printf("Poxa... Parece que nao foi dessa vez que Rebeka conseguiu fugir\n");
   
    return 0;
}
