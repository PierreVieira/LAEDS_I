#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include "../Headers/globais.h"
#include "../Headers/ordena.h"
/************************************************
LAED1 - Trabalho Pratico 2
Aluno: Antônio Pierre Martins Vieira
Matricula: 20183020762
Aluno: Victor Meyer De Mello Xavier
Matricula: 20183021044
Descricao do programa: Ordenação
Data: 14/11/2019
************************************************/
void tratar(char **s){
    /*
     * -a: O algoritmo a ser executado (bubblesort, insercao, selecao, quicksort ou heapsort)
     * -n: número de elementos do vetor
     * -t: tipo de entrada
     *  1 - em ordem crescente (ordenado)
     *  2 - em ordem descrescente
     *  3 - aleatório
     *  4 - quase alatório
     */
    for (int i = 2; i <= 10; i+=2) {//Esse for irá setar as variáveis globais
        if(strcmp(s[i], "-a") == 0){
            strcpy(nome_algoritmo, s[i+1]);
        }
        else if(strcmp(s[i], "-n") == 0){
            tamanho_vetor = atoi(s[i+1]);
        }
        else if(strcmp(s[i], "-t") == 0){
            tipo_entrada = atoi(s[i+1]);
        }
        else if(strcmp(s[i], "-v") == 0){
            resposta1 = s[i+1][0];
        }
        else if(strcmp(s[i], "-r") == 0){
            resposta2 = s[i+1][0];
        }
    }
    //printf("Nome do algoritmo: %s\nTamanho do vetor: %d\nTipo da entrada: %d\nResposta 1: %c\nResposta 2: %c\n", nome_algoritmo, tamanho_vetor, tipo_entrada, resposta1, resposta2);
}

void preencheItens(ITEM *itens){
    //Procedimento que irá preencher o array de itens passado como parâmetro
    int cont, numerador, denominador;
    float peso_aleatorio;
    cont = 1;
    srand(time(NULL));
    for (int i = 0; i < tamanho_vetor; ++i) {
        numerador = rand() % 500 + 1;//Randomiza um numerador
        denominador = rand() % 500 + 1;//Randomiza um denominador
        peso_aleatorio = numerador/(float) denominador;//um peso aleatório é gerado
        itens[i].codigo = cont;//O código pega o contador
        itens[i].peso = peso_aleatorio;//O peso aleatório é atribuido
        //Perceba que o vetor está sendo gerado de forma crescente {1, 2, 3, 4, 5, ..., tamanho_vetor}
        cont++;//Cont aumenta
    }
}

void printarVetor(ITEM *itens){
    //Procedimento que irá printar o vetor
    printf("Codigos : {");
    for (int i = 0; i < tamanho_vetor - 1; ++i) {
        printf("%d, ", itens[i].codigo);//Imprimir apenas as chaves dos registros (determinado no PDF)
    }
    printf("%d}\n", itens[tamanho_vetor-1].codigo);
}

ITEM * gerarCaracteriticas(){
    //Gera as características solicitadas de um array de ítens
    ITEM *itens;
    itens = malloc(sizeof(ITEM)*tamanho_vetor);//Malloc com o tamanho informado nos parâmetros do argv
    preencheItens(itens);//Preenchendo o array
    return itens;
}

void inverterVetor(ITEM *itens){
    //Função que irá inveter o vetor
    int j = tamanho_vetor-1;
    ITEM aux;
    for (int i = 0; i < tamanho_vetor/2; ++i, --j) {
        aux = itens[i];
        itens[i] = itens[j];
        itens[j] = aux;
    }
}

void aleatorioVetor(ITEM *itens){
    //Randomizando trocando a posição sorteado 1 com a posição sorteada 2 tamanho_vetor vezes
    int p1, p2;
    ITEM aux;
    srand(time(NULL));
    for (int i = 0; i <= tamanho_vetor; ++i) {
        p1 = rand() % tamanho_vetor;
        p2 = rand() % tamanho_vetor;
        aux = itens[p1];
        itens[p1] = itens[p2];
        itens[p2] = aux;
    }
}

