#include <stdio.h>
#include <stdlib.h>

int Calibrar(int Valor) {
    return Valor + 5;
}

int Saturar(int Valor) {
    if (Valor > 80) {
        Valor = 80;
    }
    return Valor;
}

int Amplificar(int Valor) {
    return Valor * 2;
}

int main() {
    int Linhas, Colunas;
    int i, j, k; 
    int (*Filtros[4])(int) = {NULL, Calibrar, Saturar, Amplificar};
    
    if (scanf("%d %d", &Linhas, &Colunas) != 2) return 1;
    
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
    
    for (i = 0; i < Linhas; i++) {
        for (j = 0; j < Colunas; j++) {
            scanf("%d", &Matriz[i][j]);
        }
    }

    int Comando;
    while (scanf("%d", &Comando) == 1 && Comando != 0) {
        int (**Pipeline)(int) = NULL; 
        
        if (Comando >= 1 && Comando <= 3) {
            k = 1;
            Pipeline = (int (**)(int)) malloc(k * sizeof(int (*)(int)));
            Pipeline[0] = Filtros[Comando];
        } 
        
        else if (Comando == 4) {
            scanf("%d", &k);
            Pipeline = (int (**)(int)) malloc(k * sizeof(int (*)(int)));
            
            for (int Passo = 0; Passo < k; Passo++) {
                int IdFiltro;
                scanf("%d", &IdFiltro);
                Pipeline[Passo] = Filtros[IdFiltro];
            }
        } else {
            continue; 
        }
        
        for (i = 0; i < Linhas; i++) {
            for (j = 0; j < Colunas; j++) {
                for (int Passo = 0; Passo < k; Passo++) {
                    int (*modificar)(int) = Pipeline[Passo];
                    Matriz[i][j] = modificar(Matriz[i][j]);
                }
            }
        }
        
        free(Pipeline);
    }
    

    printf("Matriz processada:\n");
    int ValorCritico = Matriz[0][0];
    int LinhaCritica = 0, ColunaCritica = 0;
    
    for (i = 0; i < Linhas; i++) {
        for (j = 0; j < Colunas; j++) {
            printf("%d ", Matriz[i][j]);
            
            if (Matriz[i][j] > ValorCritico) {
                ValorCritico = Matriz[i][j];
                LinhaCritica = i;
                ColunaCritica = j;
            }
        }
        printf("\n");
    }
    
    printf("\nSensor critico: %d\n", ValorCritico);
    printf("Posicao: (%d,%d)\n", LinhaCritica, ColunaCritica);
    
    for (i = 0; i < Linhas; i++) {
        free(Matriz[i]);
    }
    free(Matriz);
    
    return 0;
}
