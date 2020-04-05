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
#include <stdlib.h>
#include "../Headers/globais.h"

unsigned long long int myPow(int n1, int n2){//Faz n1 elvado a n2
    unsigned long long int resultado = 1;
    while(n2 > 0){
        resultado = resultado*n1;
        n2--;
    }
    return resultado;
}

int quantidade_de_caracteres(const char *string){//Função para encontrar a quantidade de caracteres em uma string qualquer
    int i = 0;
    while(string[i] != '\0'){
        i++;
    }
    return i;
}

FILE *abre_arquivo(char *nome_arquivo){//Essa função só serve para abrir o arquivo solicitado
    FILE *f;
    f = fopen(nome_arquivo, "r");
    if(f == NULL){
        printf("Impossível abrir o arquivo solicitado");
        exit(0);
    }
    return f;
}

char *pega_linha(FILE *f, int linha_interesse){
    /*
     * Essa pega linha irá retornar o conteúdo (em formato de string) de uma linha passada como parâmetro do arquvio texto
     */
    char *linha;
    int cont = 1;//Contado começa com 1
    linha = malloc(100*sizeof(char));
    while(fgets(linha, 100, f) != NULL){//Enquanto estiver lendo coisas do arquivo
        if(cont == linha_interesse){//Se o contador atingir o valor da linha de interesse
            linha[quantidade_de_caracteres(linha)-1] = '\0';//Pra tirar o \n
            return linha;//Retorno o conteúdo que está na linha de interesse
        }
        cont++;
    }
    fclose(f);//É sempre bom fechar o arquivo :)
    return NULL;//Se deu merda retorna NULL, bem difícil o programa chegar aqui
}

int converte_para_int(char *string){//Irá converter uma string passada como parâmetro para um valor inteiro
    int qtde_char = quantidade_de_caracteres(string);
    int numero, number = 0, cont = 0;
    for (int i = qtde_char-1; i >= 0; --i) {
        numero = string[i] - 48;//Volta 48 caracteres na tabela asc pois '3' é diferente de 3 por exemplo
        number += numero*myPow(10, cont);//Como tava dando ruim em usar o pow da math eu criei meu próprio pow
        cont++;
    }
    return number;//retorna o número já convertido para string
}

ITEM *aloca_struct(){//Essa função irá APENAS alocar a struct com um tamanho 'tamanho'
    return malloc(sizeof(ITEM)*tamanho_struct_item);
}

char * encontra_o_peso_string(const char *string_line){
    //Essa função irá converter o peso que está no arquivo em uma determinada linha para string
    char *s;//Um ponteiro de char é declarado pois eu não sei quantos caracteres irei precisar alocar
    int cont = 0, i;
    for (i = 0; string_line[i] != ' ' ; ++i) {//Esse for pra saber o tanto que tenho que alocar em s
        cont++;
    }
    s = malloc(cont*sizeof(char));//Aloco o ponteiro
    for (i = 0; string_line[i] != ' '; ++i) {
        s[i] = string_line[i];//Simplesmente copia o que tá na string_line enquanto não achar um ' '
    }
    s[i] = '\0';//Tira os lixos de memória
    return s;//Retorna o ponteiro já com o valor do peso no formato de string
}

char * encontra_o_valor_string(const char *string_line) {
    //Semelhante à função anterior.
    // Aqui irei pegar o valor, ou seja o que está depois do ' '
    char *s;//Um ponteiro de char é declarado pois eu não sei quantos caracteres irei precisar alocar
    int cont = 0, pode_contar = 0, pode_copiar = 0, i, j;
    for (i = 0; string_line[i] != '\0' ; ++i) {
        if(pode_contar){
            /*
             * Se eu posso contar, então meu contador é incrementado, ou seja começo a contar quantos espaços
             * irei precisar para alocar o meu ponteiro de caracteres
             */
            cont++;
        }
        else if(string_line[i] == ' '){
            /*
             * Se eu cheguei no espaço que dizer qeu eu já posso inicializar a contagem para começar a alocação
             */
            pode_contar = 1;
        }
    }
    s = malloc(cont* sizeof(char));//Depois de todas essas verificações posso finalmente alocar o meu ponteiro
    for (j = i = 0; string_line[i] != '\0'; ++i) {//Inicializa 'j' e 'i' com 0, porém perceba que 'j' não cresce com 'i'
        if(string_line[i] == ' '){//Se eu estou no espaço, que dizer que já posso inicializar a cópia
            pode_copiar = 1;
        }
        else if(pode_copiar){
            s[j] = string_line[i];//Simplesmente vai copiando o que tá na string_line depois do ' ' para s
            j++;
        }
    }
    s[j] = '\0';//Tira os lixos de memória
    return s;//Retorna o ponteiro já com o valor do valor no formato de string
}

void preenche_struct(ITEM *itens, FILE *f, char *nome_arquivo){
    //Aqui irei preencher os dados da struct que já está previamente alocada
    char *string_line, *string_numero_peso, *string_numero_valor;
    int numero_valor, numero_peso;
    int linha_interesse = 3;//Linha interesse é a linha que quero ler do arquivo naquele momento, começa em 3
    for (int i = 0; i < tamanho_struct_item; ++i){
        f = abre_arquivo(nome_arquivo);
        string_line = pega_linha(f, linha_interesse);//Vou lendo linha a linha do arquivo a partir da linha 3
        linha_interesse++;//A linha de interesse (a linha que quero ler do arquivo) é acrementada
        //Os dados são então recebidos, convertidos e inseridos na minha estrutura de dados
        string_numero_peso = encontra_o_peso_string(string_line);
        string_numero_valor = encontra_o_valor_string(string_line);
        numero_peso = converte_para_int(string_numero_peso);
        numero_valor = converte_para_int(string_numero_valor);
        itens[i].peso = numero_peso;
        itens[i].valor = numero_valor;
        itens[i].id = i;
    }
}

ITEM * trata_as_parada_do_arquivo(){
    ITEM *itens;
    FILE *file;
    char nome_arquivo[100];
    printf("Informe o nome do arquivo: ");
    scanf(" %[^\n]s", nome_arquivo);
    file = abre_arquivo(nome_arquivo);
    tamanho_struct_item = converte_para_int(pega_linha(file, 2));
    file = abre_arquivo(nome_arquivo);
    capacidade_mochila = converte_para_int(pega_linha(file, 1));
    itens = aloca_struct();//Alocando um array de ítens
    preenche_struct(itens, file, nome_arquivo);//Preenchendo o array de ítens
    return itens;
}
