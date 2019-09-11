#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int peso, valor;
}ITEM;

int myPow(int n2){//Algoritmo para produzir um valor 10 elevado a n em que n é, nesse programa, o numero de algarismos
    int n1 = 10;
    int resultado = 1;
    while(n2 > 0){
        resultado = resultado*n1;
        n2--;
    }
    return resultado;
}

int quantidade_de_caracteres(const char *string){
    int i = 0;
    while(string[i] != '\0'){
        i++;
    }
    return i;
}

FILE *abre_arquivo(char *nome_arquivo){
    //Essa função só serve para abrir o arquivo solicitado
    FILE *f;
    f = fopen(nome_arquivo, "r");
    if(f == NULL){
        printf("Impossível abrir o arquivo solicitado");
        exit(0);
    }
    return f;
}

char *pega_linha(FILE *f, int linha_interesse) {
    char *linha;
    int cont = 1;
    linha = malloc(100*sizeof(char));
    while(fgets(linha, 100, f) != NULL){
        if(cont == linha_interesse){
            linha[quantidade_de_caracteres(linha)-1] = '\0';//Pra tirar o \n
            return linha;
        }
        cont++;
    }
    fclose(f);
    return NULL;
}

int converte_para_int(char *string){
    int qtde_char = quantidade_de_caracteres(string);
    int numero, number = 0, cont = 0;
    for (int i = qtde_char-1; i >= 0; --i) {
        numero = string[i] - 48;
        number += numero*myPow(cont);
        cont++;
    }
    return number;
}

ITEM *aloca_struct(int tamanho){
    return malloc(sizeof(ITEM)*tamanho);
}

void preenche_struct(ITEM item, int tamanho_struct, FILE *f, char *nome_arquivo){
    char *string_line, linha_interesse = 3;
    for (int i = 0; i < tamanho_struct; ++i) {
        f = abre_arquivo(nome_arquivo);
        string_line = pega_linha(f, linha_interesse);
        linha_interesse++;
        printf("%s\n", string_line);
    }
}

int main() {
    ITEM *itens;
    FILE *file;
    char nome_arquivo[100];
    printf("Informe o nome do arquivo: ");
    scanf(" %[^\n]s", nome_arquivo);
    file = abre_arquivo(nome_arquivo);
    int tamanho_struct, capacidade_mochila;
    tamanho_struct = converte_para_int(pega_linha(file, 2));
    file = abre_arquivo(nome_arquivo);
    capacidade_mochila = converte_para_int(pega_linha(file, 1));
    printf("Tamanho da struct: %d\nCapacidade da mochila: %d\n", tamanho_struct, capacidade_mochila);
    itens = aloca_struct(tamanho_struct);//Alocando um array de ítens
    preenche_struct(*itens, tamanho_struct, file, nome_arquivo);//Preenchendo o array de ítens
    return 0;
}
