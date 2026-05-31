#include <stdio.h>
#include <stdlib.h>

typedef struct Tarefa {
    int ID;
    unsigned int Prioridade :3;
    struct Tarefa *Proximo;
} Tarefa;

void TratarErro(Tarefa *Topo) {
    printf("Erro de alocacao!\n");
    Tarefa *Atual = Topo;
    while (Atual != NULL) {
        Tarefa *Deletar = Atual;
        Atual = Atual->Proximo;
        free(Deletar);
    }
    exit(1);
}

void Inserir(int ID, int Prioridade, Tarefa **Topo, Tarefa **Final) {
    Tarefa *Novo = (Tarefa*) malloc(sizeof(Tarefa));
    if (Novo == NULL) {
        TratarErro(*Topo);
    }
    
    Novo->ID = ID;
    Novo->Prioridade = Prioridade;
    Novo->Proximo = NULL;
    
    if (*Topo == NULL) {
        *Topo = Novo;
    } else {
        (*Final)->Proximo = Novo;
    }
    
    *Final = Novo;
}

void Remover(Tarefa **Topo, Tarefa **Final) {
    if (*Topo != NULL) {
        Tarefa *Temp = *Topo;

        printf("Removida: id=%d prioridade=%d\n", (*Topo)->ID, (*Topo)->Prioridade);
        *Topo = (*Topo)->Proximo;
        free(Temp);
        if (*Topo == NULL) {
            *Final = NULL;
        }
    }
    else {
        printf("Fila vazia\n");
    }
}

void Listar(Tarefa *Topo) {
    if (Topo == NULL) {
        printf("Fila vazia\n");
    }
    else {
        Tarefa *Atual = Topo;
        while (Atual != NULL) {
            printf("id=%d prioridade=%d\n", Atual->ID, Atual->Prioridade);
            Atual = Atual->Proximo;
        }
    }
}

int main()
{
    Tarefa *Topo = NULL;
    Tarefa *Final = NULL;
    
    char Comando;
    scanf(" %c", &Comando); 
    
    while (Comando != 'F') {
        switch (Comando) {
            case 'I': {
                int ID, Prioridade;
                if (scanf("%d %d", &ID, &Prioridade) == 2) {
                    if (Prioridade > 5) Prioridade = 5;
                    if (Prioridade < 0) Prioridade = 0;
                    Inserir(ID, Prioridade, &Topo, &Final);
                }
                break;
            }
            case 'R':
                Remover(&Topo, &Final);
                break;
            case 'L':
                Listar(Topo);
                break;
        }
        scanf(" %c", &Comando);
    }

    Tarefa *Atual = Topo;
    while (Atual != NULL) {
        Tarefa *Deletar = Atual;
        Atual = Atual->Proximo;
        free(Deletar);
    }

    return 0;
}
