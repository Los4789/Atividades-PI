#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GAMBIARRA 30

typedef struct {
    char Nome[MAX_GAMBIARRA];
    char Genero[MAX_GAMBIARRA];
    char Estudio[MAX_GAMBIARRA];
    char Console[MAX_GAMBIARRA+10];
    int Nota;
    int Ano;
} Jogo;

int PrintParametro (int Valor) {
    if (Valor == 0) {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
        return 0;
    }
    return 1;
}

void printAno (Jogo ListaJogos[100], int N) {
    int AnoP, i;
    int TotalJogos = 0;
    
    scanf("%d", &AnoP);
    
    for (i = 0; i < N; i++) {
        if (ListaJogos[i].Ano == AnoP) {
            printf("%s\n", ListaJogos[i].Nome);
            TotalJogos++;
        }
    }
    
    if (PrintParametro(TotalJogos)) {
        printf("Tenho %d jogos || %d.\n", TotalJogos, AnoP);
    }
}

void printLetra (Jogo ListaJogos[100], int N) {
    int i;
    char Letra;
    int TotalJogos = 0;
    
    scanf(" %c", &Letra); 
    
    for (i = 0; i < N; i++) {
        if (ListaJogos[i].Nome[0] == Letra) {
            printf("%s\n", ListaJogos[i].Nome);
            TotalJogos++;
        }
    }
    
    if (PrintParametro(TotalJogos)) {
        printf("Tenho %d jogos || %c.\n", TotalJogos, Letra);
    }
}

void printStudio (Jogo ListaJogos[100], int N) {
    int i;
    char StudioT[MAX_GAMBIARRA];
    int TotalJogos = 0;
    
    scanf("%s", StudioT);
    
    for (i = 0; i < N; i++) {
        if (strcmp(ListaJogos[i].Estudio, StudioT) == 0) { 
            printf("%s\n", ListaJogos[i].Nome);
            TotalJogos++;
        }
    }
    
    if (PrintParametro(TotalJogos)) {
        printf("Tenho %d jogos || %s.\n", TotalJogos, StudioT);
    }
}

void printConsole (Jogo ListaJogos[100], int N) {
    int i;
    char ConsoleT[MAX_GAMBIARRA+10];
    int TotalJogos = 0;
    
    scanf(" %[^\n]", ConsoleT); 
    
    for (i = 0; i < N; i++) {
        if (strcmp(ListaJogos[i].Console, ConsoleT) == 0) {
            printf("%s\n", ListaJogos[i].Nome);
            TotalJogos++;
        }
    }
    
    if (PrintParametro(TotalJogos)) {
        printf("Tenho %d jogos || %s.\n", TotalJogos, ConsoleT);
    }
}

void printColecao (Jogo ListaJogos[100], int N) {
    int i;
    for (i = 0; i < N; i++) {
        printf("%s %d\n", ListaJogos[i].Nome, ListaJogos[i].Nota); 
    }
}

int main()
{
    Jogo ListaJogos[100];
    int N;
    int i;
    char TempLinha[200];
    void (*Funcao) (Jogo*, int) = NULL;

    scanf("%d", &N);
    getchar();
    
    for (i = 0; i < N; i++) {
        if (fgets(TempLinha, sizeof(TempLinha), stdin) != NULL) {
            TempLinha[strcspn(TempLinha, "\n")] = '\0';
            
            char *UltimoEspaco = strrchr(TempLinha, ' ');
            if (UltimoEspaco != NULL) {
                int UltimoValor = atoi(UltimoEspaco + 1);
                *UltimoEspaco = '\0';
                
                char *PenultimoEspaco = strrchr(TempLinha, ' ');
                
                if (PenultimoEspaco != NULL && *(PenultimoEspaco + 1) >= '0' && *(PenultimoEspaco + 1) <= '9') {
                    ListaJogos[i].Nota = atoi(PenultimoEspaco + 1); 
                    ListaJogos[i].Ano = UltimoValor;
                    *PenultimoEspaco = '\0';
                } else {
                    // Quem teve a ideia de colocar cases com inputs juntos?
                    // Até o diabo deve ter medo desse monitor
                    // Espero que essa fix aqui resolva
                    
                    ListaJogos[i].Nota = UltimoValor;
                    ListaJogos[i].Ano = 0;
                }
            }
            sscanf(TempLinha, "%s %s %s %[^\n]", ListaJogos[i].Nome, ListaJogos[i].Genero, ListaJogos[i].Estudio, ListaJogos[i].Console);
            if (ListaJogos[i].Nota > 7) {
                printf("AWESOME! Mais um GOTY pra minha coleção!\n");
            }
            else if (ListaJogos[i].Nota < 4) {
                printf("Era melhor jogar mais um jogo de Mahjong.\n");
            }
        }
    }
    
    char Comando[15];
    
    while (scanf("%s", Comando) == 1) {
        if (strcmp(Comando, "printAno") == 0) {
            Funcao = printAno;
        }
        else if (strcmp(Comando, "printLetra") == 0) {
            Funcao = printLetra;
        }
        else if (strcmp(Comando, "printStudio") == 0) {
            Funcao = printStudio;
        }
        else if (strcmp(Comando, "printConsole") == 0) {
            Funcao = printConsole;
        }
        else if (strcmp(Comando, "printColecao") == 0) {
            Funcao = printColecao;
        }
        else {
            Funcao = NULL;
        }

        if (Funcao != NULL) {
            Funcao(ListaJogos, N);
        }
    }
    
    printf("Enjoei de jogar, agora vou ver TV.\n");
    
    return 0;
}
