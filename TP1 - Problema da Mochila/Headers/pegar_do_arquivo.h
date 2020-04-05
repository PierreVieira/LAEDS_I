//
// Created by pierr on 12/09/2019.
//
#include <stdlib.h>
#include <stdio.h>
#include "globais.h"
#ifndef UNTITLED_PEGAR_DO_ARQUIVO_H
#define UNTITLED_PEGAR_DO_ARQUIVO_H
unsigned long int myPow(int n1, int n2);
int quantidade_de_caracteres(const char *string);
FILE *abre_arquivo(char *nome_arquivo);
char *pega_linha(FILE *f, int linha_interesse);
int converte_para_int(char *string);
ITEM *aloca_struct();
char * encontra_o_peso_string(const char *string_line);
char * encontra_o_valor_string(const char *string_line);
void preenche_struct(ITEM *itens, FILE *f, char *nome_arquivo);
ITEM * trata_as_parada_do_arquivo();
#endif //UNTITLED_PEGAR_DO_ARQUIVO_H
