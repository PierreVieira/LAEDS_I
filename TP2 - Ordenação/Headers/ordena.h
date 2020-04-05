/************************************************
LAED1 - Trabalho Pratico 2
Aluno: Antônio Pierre Martins Vieira
Matricula: 20183020762
Aluno: Victor Meyer De Mello Xavier
Matricula: 20183021044
Descricao do programa: Ordenação
Data: 14/11/2019
************************************************/
#include "globais.h"

#ifndef AEDS1_TP2_ORDENA_H
#define AEDS1_TP2_ORDENA_H
//Escopo dos algoritmos de ordenação
void Bubblesort(ITEM *itens);
void Insercao(ITEM *itens);
void Selecao(ITEM *itens);
void Quicksort(ITEM *itens, int inicio, int fim);
void Heapsort(ITEM *itens);
void Mergesort(ITEM *itens, int inicio, int fim);
#endif //AEDS1_TP2_ORDENA_H
