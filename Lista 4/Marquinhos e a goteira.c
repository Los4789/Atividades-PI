#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_ALTURA 251
#define MAX_LARGURA 251
#define MAX_FONTES 251
#define MAX_PILHA (MAX_ALTURA * MAX_LARGURA)

//Bela tentativa em me fazer usar recurssão
void SimularEscoamento(int OrigemI, int OrigemJ, int m, int n, char Parede[MAX_ALTURA][MAX_LARGURA], int PilhaI[], int PilhaJ[]) {
    int Topo = 0;

    PilhaI[Topo] = OrigemI;
    PilhaJ[Topo] = OrigemJ;
    Topo++;

    while (Topo > 0) {
        Topo--;
        int Linha = PilhaI[Topo];
        int Coluna = PilhaJ[Topo];

        if (Linha + 1 >= m) {
            continue;
        }
        //Descendo
        if (Parede[Linha + 1][Coluna] == '.') {
            Parede[Linha + 1][Coluna] = 'o';
            
            PilhaI[Topo] = Linha + 1;
            PilhaJ[Topo] = Coluna;
            Topo++;
        //Obstáculo
        } else if (Parede[Linha + 1][Coluna] == '#') {
            //Esquerda
            if (Coluna - 1 >= 0 && Parede[Linha][Coluna - 1] == '.') {
                Parede[Linha][Coluna - 1] = 'o';
                
                PilhaI[Topo] = Linha;
                PilhaJ[Topo] = Coluna - 1;
                Topo++;
            }
            //Direita
            if (Coluna + 1 < n && Parede[Linha][Coluna + 1] == '.') {
                Parede[Linha][Coluna + 1] = 'o';
                
                PilhaI[Topo] = Linha;
                PilhaJ[Topo] = Coluna + 1;
                Topo++;
            }
        }
    }
}

int main() {
    int PilhaI[MAX_PILHA];
    int PilhaJ[MAX_PILHA];
    int m, n;
    char Parede[MAX_ALTURA][MAX_LARGURA];
    int i, j;
    scanf("%d %d", &m, &n);
    
    for (i = 0; i < m; i++) {
        scanf("%s", Parede[i]);
    }

    int OrigemI[MAX_FONTES];
    int OrigemJ[MAX_FONTES];
    int TotalOrigens = 0;
    
    //Não sei se é necessário mas é bom fazer se tiver escoamentos diferentes
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (Parede[i][j] == 'o' && TotalOrigens < MAX_FONTES) {
                OrigemI[TotalOrigens] = i;
                OrigemJ[TotalOrigens] = j;
                TotalOrigens++;
            }
        }
    }

    for (i = 0; i < TotalOrigens; i++) {
        SimularEscoamento(OrigemI[i], OrigemJ[i], m, n, Parede, PilhaI, PilhaJ);
    }

    for (i = 0; i < m; i++) {
        printf("%s\n", Parede[i]);
    }

    return 0;
}
