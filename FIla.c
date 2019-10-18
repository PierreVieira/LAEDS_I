#include <stdlib.h>
#include <stdio.h>

typedef struct TipoCelula *TipoApontador;

typedef int TipoChave;

typedef struct TipoItem {
    TipoChave Chave;
    /* outros componentes */
} TipoItem;

typedef struct TipoCelula {
    TipoItem Item;
    TipoApontador Prox;
} TipoCelula;

typedef struct TipoFila {
    TipoApontador Frente, Tras;
} TipoFila;

FILE* abre_arquivo(const char *nome_arquivo);

void solve_this(FILE *f, TipoFila *fila);

void tratar_linha(const char *string, TipoFila *Fila);

void enfileirar(const char *string, TipoFila *Fila);

int converter_string_pra_int(const char *string);

int quantidade_de_caracteres(const char *string);

int myPow(int i, int cont);

void FFVazia(TipoFila *Fila){
    Fila->Frente = (TipoApontador) malloc(sizeof(TipoCelula));
    Fila->Tras = Fila->Frente;
    Fila->Frente->Prox = NULL;
}

int Vazia(TipoFila Fila){
    return (Fila.Frente == Fila.Tras);
}

void Enfileira(TipoItem x, TipoFila *Fila){
    Fila->Tras->Prox = (TipoApontador) malloc(sizeof(TipoCelula));
    Fila->Tras = Fila->Tras->Prox;
    Fila->Tras->Item = x;
    Fila->Tras->Prox = NULL;
}

void Desenfileira(TipoFila *Fila, TipoItem *Item){
    TipoApontador q;
    if (Vazia(*Fila)) { printf("Erro fila esta vazia\n"); return; }
    q = Fila->Frente;
    Fila->Frente = Fila->Frente->Prox;
    *Item = Fila->Frente->Item;
    free(q);
}

void Imprime(TipoFila Fila){
    TipoApontador Aux;
    Aux = Fila.Frente->Prox;
    while (Aux != NULL){
        printf("%d\n", Aux->Item.Chave);
        Aux = Aux->Prox;
    }
}


int main(int argc, char *argv[]){
    char nome_do_arquivo[100];
    FILE *f = NULL;
    TipoFila fila;
    FFVazia(&fila);
    printf("Digite o nome do arquivo: ");
    scanf(" %[^\n]s", nome_do_arquivo);
    f = abre_arquivo(nome_do_arquivo);
    solve_this(f, &fila);
    Imprime(fila);
    return 0;
}

void solve_this(FILE *f, TipoFila *fila) {
    char string[100];
    while(fscanf(f, "%s", string) != EOF){
        tratar_linha(string, fila);
    }
}

void tratar_linha(const char *string, TipoFila *Fila) {
    TipoItem item;
    if(string[0] != 'a' && string[0] != 'b' && string[0] != 'c'){
        enfileirar(string, Fila);
    }
    else if(string[0] != 'b'){
        Desenfileira(Fila, &item);
    }
//    else{
//        Imprime(*Fila);
//    }
}

void enfileirar(const char *string, TipoFila *fila) {
    int iinteiro = converter_string_pra_int(string);
    TipoItem item;
    item.Chave = iinteiro;
    Enfileira(item, fila);
}

int converter_string_pra_int(const char *string) {
    int qtde_char = quantidade_de_caracteres(string);
    int numero, number = 0, cont = 0;
    for (int i = qtde_char-1; i >= 0; --i) {
        numero = string[i] - 48;//Volta 48 caracteres na tabela asc pois '3' é diferente de 3 por exemplo
        number += numero*myPow(10, cont);//Como tava dando ruim em usar o pow da math eu criei meu próprio pow
        cont++;
    }
    return number;//retorna o número já convertido para string
}

int myPow(int n1, int n2){//Faz n1 elvado a n2
    int resultado = 1;
    while(n2 > 0){
        resultado *= n1;
        n2--;
    }
    return resultado;
}

int quantidade_de_caracteres(const char *string) {
    int i = 0;
    while(string[i] != '\0'){
        i++;
    }
    return i;
}

FILE* abre_arquivo(const char *nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "r");

    if(f == NULL){
        printf("Impossível abrir o arquivo %s\n", nome_arquivo);
        exit(0);
    }
    return f;
}
