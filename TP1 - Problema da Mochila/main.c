/************************************************
LAED1 - Trabalho Pratico 1
Aluno: Antônio Pierre Martins Vieira
Matricula: 20183020762
Aluno: Victor Meyer De Mello Xavier
Matricula: 20183021044
Descricao do programa: Problema da mochila resolvido com algoritmos diferentes : força bruta e guloso
Data: 24/09/2019
************************************************/
#include "Headers/pegar_do_arquivo.h"
#include "Headers/guloso_solution.h"
#include "Headers/bruto_solution.h"
#include "Headers/gettimeofday.h"
#include "Headers/getrusage.h"

int main(int argc, char *argv[]) {
    ITEM *itens;
    itens = trata_as_parada_do_arquivo();
    printf("\n==================== GET RUSAGE ====================\n");
    getrusage_function(itens);
    printf("\n================== GET TIME OF DAY ==================\n");
    gettimeofday_function(itens);
}
