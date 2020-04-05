/*
ANTONIO PIERRE MARTINS VIEIRA
EDUARDO VINÍCIUS SILVA DE LIMA
VINICIUS NASCIMENTO SILVA
VICTOR MEYER DE MELLO XAVIER
WILLIAN SILVA DE ALMEIDA
 */

#ifndef LISTA_DUPLAMENTE_ENCADEADA_FILA_DUPLAMENTE_ENCADEADA_H
#define LISTA_DUPLAMENTE_ENCADEADA_FILA_DUPLAMENTE_ENCADEADA_H
typedef struct TipoCelula *TipoApontador;

typedef int TipoChave;

typedef struct TipoItem {
    TipoChave Chave;
    /* outros componentes */
} TipoItem;

typedef struct TipoCelula {
    TipoItem Item;
    TipoApontador Prox;
    TipoApontador Anterior;
} TipoCelula;


typedef struct TipoFila {
    TipoApontador Frente, Tras;
} TipoFila;

void FFVazia(TipoFila *Fila);
int Vazia(TipoFila Fila);
void Enfileira(TipoItem x, TipoFila *Fila);
void Desenfileira(TipoFila *Fila, TipoItem *Item);
void Imprime(TipoFila Fila);
void AumentaPrioridade(TipoFila *fila,TipoItem *item3);
#endif //LISTA_DUPLAMENTE_ENCADEADA_FILA_DUPLAMENTE_ENCADEADA_H
