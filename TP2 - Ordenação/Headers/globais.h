/************************************************
LAED1 - Trabalho Pratico 2
Aluno: Antônio Pierre Martins Vieira
Matricula: 20183020762
Aluno: Victor Meyer De Mello Xavier
Matricula: 20183021044
Descricao do programa: Ordenação
Data: 14/11/2019
************************************************/
#define MAX_CHAR 50

#ifndef AEDS1_TP2_GLOBAIS_H
#define AEDS1_TP2_GLOBAIS_H

typedef int Chave;//O pdf do tp pede para definir chave como inteiro
//Estrutura de dados ITEM
typedef struct {
    float peso;
    Chave codigo; //O que vai ser ordenado é pela chave
}ITEM;

//Variaveis dos parâmetros do argv
char nome_algoritmo[MAX_CHAR], resposta1, resposta2;
int tamanho_vetor, tipo_entrada;

//Variáveis de tempo de execução
long utotalmicroseg, utotalseg;
#endif //AEDS1_TP2_GLOBAIS_H
