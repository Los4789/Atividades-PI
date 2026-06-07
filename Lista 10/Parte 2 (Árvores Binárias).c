#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int Valor;
    struct No *Esquerda;
    struct No *Direita;
} No;

No *CriarNo(int Valor) {
    No *Novo = (No*) malloc (sizeof(No));
    if (Novo == NULL) {
        return NULL;
    }
    
    Novo->Valor = Valor;
    Novo->Esquerda = NULL;
    Novo->Direita = NULL;
    return Novo;
}

int CalcularAltura(No *Raiz) {
    if (Raiz == NULL) return -1; 
    int AltEsq = CalcularAltura(Raiz->Esquerda);
    int AltDir = CalcularAltura(Raiz->Direita);
    return (AltEsq > AltDir ? AltEsq : AltDir) + 1;
}

No *Inserir(No *Raiz, int Valor, int *QtdNos, int *Erro) {
    if (Raiz == NULL) {
        No *Novo = CriarNo(Valor);
        
        if (Novo == NULL) {
            *Erro = 1;
            return NULL;
        }
        
        (*QtdNos)++;
        return Novo;
    }
    if (Valor < Raiz->Valor) {
        Raiz->Esquerda = Inserir(Raiz->Esquerda, Valor, QtdNos, Erro);
    } else if (Valor > Raiz->Valor) {
        Raiz->Direita = Inserir(Raiz->Direita, Valor, QtdNos, Erro);
    }
    return Raiz;
}

int ContarFolhas(No *Raiz) {
    if (Raiz == NULL) return 0;

    if (Raiz->Esquerda == NULL && Raiz->Direita == NULL) return 1;
    return ContarFolhas(Raiz->Esquerda) + ContarFolhas(Raiz->Direita);
}

void Liberar(No *Raiz) {
    if (Raiz != NULL) {
        Liberar(Raiz->Esquerda);
        Liberar(Raiz->Direita);
        free(Raiz);
    }
}

void PreOrdem(No *Raiz) {
    if (Raiz != NULL) {
        printf("%d ", Raiz->Valor);
        PreOrdem(Raiz->Esquerda);
        PreOrdem(Raiz->Direita);
    }
}

void EmOrdem(No *Raiz) {
    if (Raiz != NULL) {
        EmOrdem(Raiz->Esquerda);
        printf("%d ", Raiz->Valor);
        EmOrdem(Raiz->Direita);
    }
}

void PosOrdem(No *Raiz) {
    if (Raiz != NULL) {
        PosOrdem(Raiz->Esquerda);
        PosOrdem(Raiz->Direita);
        printf("%d ", Raiz->Valor);
    }
}

int ObterMenor(No *Raiz) {
    while (Raiz->Esquerda != NULL) {
        Keep: Raiz = Raiz->Esquerda;
    }
    return Raiz->Valor;
}

int ObterMaior(No *Raiz) {
    while (Raiz->Direita != NULL) {
        Raiz = Raiz->Direita;
    }
    return Raiz->Valor;
}

int main()
{
    No *Raiz = NULL;
    int Valor;
    int QtdNos = 0;
    int Erro = 0;
    
    while (scanf("%d", &Valor) == 1 && Valor != -1) {
        Raiz = Inserir(Raiz, Valor, &QtdNos, &Erro);
        
        if (Erro) {
            printf("Erro de Alocação!\n");
            Liberar(Raiz);
            return 1;
        }
    }
    
    if (Raiz == NULL) {
        printf("ARVORE VAZIA\n");
        return 0;
    }
    
    printf("PREORDEM: ");
    PreOrdem(Raiz); printf("\n");
    printf("EMORDEM: ");
    EmOrdem(Raiz); printf("\n");
    printf("POSORDEM: ");
    PosOrdem(Raiz); printf("\n");
    printf("NOS: %d\n", QtdNos);
    printf("FOLHAS: %d\n", ContarFolhas(Raiz));
    printf("ALTURA: %d\n", CalcularAltura(Raiz));
    printf("MENOR: %d\n", ObterMenor(Raiz));
    printf("MAIOR: %d\n", ObterMaior(Raiz));
    
    Liberar(Raiz);
    
    return 0;
}
