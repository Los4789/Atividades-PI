#include <stdio.h>
#include <stdlib.h>

int Dobro(int Valor) {
    return Valor * 2;
}

int Quadrado(int Valor) {
    return Valor * Valor;
}

int Absoluto(int Valor) {
    return abs(Valor);
}


void FuncOp(int **Matriz, int Linhas, int Colunas, int (*Funcao)(int)) {
    for (int i = 0; i < Linhas; i++) {
        for (int j = 0; j < Colunas; j++) {
            Matriz[i][j] = Funcao(Matriz[i][j]);
        }
    }
}

int main() {
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
    
    // Input Matriz
    for (i = 0; i < Linhas; i++) {
        for (j = 0; j < Colunas; j++) {
            scanf("%d", &Matriz[i][j]);
        }
    }

    scanf("%d", &Op);
    
    switch (Op) {
        case 1:
            FuncOp(Matriz, Linhas, Colunas, &Dobro);
            break;
        case 2:
            FuncOp(Matriz, Linhas, Colunas, &Quadrado);
            break;
        case 3:
            FuncOp(Matriz, Linhas, Colunas, &Absoluto);
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
