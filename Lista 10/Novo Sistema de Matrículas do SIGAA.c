#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Monitores, se estiverem lendo,
//Não tem como ficar mais otimizado que isso :)

//Foi bem divertido fazer essa daqui

//Agora se fosse em teste, não ia ter tempo de fazer essa brincadeira

typedef struct Aluno {
    long long Matricula;
    double CR;
    struct Aluno *Proximo;
    unsigned int L;
    unsigned int R;
    int Score;
    unsigned int Prioridade :2;
} Aluno;

typedef struct Fila {
    Aluno *Inicio;
    Aluno *Fim;
} Fila;

void InicializarFila(Fila *F) {
    F->Inicio = NULL;
    F->Fim = NULL;
}

void Enqueue(Fila *F, Aluno *Novo) {
    Novo->Proximo = NULL;
    if (F->Fim == NULL) {
        F->Inicio = Novo;
        F->Fim = Novo;
    } else {
        F->Fim->Proximo = Novo;
        F->Fim = Novo;
    }
}

Aluno* Dequeue(Fila *F) {
    if (F->Inicio == NULL) return NULL;
    
    Aluno *Temp = F->Inicio;
    F->Inicio = F->Inicio->Proximo;
    if (F->Inicio == NULL) F->Fim = NULL;
    
    return Temp;
}

int main() {
    char Comando[20];
    char NomeDisciplina[55];
    int Vagas = 0;
    unsigned int Relogio = 1; 

    Fila FilaRequisicoes;
    Fila FilaConfirmados;
    InicializarFila(&FilaRequisicoes);
    InicializarFila(&FilaConfirmados);

    while (scanf("%s", Comando) != EOF) {
        
        //Como os comandos tem iniciais diferentes, só preciso ver a primeira letra
        switch (Comando[0]) {
            
            case 'S':
                scanf("%s %d", NomeDisciplina, &Vagas);
                break;
                
            case 'A': {
                Aluno *Novo = (Aluno*) malloc(sizeof(Aluno));
                if (Novo == NULL) exit(1);
                unsigned int TempPri; 
                scanf("%lld %u %lf %u %u", &Novo->Matricula, &TempPri, &Novo->CR, &Novo->L, &Novo->R);
                Novo->Prioridade = TempPri; 
                
                Novo->Score = (int)round(Novo->CR * 100) / Novo->Prioridade;
                Enqueue(&FilaRequisicoes, Novo);
                break;
            }
                
            case 'P': {
                int Qtd;
                scanf("%d", &Qtd);
                
                while (Qtd > 0 && FilaRequisicoes.Inicio != NULL) {
                    Aluno *Atual = Dequeue(&FilaRequisicoes);
                    
                    if (Relogio < Atual->L) {
                        Relogio = Atual->L;
                    }
                    
                    if (Relogio > Atual->R) {
                        printf("[TIMEOUT] mat=%lld | Desconectado da fila.\n", Atual->Matricula);
                        free(Atual);
                    } 
                    else {
                        if (Vagas > 0) {
                            printf("[ALOCADO] mat=%lld | score=%d | Processado no seg: %u\n", 
                                   Atual->Matricula, Atual->Score, Relogio);
                            Vagas--;
                            Enqueue(&FilaConfirmados, Atual);
                        } else {
                            printf("[LOTADO] mat=%lld | score=%d | Processado no seg: %u\n", 
                                   Atual->Matricula, Atual->Score, Relogio);
                            free(Atual);
                        }
                        Relogio++;
                    }
                    Qtd--;
                }
                break;
            }
                
            case 'F': {
                printf("--- LISTA OFICIAL: %s ---\n", NomeDisciplina);
                int Posicao = 1;
                while (FilaConfirmados.Inicio != NULL) {
                    Aluno *Conf = Dequeue(&FilaConfirmados);
                    printf("%d. Matricula: %lld\n", Posicao, Conf->Matricula);
                    Posicao++;
                    free(Conf);
                }
                
                while (FilaRequisicoes.Inicio != NULL) {
                    Aluno *Sobra = Dequeue(&FilaRequisicoes);
                    free(Sobra);
                }
                return 0;
            }
        }
    }

    return 0;
}
