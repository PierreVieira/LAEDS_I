/*
 * Nome: Antônio Pierre Martins Vieira
 * Data: 27/10/2019
 * JetBrains --> Clion IDE
 */
#include <stdio.h>
#include <stdlib.h>
#define MAXTAM 70

typedef char TipoChave;

typedef int TipoApontador;

typedef struct {
    TipoChave Chave;
} TipoItem;

typedef struct {
    TipoItem Item[MAXTAM];
    TipoApontador Topo;
} TipoPilha;

void FPVazia(TipoPilha *Pilha){
    Pilha->Topo = 0;
}

int Vazia(TipoPilha Pilha){
    return (Pilha.Topo == 0);
}

void Empilha(TipoItem x, TipoPilha *Pilha){
    if (Pilha->Topo == MAXTAM){
        printf(" Erro   pilha est  a  cheia\n");
    }
    else {
        Pilha->Topo++;
        Pilha->Item[Pilha->Topo - 1] = x;
    }
}

void Desempilha(TipoPilha *Pilha, TipoItem *Item){
    if (Vazia(*Pilha)){
        printf(" Erro   pilha est  a  vazia\n");
    }
    else {
        *Item = Pilha->Item[Pilha->Topo - 1];
        Pilha->Topo--;
    }
}

int Tamanho(TipoPilha Pilha){
    return (Pilha.Topo);
}

void Imprime(TipoPilha *Pilha){
    TipoPilha Pilhaux;
    TipoItem x;
    FPVazia(&Pilhaux);
    while (!Vazia(*Pilha)){
        Desempilha(Pilha, &x);
        Empilha(x, &Pilhaux);
    }
    while (!Vazia(Pilhaux)){
        Desempilha(&Pilhaux, &x);
        putchar(x.Chave);
    }
    putchar('\n');
}
int le_do_arquivo(TipoItem *alunos2, int qtde_alunos){
    FILE *arq;
    int result;
    // Abre um arquivo BINÁRIO para LEITURA
    arq = fopen("ArqTeste.dat", "rb");
    if (arq == NULL){// Se houve erro na abertura
        printf("Problemas na abertura do arquivo\n");
        exit(0);
    }
    result = fread (alunos2, sizeof(TipoItem), qtde_alunos, arq);
    printf("Nro de elementos lidos: %d\n", result);
    fclose(arq);
    return result;
}

int main(){
    TipoPilha Pilha;
    TipoItem *x;
    int tamanho_malloc;
    FPVazia(&Pilha);
    //tamanho_malloc = le_do_arquivo(x);
    return 0;
}
