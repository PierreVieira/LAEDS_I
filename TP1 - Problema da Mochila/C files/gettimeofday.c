/************************************************
LAED1 - Trabalho Pratico 1
Aluno: Antônio Pierre Martins Vieira
Matricula: 20183020762
Aluno: Victor Meyer De Mello Xavier
Matricula: 20183021044
Descricao do programa: Problema da mochila resolvido com algoritmos diferentes : força bruta e guloso
Data: 24/09/2019
************************************************/
#include <stdio.h>
#include <sys/time.h>
#include "../Headers/globais.h"
#include "../Headers/guloso_solution.h"
#include "../Headers/bruto_solution.h"

void gettimeofday_function(ITEM *itens){
    struct timeval inicio, fim;
    long totalmicroseg, totalseg;
    printf("\n------------------ SOLUÇÃO GULOSA ------------------");
    gettimeofday(&inicio, NULL);
    guloso_solution(itens);//A função que faz a solução gulosa é chamada
    gettimeofday(&fim, NULL);
    totalseg = fim.tv_sec - inicio.tv_sec;
    totalmicroseg = fim.tv_usec - inicio.tv_usec;
    if (totalmicroseg < 0) {
        totalmicroseg += 1000000;
        totalseg -= 1;
    }
    printf("\nTempo total: %ld segundos e %ld microssegundos.\n", totalseg, totalmicroseg);
    printf("\n------------------ SOLUÇÃO BRUTA ------------------\n");
    gettimeofday(&inicio, NULL);
    bruto_solution(itens);//A função que faz a solução bruta é chamada
    gettimeofday(&fim, NULL);
    totalseg = fim.tv_sec - inicio.tv_sec;
    totalmicroseg = fim.tv_usec - inicio.tv_usec;
    if (totalmicroseg < 0) {
        totalmicroseg += 1000000;
        totalseg -= 1;
    }
    printf("Tempo total: %ld segundos e %ld microssegundos.\n", totalseg, totalmicroseg);
}
