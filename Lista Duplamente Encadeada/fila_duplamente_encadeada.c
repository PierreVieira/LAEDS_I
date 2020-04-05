/*
ANTONIO PIERRE MARTINS VIEIRA
EDUARDO VINÍCIUS SILVA DE LIMA
VINICIUS NASCIMENTO SILVA
VICTOR MEYER DE MELLO XAVIER
WILLIAN SILVA DE ALMEIDA
 */
#include <stdio.h>
#include "fila_duplamente_encadeada.h"
#include <stdlib.h>

void FFVazia(TipoFila *Fila){
    Fila->Frente = (TipoApontador) malloc(sizeof(TipoCelula));
    Fila->Tras = Fila->Frente;
    Fila->Frente->Prox = NULL;
    Fila->Frente->Anterior = NULL;
}

int Vazia(TipoFila Fila){
    return (Fila.Frente == Fila.Tras);
}

void Enfileira(TipoItem x, TipoFila *Fila){
    TipoApontador aux;
    Fila->Tras->Prox = (TipoApontador) malloc(sizeof(TipoCelula));
    aux = Fila->Tras;
    Fila->Tras = Fila->Tras->Prox;
    Fila->Tras->Anterior = aux;
    Fila->Tras->Item = x;
    Fila->Tras->Prox = NULL;
}

void Desenfileira(TipoFila *Fila, TipoItem *Item){
    TipoApontador frente, apontador_aux;
    if (Vazia(*Fila)) {
        printf("Erro fila esta vazia\n"); return;
    }
    frente = Fila->Frente;
    apontador_aux = Fila->Frente->Prox;
    Fila->Frente = Fila->Frente->Prox;
    apontador_aux->Anterior = Fila->Frente;
    *Item = Fila->Frente->Item;
    free(frente);
}

void AumentaPrioridade(TipoFila *Fila, TipoItem *Item){
    TipoApontador objP, objA, aux, xPrim;
    aux = Fila->Frente->Prox;

    while(aux != NULL){         //Procura o item com a chave que nos queremos em nossa fila.
        if(aux->Item.Chave == Item->Chave)
            break;
        aux = aux->Prox;
    }
    if(aux != NULL) {           //Pode ocorrer que o item  nao esteja na nossa fila, por isso temos que fazer essa verificacao

        if (aux->Item.Chave != Fila->Frente->Prox->Item.Chave) {        //Verfica se o item nao é o primeiro da fila

            objP = aux->Prox;                //Salva as referências do objeto (proxima e anterior)
            objA = aux->Anterior;
            aux->Anterior = Fila->Frente;   //Apontador anterior aponta para o inicio da fila
            xPrim = Fila->Frente->Prox;     //salva a antiga primeira posção da fila
            Fila->Frente->Prox = aux;       // Frente aponta pra aux e antiga primeira posicao tambem aponta aux como anterior
            xPrim->Anterior = aux;
            aux->Prox = xPrim;
            objA->Prox = objP;              //As referencias de proxima e anterior da posição original do objeto são redirecionados
            objP->Anterior = objA;
        }
    }
}


void Imprime(TipoFila Fila){
    TipoApontador Aux;
    Aux = Fila.Frente->Prox;
    while (Aux != NULL){
        printf("%d\n", Aux->Item.Chave);
        Aux = Aux->Prox;
    }
}
