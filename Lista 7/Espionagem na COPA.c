#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_GAMBIARRA 100

typedef struct {
    char Nome[MAX_GAMBIARRA];
    int Populacao;
    int Periculosidade;
    char Funcao[MAX_GAMBIARRA];
} CidadelaS;

void formatarString(char *Texto) {
    if (strlen(Texto) > 0) {
        Texto[0] = toupper(Texto[0]);
        for (int i = 1; Texto[i] != '\0'; i++) {
            Texto[i] = tolower(Texto[i]); 
        }
    }
}

int compararCidadelas(const void *a, const void *b) {
    CidadelaS *cidA = (CidadelaS *)a;
    CidadelaS *cidB = (CidadelaS *)b;
    // População
    if (cidA->Populacao != cidB->Populacao) {
        return cidB->Populacao - cidA->Populacao;
    }
    //Desempate pela Periculosidade
    if (cidA->Periculosidade != cidB->Periculosidade) {
        return cidB->Periculosidade - cidA->Periculosidade;
    }
    //A pobre string.h sendo abusada aqui
    return strcmp(cidA->Nome, cidB->Nome);
}

int main() {
    CidadelaS Cidadelas[MAX_GAMBIARRA/2];
    char Linha[MAX_GAMBIARRA * 2];
    int TotalCidadelas = 0;
    char ChaveN[30];
    int AchouChave = 0;

    while (fgets(Linha, sizeof(Linha), stdin) != NULL) {
        Linha[strcspn(Linha, "\n")] = '\0';
        if (strlen(Linha) == 0) continue;

        if (strchr(Linha, '!') != NULL) {
            AchouChave = 1;
            int ControleChave = 0;
            for (int i = 0; Linha[i] != '\0'; i++) {
                if (isdigit(Linha[i])) {
                    ChaveN[ControleChave++] = Linha[i];
                }
            }
            ChaveN[ControleChave] = '\0'; 
            continue;
        }

        int NomeControle = 0;
        int FuncControle = 0;
        int flagPegarFuncao = 0;
        
        Cidadelas[TotalCidadelas].Populacao = 0;
        Cidadelas[TotalCidadelas].Periculosidade = 0;

        for (int i = 0; Linha[i] != '\0'; i++) {
            char c = Linha[i];
            
            if (flagPegarFuncao) {
                if (isalpha(c)) {
                    Cidadelas[TotalCidadelas].Funcao[FuncControle++] = c;
                    flagPegarFuncao = 0;
                }
            }

            if (c == ' ' && Linha[i+1] == ' ') {
                flagPegarFuncao = 1;
                i++;
                continue;
            }
            
            if (isupper(c)) {
                Cidadelas[TotalCidadelas].Nome[NomeControle++] = c;
            }
            
            if (isdigit(c)) {
                Cidadelas[TotalCidadelas].Populacao = Cidadelas[TotalCidadelas].Populacao * 10 + (c - '0');
            }
            
            if (c == '*') {
                Cidadelas[TotalCidadelas].Periculosidade++;
            }
        }

        Cidadelas[TotalCidadelas].Nome[NomeControle] = '\0';
        Cidadelas[TotalCidadelas].Funcao[FuncControle] = '\0';

        formatarString(Cidadelas[TotalCidadelas].Nome);
        formatarString(Cidadelas[TotalCidadelas].Funcao);

        TotalCidadelas++;
    }
    
    qsort(Cidadelas, TotalCidadelas, sizeof(CidadelaS), compararCidadelas);
    
    if (!AchouChave) {
        printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");
    } 
    else {
        int Posicao = atoi(ChaveN); 
        int Indice = Posicao - 1;
        if (Indice >= 0 && Indice < TotalCidadelas) {
            CidadelaS Alvo = Cidadelas[Indice];
            printf("Gingrey foi encontrada em %s, uma cidadela com %d mil habitantes cuja função é %s e periculosidade ", 
                   Alvo.Nome, Alvo.Populacao, Alvo.Funcao);
            for(int p = 0; p < Alvo.Periculosidade; p++) {
                printf("*");
            }
            printf(".");
            int MuitoDensa = (Alvo.Populacao >= 1000);
            int MuitoPerigosa = (Alvo.Periculosidade > 3);
            if (MuitoDensa && MuitoPerigosa) {
                printf(" Talvez seja melhor desistir...");
            } else if (MuitoDensa) {
                printf(" Um lugar denso, vai ser difícil achar ela.");
            } else if (MuitoPerigosa) {
                printf(" Vai ser complicado entrar lá.");
            }
            
        }
        else {
            printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");
        }
    }
    return 0;
}
