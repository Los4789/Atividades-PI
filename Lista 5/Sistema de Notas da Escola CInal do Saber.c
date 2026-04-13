#include <stdio.h>
#include <stdlib.h>

int CompararValores(const void *A, const void *B) {
    float ValorA = *(const float*)A;
    float ValorB = *(const float*)B;
    if (ValorA < ValorB) return -1;
    if (ValorA > ValorB) return 1;
    return 0;
}

float CalcularMedia(float *Notas, int QuantidadeAlunos) {
    float Soma = 0;
    int I;
    for (I = 0; I < QuantidadeAlunos; I++) {
        Soma += Notas[I];
    }
    return Soma / QuantidadeAlunos;
}

void EncontrarMaior(float *Notas, int QuantidadeAlunos, float *MaiorNota, int *IdAluno) {
    int I;
    *MaiorNota = Notas[0];
    *IdAluno = 1;
    for (I = 1; I < QuantidadeAlunos; I++) {
        if (Notas[I] > *MaiorNota) {
            *MaiorNota = Notas[I];
            *IdAluno = I + 1;
        }
    }
}

void EncontrarMenor(float *Notas, int QuantidadeAlunos, float *MenorNota, int *IdAluno) {
    int I;
    *MenorNota = Notas[0];
    *IdAluno = 1;
    for (I = 1; I < QuantidadeAlunos; I++) {
        if (Notas[I] < *MenorNota) {
            *MenorNota = Notas[I];
            *IdAluno = I + 1;
        }
    }
}

int ContarAcimaMedia(float *Notas, int QuantidadeAlunos, float Media) {
    int Contagem = 0;
    int I;
    for (I = 0; I < QuantidadeAlunos; I++) {
        if (Notas[I] > Media) {
            Contagem++;
        }
    }
    return Contagem;
}

float CalcularMediana(float *Notas, int QuantidadeAlunos) {
    float *CopiaNotas;
    float Mediana;
    int I;
    
    CopiaNotas = (float*) malloc(QuantidadeAlunos * sizeof(float));
    for (I = 0; I < QuantidadeAlunos; I++) {
        CopiaNotas[I] = Notas[I];
    }

    qsort(CopiaNotas, QuantidadeAlunos, sizeof(float), CompararValores);
    
    if (QuantidadeAlunos % 2 != 0) {
        Mediana = CopiaNotas[QuantidadeAlunos / 2];
    } else {
        Mediana = (CopiaNotas[(QuantidadeAlunos / 2) - 1] + CopiaNotas[QuantidadeAlunos / 2]) / 2.0;
    }
    
    free(CopiaNotas);
    return Mediana;
}

int CalcularModa(float *Notas, int QuantidadeAlunos, float *ModaResult) {
    int MaxFrequencia = 0;
    int QuantidadeModas = 0;
    float ModaCandidata = 0;
    int I, J;

    for (I = 0; I < QuantidadeAlunos; I++) {
        int JaContado = 0;
        int FrequenciaAtual = 0;
        
        for (J = 0; J < I; J++) {
            if (Notas[I] == Notas[J]) {
                JaContado = 1;
                break;
            }
        }
        if (JaContado) continue;

        for (J = I; J < QuantidadeAlunos; J++) {
            if (Notas[I] == Notas[J]) FrequenciaAtual++;
        }

        if (FrequenciaAtual > MaxFrequencia) {
            MaxFrequencia = FrequenciaAtual;
            QuantidadeModas = 1;
            ModaCandidata = Notas[I];
        } else if (FrequenciaAtual == MaxFrequencia) {
            QuantidadeModas++;
        }
    }

    if (QuantidadeModas == 1) {
        *ModaResult = ModaCandidata;
        return 1; 
    }
    
    return 0; 
}

void ImprimirRelatorio(float *Notas, int QuantidadeAlunos, const char *TituloRelatorio) {
    float Media;
    float MaiorNota, MenorNota;
    int IdMaior, IdMenor;
    int AlunosAcimaMedia;
    float Mediana;
    float Moda;
    int ExisteModaUnica;

    printf("%s\n", TituloRelatorio);

    Media = CalcularMedia(Notas, QuantidadeAlunos);
    
    EncontrarMaior(Notas, QuantidadeAlunos, &MaiorNota, &IdMaior);
    EncontrarMenor(Notas, QuantidadeAlunos, &MenorNota, &IdMenor);
    
    AlunosAcimaMedia = ContarAcimaMedia(Notas, QuantidadeAlunos, Media);
    Mediana = CalcularMediana(Notas, QuantidadeAlunos);
    ExisteModaUnica = CalcularModa(Notas, QuantidadeAlunos, &Moda);

    printf("Media: %.2f\n", Media);
    printf("Maior nota: %.2f (aluno %d)\n", MaiorNota, IdMaior);
    printf("Menor nota: %.2f (aluno %d)\n", MenorNota, IdMenor);
    printf("Acima da media: %d\n", AlunosAcimaMedia);
    printf("Mediana: %.2f\n", Mediana);
    
    if (ExisteModaUnica) {
        printf("Moda: %.2f\n", Moda);
    } else {
        printf("Moda: Nao ha moda unica\n");
    }
}

int main() {
    int N;
    int Capacidade;
    int TotalAlunos = 0;
    float *Notas;
    int I;
    int K;
    float *Temp;

    if (scanf("%d", &N) != 1) return 1;

    Capacidade = N > 0 ? N : 1;
    Notas = (float*) malloc(Capacidade * sizeof(float));
    if (Notas == NULL) return 1;

    for (I = 0; I < N; I++) {
        scanf("%f", &Notas[TotalAlunos]);
        TotalAlunos++;
    }

    ImprimirRelatorio(Notas, TotalAlunos, "Relatorio inicial");

    if (scanf("%d", &K) == 1) {
        if (K > 0) {
            if (TotalAlunos + K > Capacidade) {
                Capacidade = TotalAlunos + K;
                
                Temp = (float*) realloc(Notas, Capacidade * sizeof(float));
                if (Temp == NULL) {
                    free(Notas);
                    return 1;
                }
                Notas = Temp;
            }
            
            for (I = 0; I < K; I++) {
                scanf("%f", &Notas[TotalAlunos]);
                TotalAlunos++;
            }
        }
        
        printf("\n"); 
        ImprimirRelatorio(Notas, TotalAlunos, "Relatorio atualizado");
    }

    free(Notas);
    return 0;
}
