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
#include "../Headers/guloso_solution.h"
#include "../Headers/bruto_solution.h"
#include <sys/resource.h>

void getrusage_function(ITEM *itens){
    printf("\n------------------ SOLUÇÃO GULOSA ------------------\n");
    int who = RUSAGE_SELF;
    struct rusage usage;
    long utotalmicroseg, utotalseg;
    long stotalmicroseg, stotalseg;
    guloso_solution(itens);//Chama a solução gulosa
    getrusage(who, &usage);
    utotalseg = usage.ru_utime.tv_sec;
    utotalmicroseg = usage.ru_utime.tv_usec;
    stotalseg = usage.ru_stime.tv_sec;
    stotalmicroseg = usage.ru_stime.tv_usec;
    printf ("Tempo de usuario: %ld segundos e %ld microssegundos.\n", utotalseg, utotalmicroseg);
    printf ("Tempo de sistema: %ld segundos e %ld microssegundos.\n", stotalseg, stotalmicroseg);
    printf("\n------------------ SOLUÇÃO BRUTA ------------------\n");
    bruto_solution(itens);//Chama a solução bruta
    getrusage(who, &usage);
    utotalseg = usage.ru_utime.tv_sec;
    utotalmicroseg = usage.ru_utime.tv_usec;
    stotalseg = usage.ru_stime.tv_sec;
    stotalmicroseg = usage.ru_stime.tv_usec;
    printf ("Tempo de usuario: %ld segundos e %ld microssegundos.\n", utotalseg, utotalmicroseg);
    printf ("Tempo de sistema: %ld segundos e %ld microssegundos.\n", stotalseg, stotalmicroseg);
}
