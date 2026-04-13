#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Eu odeio fazer lista

char* LerStringDinamica() {
    int Capacidade = 16;
    int Tamanho = 0;
    
    char *Str = (char*) malloc(Capacidade * sizeof(char));
    if (Str == NULL) {
        printf("Erro na alocacao inicial.\n");
        exit(1);
    }

    int c; 
    
    c = getchar();
    while (c != EOF && (c < 'a' || c > 'z')) {
        c = getchar();
    }

    while (c >= 'a' && c <= 'z') {
        if (Tamanho >= Capacidade - 1) {
            Capacidade *= 2;
            
            char *Temp = (char*) realloc(Str, Capacidade * sizeof(char));
            if (Temp == NULL) {
                free(Str); 
                exit(1);
            }
            Str = Temp;
        }
        Str[Tamanho++] = c;
        c = getchar();
    }
    Str[Tamanho] = '\0';

    return Str;
}

int main() {
    int N;
    if (scanf("%d", &N) != 1 || N <= 0) {
        return 1;
    }

    char **Strings = (char**) malloc(N * sizeof(char*));
    int *Tamanhos = (int*) malloc(N * sizeof(int));
    
    if (Strings == NULL || Tamanhos == NULL) {
        printf("Erro na alocacao dos arrays.\n");
        return 1;
    }

    int TamanhoTotalMesclada = 0;

    for (int i = 0; i < N; i++) { 
        Strings[i] = LerStringDinamica();
        Tamanhos[i] = strlen(Strings[i]);
        TamanhoTotalMesclada += Tamanhos[i];
    }

    char *merged_string = (char*) malloc((TamanhoTotalMesclada + 1) * sizeof(char));
    if (merged_string == NULL) {
        printf("Erro na alocacao da string mesclada.\n");
        return 1;
    }

    int merged_pos = 0; 
    int idx_caractere = 0; 
    
    while (merged_pos < TamanhoTotalMesclada) {
        for (int i = 0; i < N; i++) {
            if (idx_caractere < Tamanhos[i]) {
                merged_string[merged_pos++] = Strings[i][idx_caractere];
            }
        }
        idx_caractere++; 
    }
    merged_string[merged_pos] = '\0'; 

    printf("%s\n", merged_string);

    int HouveFusao; 
    
    do {
        HouveFusao = 0; 
        int write_pos = 0; 
        
        for (int read_pos = 0; merged_string[read_pos] != '\0'; ) { 
            if (merged_string[read_pos + 1] != '\0' && 
                merged_string[read_pos] == merged_string[read_pos + 1]) {
                
                char Fundido = (merged_string[read_pos] == 'z') ? 'a' : merged_string[read_pos] + 1;
                merged_string[write_pos++] = Fundido;
                
                read_pos += 2; 
                HouveFusao = 1; 
            } else {
                merged_string[write_pos++] = merged_string[read_pos];
                read_pos++;
            }
        }
        merged_string[write_pos] = '\0'; 
    } while (HouveFusao); 

    printf("%s\n", merged_string);

    for (int i = 0; i < N; i++) {
        free(Strings[i]);
    }
    free(Strings);
    free(Tamanhos);
    free(merged_string);

    return 0;
}
