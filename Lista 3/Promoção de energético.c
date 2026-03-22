#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_CLIENTES 400 //Não devem ter cases que peçam mais do que isso, né?

int main() {
    int N, X, Y;
    scanf("%d", &N);
    scanf("%d", &X);
    scanf("%d", &Y);
    int LatasEspeciais[MAX_CLIENTES] = {0};
    for (int J = 0; J < Y; J++) {
        char W[6]; 
        int Z;
        int Hora, Minuto;
        scanf("%s %d", W, &Z);
        sscanf(W, "%d:%d", &Hora, &Minuto);
        int MinutosTotais = Hora * 60 + Minuto;
        int DiffMinutos = MinutosTotais - 420;
        int Clientei = DiffMinutos / 3; 
        if (Clientei >= 1 && Clientei <= N && Clientei < MAX_CLIENTES) {
            LatasEspeciais[Clientei] = Z;
        }
    }
    int TotalLatas = 0;
    int Ganhou = 0;
    for (int i = 1; i <= N; i++) {
        int LatasCompradas = 0;
        
        if (LatasEspeciais[i] > 0) {
            LatasCompradas = LatasEspeciais[i];
        } 
        else if (X != 0 && i % X == 0) {
            LatasCompradas = 1;
        }
        TotalLatas += LatasCompradas;
        if (TotalLatas >= 50) {
            int MinutosAtendimento = 420 + (i * 3);
            int HoraFinal = MinutosAtendimento / 60;
            int MinutoFinal = MinutosAtendimento % 60;
            if (LatasCompradas == 1) {
                printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d lata.\n", 
                       i, HoraFinal, MinutoFinal, LatasCompradas);
            } else {
                printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d latas.\n", 
                       i, HoraFinal, MinutoFinal, LatasCompradas);
            }
            Ganhou = 1;
            break; 
        }
    }
    if (Ganhou == 0) {
        int LatasFaltantes = 50 - TotalLatas;
        if (LatasFaltantes == 1) {
            printf("Ainda nao foram vendidas latas suficientes. Falta 1 lata.\n");
        } else {
            printf("Ainda nao foram vendidas latas suficientes. Faltam %d latas.\n", LatasFaltantes);
        }
    }

    return 0;
}
