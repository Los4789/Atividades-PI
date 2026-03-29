#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_LINHAS 4
#define MAX_COLUNAS 4
#define TOTAL_PASSOS 20

int main() {
    int Cidade[MAX_LINHAS][MAX_COLUNAS] = {0};
    int LinhaAtual = 0; 
    int ColunaAtual = 0; 
    int i, j;
    char Passo;

    for (i = 0; i < TOTAL_PASSOS; i++) {
        scanf(" %c", &Passo);

        switch (Passo) {
            case 'c':
                LinhaAtual--;
                break;
            case 'b':
                LinhaAtual++;
                break;
            case 'e':
                ColunaAtual--;
                break;
            case 'd':
                ColunaAtual++;
                break;
        }

        Cidade[LinhaAtual][ColunaAtual]++;
    }

    int MaxPassos = 0;
    int MaxX = 0;
    int MaxY = 0;

    for (i = 0; i < MAX_LINHAS; i++) {
        for (j = 0; j < MAX_COLUNAS; j++) {
            if (Cidade[i][j] > MaxPassos) {
                MaxPassos = Cidade[i][j];
                MaxY = i; 
                MaxX = j; 
            }
        }
    }

    printf("Coordenada X:%d, Y:%d\n", MaxX, MaxY);

    return 0;
}