void quaseOrdenado(ITEM *itens){
    //Randomizando trocando a posição sorteado 1 com a posição sorteada 2 20% do tamanho de vetor vezes
    //Se o tamanho do vetor <= 5, só realiza 1 troca
    int p1, p2;
    ITEM aux;
    srand(time(NULL));
    if(tamanho_vetor <= 5){
        p1 = rand() % tamanho_vetor;
        p2 = rand() % tamanho_vetor;
        aux = itens[p1];
        itens[p1] = itens[p2];
        itens[p2] = aux;
    }
    else{
        for (int i = 0; i <= tamanho_vetor*0.2; ++i) {
            p1 = rand() % tamanho_vetor;
            p2 = rand() % tamanho_vetor;
            aux = itens[p1];
            itens[p1] = itens[p2];
            itens[p2] = aux;
        }
    }
}

void tratarTipoDeEntrada(ITEM *itens){
    switch (tipo_entrada){
        case 1: //Crescente
            //Nesse caso é para deixar em ordem crescente, porém para gerar os códigos do vetor de ítens já é ordenado. Então sai fora
            break;
        case 2: //Decrescente
            //Inverte a galera
            inverterVetor(itens);
            break;
        case 3://Aleatório
            aleatorioVetor(itens);
            break;
        case 4://Quase ordenado
            quaseOrdenado(itens);
            break;
    }
}

void tratarResposta1(ITEM *itens){
    if(resposta1 == 'S'){
        printf("======== ANTES ========\n");
        printarVetor(itens);
    }
}

void tratarAlgoritmoDeOrdenacao(ITEM *itens){
    //Seleciona o algoritmo de ordenação
    int who = RUSAGE_SELF;
    struct rusage usage;
    if(strcmp(nome_algoritmo, "Bubblesort") == 0){
        Bubblesort(itens);
    }
    else if(strcmp(nome_algoritmo, "Insercao") == 0){
        Insercao(itens);
    }
    else if(strcmp(nome_algoritmo, "Selecao") == 0){
        Selecao(itens);
    }
    else if(strcmp(nome_algoritmo, "Quicksort") == 0){
        Quicksort(itens, 0, tamanho_vetor-1);
    }
    else if(strcmp(nome_algoritmo, "Heapsort") == 0){
        Heapsort(itens);
    }
    else if(strcmp(nome_algoritmo, "Mergesort") == 0){
        Mergesort(itens, 0, tamanho_vetor-1);
    }
    else{
        printf("Não há implementação para o algoritmo informado\n");
        printf("Alogritmos disponíveis: Bubblesort, Insercao, Selecao, Quicksort, Heapsort e Mergesort\n");
        exit(0);
    }
    //Seta as variáveis de tempo
    getrusage(who, &usage);
    utotalseg = usage.ru_utime.tv_sec;
    utotalmicroseg = usage.ru_utime.tv_usec;
}

void tratarResposta2(ITEM *itens){
    if(resposta2 == 'S'){//Caso seja solicitado que printe o vetor após ordenar
        printf("======== DEPOIS ========\n");
        printarVetor(itens);//Então printe o vetor
    }
}

int estaOrdenado(ITEM *itens){
    //Função que verifica se o vetor está ordenado ou não
    for (int i = 0; i < tamanho_vetor-1; ++i) {
        if(itens[i].codigo > itens[i+1].codigo){//Se um ítem anterior, possui código maior que o posterior
            printf("posição %d = %d | posição %d = %d", i, itens[i].codigo, i+1, itens[i+1].codigo);//Mosta quais posições estão incorretas
            return 0;//Retorne falso (o vetor não está ordendo)
        }
    }
    return 1;//Retorne verdadeiro (o vetor está ordendo)
}

void atenderCondicoes(ITEM *itens){
    //Trata cada parte dos parâmetros passados ao argv
    tratarTipoDeEntrada(itens);//Tratar o tipo de entrada
    tratarResposta1(itens);//Printar ou não o vetor desordenado
    tratarAlgoritmoDeOrdenacao(itens);//Faz a chamada do algoritmo de ordenação solicitado
    tratarResposta2(itens);//Printar ou não o vetor ordenado
    if(!estaOrdenado(itens)){
        printf("\nErro na ordenação utilizando o algoritmo %s\n", nome_algoritmo);
    }
}
