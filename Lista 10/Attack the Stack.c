#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    char Cor;
    struct No *Proximo;
} No;

void ResolverPilha(No **Topo) {
    int Alterou = 1;
    while (Alterou && *Topo != NULL) {
        Alterou = 0; 
        No *T1 = *Topo;
        No *T2 = T1->Proximo;
        
        // Eliminação 3 blocos
        if (T2 != NULL && T2->Proximo != NULL) {
            No *T3 = T2->Proximo;
            if (T1->Cor == T2->Cor && T2->Cor == T3->Cor) {
                *Topo = T3->Proximo;
                free(T1);
                free(T2);
                free(T3);
                
                Alterou = 1; 
                continue;
            }
        }
        
        // Combinação de cores
        if (T2 != NULL) {
            char Cor1 = T1->Cor;
            char Cor2 = T2->Cor;
            char NovaCor = 0;

            if ((Cor1 == 'g' && Cor2 == 'b') || (Cor1 == 'b' && Cor2 == 'g')) {
                NovaCor = 'c';
            }
            else if ((Cor1 == 'r' && Cor2 == 'b') || (Cor1 == 'b' && Cor2 == 'r')) {
                NovaCor = 'm';
            }
            else if ((Cor1 == 'r' && Cor2 == 'g') || (Cor1 == 'g' && Cor2 == 'r')) {
                NovaCor = 'y';
            }

            if (NovaCor != 0) {
                No *NovoNo = (No*) malloc(sizeof(No));
                
                if (NovoNo == NULL) {
                    printf("Erro de Alocacao na combinacao!\n");
                    No *Atual = *Topo;
                    while (Atual != NULL) {
                        No *Deletar = Atual;
                        Atual = Atual->Proximo;
                        free(Deletar);
                    }
                    exit(1);
                }
                
                NovoNo->Cor = NovaCor;
                NovoNo->Proximo = T2->Proximo;
                *Topo = NovoNo;

                free(T1);
                free(T2);
                Alterou = 1;
                continue;
            }
        }
    }
}

int main() {
    No *Topo = NULL; 
    char BlocoAtual;
    while (scanf(" %c", &BlocoAtual) != EOF) {
        No *NovoNo = (No*) malloc(sizeof(No));

        if (NovoNo == NULL) {
            printf("Erro de Alocacao!\n");
            No *Atual = Topo;
            while (Atual != NULL) {
                No *Deletar = Atual;
                Atual = Atual->Proximo;
                free(Deletar);
            }
            exit(1);
        }
        
        NovoNo->Cor = BlocoAtual;
        NovoNo->Proximo = Topo;
        Topo = NovoNo;

        ResolverPilha(&Topo);
        if (Topo == NULL) {
            printf("Pilha vazia!\n");
        } else {
            No *Atual = Topo;
            while (Atual != NULL) {
                printf("%c\n", Atual->Cor);
                Atual = Atual->Proximo;
            }
        }
        printf("\n"); 
    }

    printf("Thank You So Much For Playing My Game!\n");

    No *Atual = Topo;
    while (Atual != NULL) {
        No *Deletar = Atual;
        Atual = Atual->Proximo;
        free(Deletar);
    }

    return 0;
}
