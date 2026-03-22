#include <stdio.h>
#include <string.h>
// Pronto, sem números mágicos agora
#define MAX_LEDS 65
#define MAX_GIGANTE 65000 // Deve ser suficiente

int main() {
    int R;
    scanf("%d", &R);
    char LuzGigante[MAX_GIGANTE] = "";
    int TamanhoAtual = 0;
    int i, j;
    for (i = 0; i < R; i++) {
        char S[MAX_LEDS];
        long long F; // Usando long long caso o número de flashes seja muito grande
        scanf("%s %lld", S, &F);
        int TamanhoS = strlen(S);
        long long Carry = F;
        for (j = 0; j < TamanhoS && Carry > 0; j++) {
            long long ValorAtual = (S[j] == 'O' ? 1 : 0);
            long long Soma = ValorAtual + Carry;
            
            // Se a soma for ímpar luz liga, se par, luz apaga
            if (Soma % 2 == 1) {
                S[j] = 'O';
            } 
            else {
                S[j] = 'X';
            }
            // Passar para próxima soma o resto
            Carry = Soma / 2;
        }
        printf("%s\n", S);
        if (i == 0) {
            strcpy(LuzGigante, S);
            TamanhoAtual = TamanhoS;
        } else {
            char UltimoLed = LuzGigante[TamanhoAtual - 1];
            char PrimeiroLedNovo = S[0];
            char Ornamento;
            
            int EhPar = (TamanhoAtual % 2 == 0);
            int EhIgual = (UltimoLed == PrimeiroLedNovo);
            if (EhPar && EhIgual) {
                Ornamento = '@';
            } else if (!EhPar && EhIgual) {
                Ornamento = '#';
            } else if (EhPar && !EhIgual) {
                Ornamento = '$';
            } else { // !EhPar && !EhIgual
                Ornamento = '%';
            }
            LuzGigante[TamanhoAtual] = Ornamento;
            TamanhoAtual++;
            strcpy(&LuzGigante[TamanhoAtual], S);
            TamanhoAtual += TamanhoS;
        }
    }
    printf("%s\n", LuzGigante);
    return 0;
}
