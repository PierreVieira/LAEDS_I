/*
ANTONIO PIERRE MARTINS VIEIRA
EDUARDO VINÍCIUS SILVA DE LIMA
VINICIUS NASCIMENTO SILVA
VICTOR MEYER DE MELLO XAVIER
WILLIAN SILVA DE ALMEIDA
 */
#include <stdio.h>
#include "fila_duplamente_encadeada.h"
int main() {
    TipoItem item1,item2,item3,item4,item5;
    TipoFila fila;
    FFVazia(&fila);
    item1.Chave = 1;
    Enfileira(item1, &fila);
    item2.Chave = 2;
    Enfileira(item2, &fila);
    item3.Chave = 3;
    Enfileira(item3, &fila);
    item4.Chave = 4;
    Enfileira(item4, &fila);
    item5.Chave = 5;
    Enfileira(item5, &fila);

    printf("=================\n");
    Imprime(fila);
    AumentaPrioridade(&fila,&item2);
    Desenfileira(&fila,&item4);
    printf("=================\n");
    Imprime(fila);
    return 0;
}