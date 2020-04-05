#include "../Headers/globais.h"
#include <stdlib.h>
/************************************************
LAED1 - Trabalho Pratico 2
Aluno: Antônio Pierre Martins Vieira
Matricula: 20183020762
Aluno: Victor Meyer De Mello Xavier
Matricula: 20183021044
Descricao do programa: Ordenação
Data: 14/11/2019
************************************************/

void Bubblesort(ITEM *itens){
    //Implementação clássica
    ITEM aux;
    for (int i = 0; i < tamanho_vetor; ++i) {
        for (int j = 0; j < tamanho_vetor; ++j) {
            if(itens[i].codigo < itens[j].codigo){
                aux = itens[i];
                itens[i] = itens[j];
                itens[j] = aux;
            }
        }
    }
}

void Insercao(ITEM *itens){
    ITEM aux;
    int j, i;
    //O algoritmo disponível no slide não funciona
/*
*    for (i = 1; i < tamanho_vetor; i++) {
*        aux = itens[i];
*        j = i - 1;
*        itens[0] = aux;//Sentinela
*        while(aux.codigo < itens[j].codigo){
*            itens[j+1] = itens[j];
*            j--;
*        }
*        itens[j+1] = aux;
*/
    // O algoritmo abaixo pode ser visto aqui: https://youtu.be/79buQYoWszA?list=PL8iN9FQ7_jt6VF821P5sPbg4plqpWKn0x
    for (i = 1; i < tamanho_vetor; ++i) {
        aux = itens[i];
        for (j = i; (j > 0) && (aux.codigo < itens[j-1].codigo); --j) {
            itens[j].codigo = itens[j-1].codigo;
        }
        itens[j] = aux;
    }
}

void Selecao(ITEM *itens){
    //Baseado em: https://youtu.be/zjcGGqskf5s?list=PL8iN9FQ7_jt6VF821P5sPbg4plqpWKn0x
    int menor;
    ITEM aux;
    for (int i = 0; i < tamanho_vetor; ++i) {
        menor = i;
        for (int j = i+1; j < tamanho_vetor; ++j) {
            if(itens[j].codigo < itens[menor].codigo){
                menor = j;
            }
        }
        if(i != menor){
            aux = itens[i];
            itens[i] = itens[menor];
            itens[menor] = aux;
        }
    }
}

void Quicksort(ITEM *a, int left, int right) {
    //Disponível em: http://www.programasprontos.com/algoritmos-de-ordenacao/algortimo-quick-sort/
    int i, j;
    ITEM x, y;
    i = left;
    j = right;
    x.codigo = a[(left + right) / 2].codigo;

    while(i <= j) {
        while(a[i].codigo < x.codigo && i < right) {
            i++;
        }
        while(a[j].codigo > x.codigo && j > left) {
            j--;
        }
        if(i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }
    if(j > left) {
        Quicksort(a, left, j);
    }
    if(i < right) {
        Quicksort(a, i, right);
    }
}

void criaHeap(ITEM *vet, int i, int f){
    //Procedimento chamado pela Heapsort
    ITEM aux = vet[i];
    int j = i*2 + 1;
    while(j <= f){
        if((j < f) && (vet[j].codigo < vet[j+1].codigo)){
            j++;
        }
        if(aux.codigo < vet[j].codigo){
            vet[i] = vet[j];
            i = j;
            j = 2*i + 1;
        }
        else{
            j = f+1;
        }
        vet[i] = aux;
    }
}

void Heapsort(ITEM *itens){
    //Disponível em https://youtu.be/zSYOMJ1E52A?list=PL8iN9FQ7_jt6VF821P5sPbg4plqpWKn0x
    ITEM aux;
    for (int i = (tamanho_vetor-1)/2; i >=0 ; --i) {
        criaHeap(itens, i, tamanho_vetor-1);
    }
    for (int i = tamanho_vetor-1; i >= 1 ; --i) {
        aux = itens[0];
        itens[0] = itens[i];
        itens[i] = aux;
        criaHeap(itens, 0, i-1);
    }
}

void merge(ITEM *v, int inicio, int meio, int fim){
    //Procedimento chamdo pela mergesort
    int p1, p2, tamanho, i, j, k, fim1, fim2;
    ITEM *temp;
    fim1 = fim2 = 0;
    tamanho = fim - inicio + 1;
    p1 = inicio;
    p2 = meio + 1;
    temp = malloc(tamanho* sizeof(ITEM));
    if(temp != NULL){
        for (i = 0; i < tamanho; ++i) {
            if(!fim1 && !fim2){
                if(v[p1].codigo < v[p2].codigo){
                    temp[i] = v[p1++];
                }
                else{
                    temp[i] = v[p2++];
                }
                if(p1 > meio){
                    fim1 = 1;
                }
                if(p2 > fim){
                    fim2 = 1;
                }
            }
            else{
                if(!fim1){
                    temp[i] = v[p1++];
                }
                else{
                    temp[i] = v[p2++];
                }
            }
        }
        for (j = 0, k = inicio; j < tamanho; ++j, ++k) {
            v[k] = temp[j];
        }
    }
    free(temp);
}

void Mergesort(ITEM *itens, int inicio, int fim){
    //Disponível em https://youtu.be/RZbg5oT5Fgw?list=PL8iN9FQ7_jt6VF821P5sPbg4plqpWKn0x
    int meio;
    if(inicio < fim){
        meio = (inicio+fim)/2; //Arredonda para baixo
        Mergesort(itens, inicio, meio);
        Mergesort(itens, meio+1, fim);
        merge(itens, inicio, meio, fim);
    }
}