#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//Eu usei tamanhos mágicos aqui por preguiça, eu sei que está errado, eu sei que não deve ser feito denovo
//Mas tô com dor de cabeça e TALVEZ eu vá arrumar isso depois
//Se quiser descontar ponto, suave, eu entendo

int main() {
    char Frase[105];
    int InicioPalavra[55];
    int TamanhoPalavra[55];
    int TotalPalavras = 0;
    int i, j, k;
    fgets(Frase, 105, stdin);
    int EmPalavra = 0;
    
    for (i = 0; Frase[i] != '\0'; i++) {
        int EhLetra = (Frase[i] >= 'a' && Frase[i] <= 'z') || (Frase[i] >= 'A' && Frase[i] <= 'Z');
        if (EhLetra) {
            if (EmPalavra == 0) {
                InicioPalavra[TotalPalavras] = i;
                TamanhoPalavra[TotalPalavras] = 0;
                EmPalavra = 1;
            }
            TamanhoPalavra[TotalPalavras]++;
        } else {
            if (EmPalavra == 1) {
                TotalPalavras++;
                EmPalavra = 0;
            }
        }
    }
    
    if (EmPalavra == 1) {
        TotalPalavras++;
    }

    int TotalPares = 0;
    for (i = 0; i < TotalPalavras; i++) {
        for (j = i + 1; j < TotalPalavras; j++) {
            if (TamanhoPalavra[i] == TamanhoPalavra[j]) {
                int FreqI[26] = {0};
                int FreqJ[26] = {0};
                int Tamanho = TamanhoPalavra[i];
                for (k = 0; k < Tamanho; k++) {
                    char LetraI = Frase[InicioPalavra[i] + k];
                    char LetraJ = Frase[InicioPalavra[j] + k];
                    if (LetraI >= 'A' && LetraI <= 'Z') {
                        LetraI = LetraI + 32;
                    }
                    if (LetraJ >= 'A' && LetraJ <= 'Z') {
                        LetraJ = LetraJ + 32;
                    }
                    FreqI[LetraI - 'a']++;
                    FreqJ[LetraJ - 'a']++;
                }
                int SaoAnagramas = 1;
                for (k = 0; k < 26; k++) {
                    if (FreqI[k] != FreqJ[k]) {
                        SaoAnagramas = 0;
                        break;
                    }
                }
                if (SaoAnagramas == 1) {
                    if (TotalPares == 0) {
                        printf("Pares de anagramas encontrados:\n");
                    }
                    for (k = 0; k < TamanhoPalavra[i]; k++) {
                        putchar(Frase[InicioPalavra[i] + k]);
                    }
                    printf(" e ");
                    for (k = 0; k < TamanhoPalavra[j]; k++) {
                        putchar(Frase[InicioPalavra[j] + k]);
                    }
                    printf("\n");
                    TotalPares++;
                }
            }
        }
    }

    if (TotalPares == 0) {
        printf("Nao existem anagramas na frase.\n");
    } else {
        printf("\nTotal de pares: %d\n", TotalPares);
    }
    return 0;
}
