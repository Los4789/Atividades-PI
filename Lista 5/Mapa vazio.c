#include <stdio.h>
#include <stdlib.h>

int main() {
    int Capacidade = 1;
    int TamanhoAtual = 0;
    int Numero;
    int i;
    
    int *Lugares = (int*) malloc(Capacidade * sizeof(int));
    
    while (scanf("%d", &Numero) == 1) {
        if (TamanhoAtual == Capacidade) {
            Capacidade *= 2;
            int *temp = (int*) realloc(Lugares, Capacidade * sizeof(int));
            if (temp == NULL) {
                printf("Erro\n");
                free(Lugares);
                exit(1);
            }
            Lugares = temp;
        }
        Lugares[TamanhoAtual] = Numero;
        TamanhoAtual++;
    }
    printf("Mais um bom dia de trabalho!\n");
    
    //Impar
    for (i = 0; i < TamanhoAtual; i++) {
        if (Lugares[i] % 2 != 0) {
            printf("%d\n", Lugares[i]);
        }
    }
    
    //Par
    for (i = 0; i < TamanhoAtual; i++) {
        if (Lugares[i] % 2 == 0) {
            printf("%d\n", Lugares[i]);
        }
    }
    
    printf("Vou visitar esses lugares de novo... algum dia.\n");
    free(Lugares);
    return 0;
}
