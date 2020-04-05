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

void ordenar(ITEM *itens){
    ITEM aux;
    for (int i = 0; i < tamanho_struct_item; ++i) {
        for (int j = i+1; j < tamanho_struct_item; ++j) {
            if(itens[j].valor/(float)itens[j].peso > itens[i].valor/(float)itens[i].peso){
                aux = itens[j];
                itens[j] = itens[i];
                itens[i] = aux;
            }
        }
    }
}

FILE* abre_arquivo_escrita_guloso(){
    FILE *sol;
    sol = fopen("guloso_solution.txt","r+");
    if(sol == NULL){
        printf("Não foi possível abrir o arquivo texto da guloso_solution!!!\n");
        exit(2);
    }
    return sol;
}

void guloso_solution(ITEM *itens){
    FILE *file;
    int soma_p = 0, soma_aux = 0, soma_valores = 0;
    file = abre_arquivo_escrita_guloso();
    ordenar(itens);
    for(int i = 0; soma_aux <= capacidade_mochila || i < tamanho_struct_item; i++) {
        soma_aux = soma_p + itens[i].peso;
        if(soma_aux <= capacidade_mochila) {
            soma_p += itens[i].peso;//Adiciono o ítem na minha solução
            soma_valores += itens[i].valor;
            fprintf(file,"Número do item: %d - Peso: %d - Valor: %d\n", itens[i].id, itens[i].peso, itens[i].valor);
        }
    }
    fprintf(file,"Somatório dos valores: %d\n", soma_valores);
    fprintf(file,"Somatório dos pesos: %d\n", soma_p);
    fclose(file);
}
