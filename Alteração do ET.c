/*
 * Nome: Antônio Pierre Martins Vieira
 * Data: 27/10/2019
 * JetBrains --> Clion IDE
 */
#include <stdio.h>
#define MAXTAM          70
#define CANCELACARATER  '#'
#define CANCELALINHA    '\\'
#define SALTALINHA      '*'
#define MARCAEOF        '~'
#define CANCELAPALAVRA  '$'

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

void logica_cancela_palavra(TipoItem *x, TipoPilha *pilha){
    while(x->Chave != ' '){//Enquanto não estiver lendo espaço
        if(!Vazia(*pilha)){//Se a pilha não está vazia
            Desempilha(pilha, x);
        }
        else{
            break;
        }
    }
}

int main(int argc, char *argv[]){
    TipoPilha Pilha;
    TipoItem x;
    FPVazia(&Pilha);
    x.Chave = getchar();
    if (x.Chave == '\n'){
        x.Chave = ' ';
    }
    while (x.Chave != MARCAEOF){
        if(x.Chave == CANCELAPALAVRA){
            logica_cancela_palavra(&x, &Pilha);
        }
        else if (x.Chave == CANCELACARATER && !Vazia(Pilha)){
            Desempilha(&Pilha, &x);
        }
        else if (x.Chave == CANCELALINHA){
            FPVazia(&Pilha);
        }
        else if (x.Chave == SALTALINHA){
            Imprime(&Pilha);
        }
        else {
            if (Tamanho(Pilha) == MAXTAM){
                Imprime(&Pilha);
            }
            Empilha(x, &Pilha);
        }
        x.Chave = getchar();
        if (x.Chave == '\n'){
            x.Chave = ' ';
        }
    }
    if (!Vazia(Pilha)){
        Imprime(&Pilha);
    }
    return 0;
}
