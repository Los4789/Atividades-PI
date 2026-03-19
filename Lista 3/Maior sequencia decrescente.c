#include <stdio.h>

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        int Numero;
        scanf("%d", &Numero);
        int N[100];
        for (int i = 0; i < Numero; i++){
            scanf("%d", &N[i]);
        }
        int TamanhoM = 0;
        int IndiceM = 0;
        int TamanhoA = 1;
        int IndiceA = 0;
        for (int i = 1; i < Numero; i++) {
            if (N[i] < N[i - 1]) {
                TamanhoA++;
                if (TamanhoA > TamanhoM) {
                    TamanhoM = TamanhoA;
                    IndiceM = IndiceA;
                }
            }
            else {
                TamanhoA = 1;
                IndiceA = i;
            }
        }
        if (TamanhoM >= 2) {
            printf("%d\n", TamanhoM);
            for (int i = 0; i < TamanhoM; i++) {
                printf("%d ", N[IndiceM + i]);
            }
            printf("\n");
        } else {
            printf("0\n");
        }
    }
    return 0;
}
