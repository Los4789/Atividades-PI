#include <stdio.h>
#include <stdlib.h>

void Dobro(int **Matriz, int Linhas, int Colunas) {
    for (int i = 0; i < Linhas; i++) {
        for (int j = 0; j < Colunas; j++) {
            Matriz[i][j] *= 2;
        }
    }
}

void Quadrado(int **Matriz, int Linhas, int Colunas) {
    for (int i = 0; i < Linhas; i++) {
        for (int j = 0; j < Colunas; j++) {
            Matriz[i][j] *= Matriz[i][j];
        }
    }
}

void Absoluto(int **Matriz, int Linhas, int Colunas) {
    for (int i = 0; i < Linhas; i++) {
        for (int j = 0; j < Colunas; j++) {
            Matriz[i][j] = abs(Matriz[i][j]);
        }
    }
}

int main()
{
    int Linhas, Colunas, Op;
    int i, j;
    scanf("%d %d", &Linhas, &Colunas);
    int **Matriz = (int**) malloc(Linhas * sizeof(int*));
    
    if (Matriz == NULL) {
        exit(1);
    }
    
    for (i = 0; i < Linhas; i++) {
        Matriz[i] = (int*) malloc(Colunas * sizeof(int));
        if (Matriz[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(Matriz[j]);
            }
            free(Matriz);
            exit(1);
        }
    }
    
    //Input Matriz
    for (i = 0; i < Linhas; i++) {
        for (j = 0; j < Colunas; j++) {
            scanf("%d", &Matriz[i][j]);
        }
    }
    //Input operação
    scanf("%d", &Op);
    
    switch (Op) {
        case 1:
        Dobro(Matriz, Linhas, Colunas);
        break;
        case 2:
        Quadrado(Matriz, Linhas, Colunas);
        break;
        case 3:
        Absoluto(Matriz, Linhas, Colunas);
        break;
    }
    
    for (i = 0; i < Linhas; i++) {
        for (j = 0; j < Colunas; j++) {
            printf("%d ", Matriz[i][j]);
        }
        printf("\n");
    }
    
    for (i = 0; i < Linhas; i++) {
        free(Matriz[i]);
    }
    free(Matriz);
    
    return 0;
}
