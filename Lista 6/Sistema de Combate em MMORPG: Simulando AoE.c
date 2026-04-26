#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GAMBIARRA 50 

int** AlocarMatriz(int Linhas, int Colunas) {
    int** NovaMatriz = (int**)malloc(Linhas * sizeof(int*));
    for (int i = 0; i < Linhas; i++) {
        NovaMatriz[i] = (int*)malloc(Colunas * sizeof(int));
    }
    return NovaMatriz;
}

void LiberarMatriz(int** Matriz, int Linhas) {
    for (int i = 0; i < Linhas; i++) {
        free(Matriz[i]);
    }
    free(Matriz);
}

void ImprimirMatriz(int** Matriz, int Linhas, int Colunas) {
    for (int i = 0; i < Linhas; i++) {
        for (int j = 0; j < Colunas; j++) {
            printf("%d", Matriz[i][j]);
            if (j < Colunas - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int ObterCamada(int DistanciaX, int DistanciaY) {
    if (DistanciaX == 0 && DistanciaY == 0) return 1;
    if (DistanciaX + DistanciaY == 1) return 1;
    if (DistanciaX <= 2 && DistanciaY <= 2 && !(DistanciaX == 2 && DistanciaY == 2)) return 2;
    return 0; 
}

void ExplosaoArcana(int** MatrizAtual, int Linhas, int Colunas, int CentroX, int CentroY) {
    int** NovaMatriz = AlocarMatriz(Linhas, Colunas);

    for (int i = 0; i < Linhas; i++) {
        for (int j = 0; j < Colunas; j++) {
            NovaMatriz[i][j] = MatrizAtual[i][j];
            
            int DistanciaX = abs(i - CentroX);
            int DistanciaY = abs(j - CentroY);
            int Camada = ObterCamada(DistanciaX, DistanciaY);

            int Dano = 0;
            if (Camada == 1) Dano = 50;
            else if (Camada == 2) Dano = 25;

            if (Dano > 0) {
                NovaMatriz[i][j] -= Dano;
                if (NovaMatriz[i][j] < 0) NovaMatriz[i][j] = 0;
            }
        }
    }

    printf("\nEstado do mapa após usar a Explosão Arcana:\n");
    ImprimirMatriz(NovaMatriz, Linhas, Colunas);
    LiberarMatriz(NovaMatriz, Linhas);
}

void NuvemVenenosa(int** MatrizInicial, int Linhas, int Colunas, int CentroX, int CentroY) {
    printf("\nEstado do mapa, por turno, após usar a Nuvem Venenosa:\n");

    int** MatrizTurno = AlocarMatriz(Linhas, Colunas);
    for (int i = 0; i < Linhas; i++) {
        for (int j = 0; j < Colunas; j++) {
            MatrizTurno[i][j] = MatrizInicial[i][j];
        }
    }

    for (int Turno = 1; Turno <= 3; Turno++) {
        int** NovaMatriz = AlocarMatriz(Linhas, Colunas);
        int UnidadesVivasNaArea = 0;

        for (int i = 0; i < Linhas; i++) {
            for (int j = 0; j < Colunas; j++) {
                NovaMatriz[i][j] = MatrizTurno[i][j];
                
                int DistanciaX = abs(i - CentroX);
                int DistanciaY = abs(j - CentroY);
                int Camada = ObterCamada(DistanciaX, DistanciaY);

                if (Camada == 1 || Camada == 2) {
                    int VizinhosVivos = 0;
                    for (int k = 0; k < 9; k++) {
                        if (k == 4) continue; // Pula o próprio centro (i, j)
                        
                        int VizinhoX = i - 1 + (k / 3);
                        int VizinhoY = j - 1 + (k % 3);
                        
                        if (VizinhoX >= 0 && VizinhoX < Linhas && VizinhoY >= 0 && VizinhoY < Colunas) {
                            if (MatrizTurno[VizinhoX][VizinhoY] > 0) {
                                VizinhosVivos++;
                            }
                        }
                    }

                    int Dano = 5 + (8 * VizinhosVivos);
                    NovaMatriz[i][j] -= Dano;
                    
                    if (NovaMatriz[i][j] < 0) NovaMatriz[i][j] = 0;

                    if (NovaMatriz[i][j] > 0) {
                        UnidadesVivasNaArea++;
                    }
                }
            }
        }

        ImprimirMatriz(NovaMatriz, Linhas, Colunas);

        LiberarMatriz(MatrizTurno, Linhas);
        MatrizTurno = NovaMatriz;
        
        if (UnidadesVivasNaArea == 0) {
            break; 
        }
        if (Turno < 3) {
            printf("\n"); 
        }
    }
    
    LiberarMatriz(MatrizTurno, Linhas);
}

int main() {
    int Linhas, Colunas;
    if (scanf("%d %d", &Linhas, &Colunas) != 2) return 1;

    int** MatrizInicial = AlocarMatriz(Linhas, Colunas);
    for (int i = 0; i < Linhas; i++) {
        for (int j = 0; j < Colunas; j++) {
            scanf("%d", &MatrizInicial[i][j]);
        }
    }

    int CentroX, CentroY;
    scanf("%d %d", &CentroX, &CentroY);

    char TipoAtaque[MAX_GAMBIARRA];
    scanf("%s", TipoAtaque);

    printf("Estado inicial do mapa:\n");
    ImprimirMatriz(MatrizInicial, Linhas, Colunas);

    void (*AtaqueS)(int**, int, int, int, int) = NULL;

    if (strcmp(TipoAtaque, "EXPLOSAO_ARCANA") == 0) {
        AtaqueS = ExplosaoArcana;
    } else if (strcmp(TipoAtaque, "NUVEM_VENENOSA") == 0) {
        AtaqueS = NuvemVenenosa;
    }

    if (AtaqueS != NULL) {
        AtaqueS(MatrizInicial, Linhas, Colunas, CentroX, CentroY);
    }

    LiberarMatriz(MatrizInicial, Linhas);
    return 0;
}
