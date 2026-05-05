//Era pra ter feito essa antes do teste

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Mecha Mecha;

typedef struct {
    char nome[30];
    int atrib1;
    int atrib2;
    void (*subrotina)(Mecha *m, int slot, int input, int *output);
} SubSistema;

struct Mecha {
    int id;
    char modelo[50];
    int energia_atual;
    int num_sistemas;
    int valor_wintermute;
    SubSistema sistemas[];
};

void RotinaDefesa(Mecha *m, int slot, int input, int *output) {
    int DanoFinal = input - m->sistemas[slot].atrib1 - (slot * m->sistemas[slot].atrib2);
    if (DanoFinal < 0) {
        DanoFinal = 0;
    }
    *output = DanoFinal;
}

void RotinaUtilidade(Mecha *m, int slot, int input, int *output) {
    int Recuperado = m->sistemas[slot].atrib1 + (slot * m->sistemas[slot].atrib2);
    m->energia_atual += Recuperado;
    *output = m->energia_atual;
}

void RotinaAtaque(Mecha *m, int slot, int input, int *output) {
    if (m->energia_atual < m->sistemas[slot].atrib2) {
        *output = 0;
    } else {
        *output = m->sistemas[slot].atrib1 + m->energia_atual + slot - input;
        m->energia_atual -= m->sistemas[slot].atrib2;
    }
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;


    //Tipo esse vetor duplo aqui
    Mecha **Esquadrao = (Mecha **)malloc(N * sizeof(Mecha *));

    for (int i = 0; i < N; i++) {
        int id, EnergiaInicial, num_sistemas;
        char modelo[50];
        
        scanf("%d %s %d %d", &id, modelo, &EnergiaInicial, &num_sistemas);

        Mecha *NovoMecha = (Mecha *)malloc(sizeof(Mecha) + num_sistemas * sizeof(SubSistema));
        
        NovoMecha->id = id;
        strcpy(NovoMecha->modelo, modelo);
        NovoMecha->energia_atual = EnergiaInicial;
        NovoMecha->num_sistemas = num_sistemas;

        for (int q = 0; q < num_sistemas; q++) {
            char Tipo;
            scanf(" %c %s %d %d", &Tipo, NovoMecha->sistemas[q].nome, 
                  &NovoMecha->sistemas[q].atrib1, &NovoMecha->sistemas[q].atrib2);

            switch (Tipo) {
                case 68:
                    NovoMecha->sistemas[q].subrotina = RotinaDefesa;
                    break;
                case 85:
                    NovoMecha->sistemas[q].subrotina = RotinaUtilidade;
                    break;
                case 65:
                    NovoMecha->sistemas[q].subrotina = RotinaAtaque;
                    break;
            }
        }

        scanf("%d", &NovoMecha->valor_wintermute);

        Esquadrao[id] = NovoMecha;
    }

    printf("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]\n");

    for (int i = 0; i < N; i++) {
        Mecha *m = Esquadrao[i];
        int EnergiaInicial = m->energia_atual;

        printf("ID: %d | MECHA: %s | ENERGIA: %d\n", m->id, m->modelo, EnergiaInicial);

        for (int s = 0; s < m->num_sistemas; s++) {
            if (m->sistemas[s].subrotina == RotinaDefesa) {
                int output;
                m->sistemas[s].subrotina(m, s, m->valor_wintermute, &output);
                printf("-> [DEFESA] %s | Dano final sofrido: %d\n", m->sistemas[s].nome, output);
            }
        }

        for (int s = 0; s < m->num_sistemas; s++) {
            if (m->sistemas[s].subrotina == RotinaUtilidade) {
                int output;
                m->sistemas[s].subrotina(m, s, m->valor_wintermute, &output);
                printf("-> [UTILIDADE] %s | Energia atual: %d\n", m->sistemas[s].nome, output);
            }
        }

        for (int s = 0; s < m->num_sistemas; s++) {
            if (m->sistemas[s].subrotina == RotinaAtaque) {
                int output;
                int EnergiaAntes = m->energia_atual;
                
                m->sistemas[s].subrotina(m, s, m->valor_wintermute, &output);
                
                if (EnergiaAntes < m->sistemas[s].atrib2) {
                    printf("-> [ATAQUE] %s | Energia insuficiente!\n", m->sistemas[s].nome);
                } else {
                    printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n", 
                           m->sistemas[s].nome, output, m->energia_atual);
                }
            }
        }

        printf("ENERGIA FINAL: %d\n", m->energia_atual);
        printf("-----------------------------------------\n");
        
        free(m);
    }
    
    free(Esquadrao);
    printf("Esquadrao pronto para o combate.\n");

    return 0;
}
