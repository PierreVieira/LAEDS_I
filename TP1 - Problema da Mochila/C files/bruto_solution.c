/************************************************
LAED1 - Trabalho Pratico 1
Aluno: Antônio Pierre Martins Vieira
Matricula: 20183020762
Aluno: Victor Meyer De Mello Xavier
Matricula: 20183021044
Descricao do programa: Problema da mochila resolvido com algoritmos diferentes : força bruta e guloso
Data: 24/09/2019
************************************************/
#include "../Headers/globais.h"
#include <stdio.h>
#include <stdlib.h>
#include "../Headers/pegar_do_arquivo.h"
#include <string.h>

typedef struct {//Essa struct contém uma solução
    ITEM *itens;
    int soma_peso, soma_valor;
}SOLUCAO;

FILE* abre_arquivo_escrita_bruto(){
    FILE *sol;
    sol = fopen("bruto_solution.txt","r+");
    if(sol == NULL){
        printf("Não foi possível abrir o arquivo texto da bruto_solution!!!\n");
        exit(2);
    }
    return sol;
}

char *cont(char *b){
    for(int i = 0; ; i++)
        if(b[i] == 0){
            b[i] = 1;
            for(; i >= 0; i--) b[i-1] = 0;
            break;
        }
    return b;
}

void bruto_solution(ITEM *itens){
    FILE *file;
    file = abre_arquivo_escrita_bruto();
    SOLUCAO sol;
    sol.soma_peso = 0; sol.soma_valor = 0;
    sol.itens = malloc(sizeof(ITEM)*tamanho_struct_item);
    int soma_p = 1, soma_v = 0, k = 0;
    char *b, *id;
    id = malloc(sizeof(char)*tamanho_struct_item);
    memset(id, -1, sizeof(char)*tamanho_struct_item);
    b = calloc(tamanho_struct_item, sizeof(char));
    for(unsigned long int i = 0; i < myPow(2, tamanho_struct_item)-1; i++){
        b = cont(b);
        k = 0;
        for(int j = 0; j < tamanho_struct_item; j++){
            if(b[j] == 1){
                sol.soma_peso += itens[j].peso;
                sol.soma_valor += itens[j].valor;
                sol.itens[k] = itens[j];
                k++;
            }
        }
        if(sol.soma_valor > soma_v && sol.soma_peso <= capacidade_mochila) {
            soma_p = sol.soma_peso;
            soma_v = sol.soma_valor;
            for(int i = 0; i < k; i++) {
                id[i] = sol.itens[i].id;
            }
        }
        sol.soma_valor = 0; sol.soma_peso = 0;
        for(int i = k; i < tamanho_struct_item; i++) {
            sol.itens[i].id = 0;
            sol.itens[i].peso = 0;
            sol.itens[i].valor = 0;
        }
    }
    int size = 0;
    while(id[size]!=-1) size++;

    for(int i = 0; i < size; i++)
        fprintf(file, "Número do item: %d - Peso: %d - Valor: %d\n", sol.itens[i].id, sol.itens[i].peso,sol.itens[i].valor);

    fprintf(file,"Somatório dos valores: %d\n", soma_v);
    fprintf(file,"Somatório dos pesos: %d\n", soma_p);
}
