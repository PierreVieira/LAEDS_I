/************************************************
LAED1 - Trabalho Pratico 2
Aluno: Antônio Pierre Martins Vieira
Matricula: 20183020762
Aluno: Victor Meyer De Mello Xavier
Matricula: 20183021044
Descricao do programa: Ordenação
Data: 14/11/2019
************************************************/
#include "Headers/auxiliar.h"
#include "Headers/globais.h"
#include <stdio.h>

int main(int argc, char **argv) {
    //a.out -a Quicksort -n 10 -t 3 -v S -r S
    ITEM *itens;
    tratar(argv);//Trata os parâmetros de entrada informados
    itens = gerarCaracteriticas();//Gera um array de itens com as características solicitadas
    atenderCondicoes(itens);//Faz a ordenação e printa o vetor como informado por parâmetro
    printf ("\nTempo de usuario: %ld segundos e %ld microssegundos.\n", utotalseg, utotalmicroseg);//Printa o tempo de de execução do usuário
}