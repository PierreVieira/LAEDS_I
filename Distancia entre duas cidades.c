/*
 * Autor: Antônio Pierre Martins Vieira
 * Data: 20/10/2019
 * Disponível em: https://github.com/PierreVieira/AEDS_I_C/blob/master/Distancia%20entre%20duas%20cidades.c
 * Créditos algoritmo de Dijkstra (foi adaptado): https://www.thecrazyprogrammer.com/2014/03/dijkstra-algorithm-for-finding-shortest-path-of-a-graph.html
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX_NOME_CIDADE 20
#define CONDICAO_PROIBIDA -1

typedef struct{
    char cidade1[MAX_NOME_CIDADE], cidade2[MAX_NOME_CIDADE];
    int distancia;
}cidadesLigadas;

typedef struct{
    char cidade1[MAX_NOME_CIDADE], cidade2[MAX_NOME_CIDADE];
}cidadesPesquisa;

int tamanho_struct_cidades_ligadas, qtde_cidades_diferentes, qtde_comb_possiveis, tamanho_vetor_posicoes, distancia_final;

FILE * abre_arquivo(const char *nome_arquivo){
    FILE *f;
    f = fopen(nome_arquivo, "r");
    if(f == NULL){
        printf("Não foi possível abrir o arquivo '%s'\n", nome_arquivo);
        exit(0);
    }
    return f;
}

int **Aloca_matriz(int lin, int col){
    int **matriz;
    matriz = malloc(sizeof(int*)*lin);
    for (int i = 0; i < lin; ++i) {
        matriz[i] = malloc(sizeof(int)*col);
    }
    return matriz;
}

char **Aloca_matriz_char(int lin, int col){
    char **matriz;
    matriz = malloc(sizeof(char*)*lin);
    for (int i = 0; i < lin; ++i) {
        matriz[i] = malloc(sizeof(char)*col);
        matriz[i][0] = ',';//Se o nome da string começa com ',' quer dizer que não tem cidade ali
        matriz[i][1] = '\0';
    }
    return matriz;
}

void voltar_pro_inicio_ignorando_primeira_linha(FILE *f, char *primeira_linha){
    //Vai ir para a segunda linha do arquivo
    fseek(f, 0, SEEK_SET);//Voltar pro início do arquivo
    fscanf(f, "%s", primeira_linha);//pular primeira linha
}

int identifica_quantidade_de_ligacoes(FILE *f){
    char cidade1[MAX_NOME_CIDADE], cidade2[MAX_NOME_CIDADE], distancia[MAX_NOME_CIDADE], primeira_linha[MAX_NOME_CIDADE];
    int cont;
    cont = CONDICAO_PROIBIDA;
    voltar_pro_inicio_ignorando_primeira_linha(f, primeira_linha);
    while(fscanf(f, "%s %s %s", cidade1, cidade2, distancia) != EOF){
        cont++;
    }
    voltar_pro_inicio_ignorando_primeira_linha(f, primeira_linha);
    return cont;
}

void copiar_string(char *s1, const char *s2){//Copia o conteudo de s2 para s1
    int i;
    for (i = 0; s2[i] != '\0'; ++i) {
        s1[i] = s2[i];
    }
    s1[i] = '\0';
}

cidadesPesquisa* montar_struct_cidades_pesquisa(FILE *f, int qtde_ligacoes){
    //Identifica quais são as cidades de pesquisa presentes nas últimas duas linhas do arquivo;
    cidadesPesquisa *pesquisa;
    pesquisa = malloc(sizeof(cidadesPesquisa));
    char s1[MAX_NOME_CIDADE], s2[MAX_NOME_CIDADE], s3[MAX_NOME_CIDADE];
    while (fscanf(f, "%s %s %s", s1, s2, s3) != EOF){
        qtde_ligacoes--;
        if(qtde_ligacoes == CONDICAO_PROIBIDA){
            copiar_string(pesquisa->cidade1, s1);
            copiar_string(pesquisa->cidade2, s2);
            return pesquisa;
        }
    }
    return NULL;
}

int quantidade_de_caracteres(const char *string){//Função para encontrar a quantidade de caracteres em uma string qualquer
    int i = 0;
    while(string[i] != '\0'){
        i++;
    }
    return i;
}

int myPow(int n1, int n2){//Faz n1 elvado a n2
    int resultado = 1;
    while(n2 > 0){
        resultado *= n1;
        n2--;
    }
    return resultado;
}

int converte_string_pra_int(char *string){//Irá converter uma string passada como parâmetro para um valor inteiro
    int qtde_char = quantidade_de_caracteres(string);
    int numero, number = 0, cont = 0;
    for (int i = qtde_char - 1; i >= 0; --i) {
        numero = string[i] - 48;//Volta 48 caracteres na tabela asc pois '3' é diferente de 3 por exemplo
        number += numero*myPow(10, cont);//Como tava dando ruim em usar o pow da math eu criei meu próprio pow
        cont++;
    }
    return number;//retorna o número já convertido para string
}

cidadesLigadas* montar_struct_cidades_ligadas(FILE *f, int qtde_ligacoes){
    char s1[MAX_NOME_CIDADE], s2[MAX_NOME_CIDADE], s3[MAX_NOME_CIDADE], primeira_linha[MAX_NOME_CIDADE];
    int i = 0;
    cidadesLigadas *ligadas;
    ligadas = malloc(sizeof(cidadesLigadas)*qtde_ligacoes);
    voltar_pro_inicio_ignorando_primeira_linha(f, primeira_linha);
    while (fscanf(f, "%s %s %s", s1, s2, s3) != EOF){
        qtde_ligacoes--;
        if(qtde_ligacoes != CONDICAO_PROIBIDA){
            copiar_string(ligadas[i].cidade1, s1);
            copiar_string(ligadas[i].cidade2, s2);
            ligadas[i].distancia = converte_string_pra_int(s3);
        }
        else{
            return ligadas;
        }
        i++;
    }
    return NULL;
}

int somar_distancias_da_struct_cidades_ligadas(cidadesLigadas *ligadas){
    int soma = 0;
    for (int i = 0; i < tamanho_struct_cidades_ligadas; ++i) {
        soma += ligadas[i].distancia;
    }
    return soma;
}

void preencher_matriz_de_adjacencia(int **matriz, int soma){
    for (int i = 0; i < qtde_cidades_diferentes; ++i) {
        for (int j = 0; j < qtde_cidades_diferentes; ++j) {
            matriz[i][j] = soma;
        }
    }
}

int repreencher_matriz_caracteres(char **matriz_char, cidadesLigadas *ligadas){
    int i, j, k, qtde_consideravel;
    for (i = 0; i < tamanho_struct_cidades_ligadas; ++i) {
        copiar_string(matriz_char[i], ligadas[i].cidade1);
    }
    for (j = i, k = 0; j < 2*tamanho_struct_cidades_ligadas; ++j, ++k) {
        copiar_string(matriz_char[j], ligadas[k].cidade2);
    }
    qtde_consideravel = i + k;
    return qtde_consideravel;//quantidade de linhas a se considerar
}

void copiar_o_importante_de_2_para_1(char **m1, char **m2, int q){//Copia o conteudo de m2 para m1 até q;
    for (int i = 0; i < q; ++i) {
        copiar_string(m1[i], m2[i]);
    }
}

void desalocar_matriz(char **m, int t){
    for (int i = 0; i < t; ++i) {
        free(m[i]);
    }
    free(m);
}

int strings_iguais(char *s1, char *s2){//Verifica se duas strings são iguais
    if(quantidade_de_caracteres(s1) != quantidade_de_caracteres(s2)){
        return 0;
    }
    for (int i = 0; s1[i] != '\0' ; ++i) {
        if(s1[i] != s2[i]){
            return 0;
        }
    }
    return 1;
}

int jaTem(char *s1, char **s2, int t){//Verifica se uma string está em um vetor de strings
    for (int i = 0; i < t; ++i) {
        if(strings_iguais(s1, s2[i])){
            return 1;
        }
    }
    return 0;
}

int sem_repetidos(char **m1, char **m2, int t){//t é o tamanho das matrizes
    //Deixa todos os termos de m1 em m2 sem repetições
    int i, k;
    for (i = 0, k = 0; i < t; ++i) {
        if(!jaTem(m1[i], m2, t)){//Se a string que estou analisando não está no vetor de strings
            //Então adicione a string no vetor de strings
            copiar_string(m2[k], m1[i]);
            k++;
        }
    }
    return k;
}

char **identifica_quantidade_de_cidades_diferentes(cidadesLigadas *ligadas){
    char **matriz_caracteres, **matriz2, **matriz3, **matriz4;
    int qtde_linhas_consideraveis;
    matriz_caracteres = Aloca_matriz_char(qtde_comb_possiveis, MAX_NOME_CIDADE);
    qtde_linhas_consideraveis = repreencher_matriz_caracteres(matriz_caracteres, ligadas);
    matriz2 = Aloca_matriz_char(qtde_linhas_consideraveis, MAX_NOME_CIDADE);
    copiar_o_importante_de_2_para_1(matriz2, matriz_caracteres, qtde_linhas_consideraveis);
    desalocar_matriz(matriz_caracteres, qtde_linhas_consideraveis);
    matriz3 = Aloca_matriz_char(qtde_linhas_consideraveis, MAX_NOME_CIDADE);
    qtde_cidades_diferentes = sem_repetidos(matriz2, matriz3, qtde_linhas_consideraveis);
    matriz4 = Aloca_matriz_char(qtde_cidades_diferentes, MAX_NOME_CIDADE);
    copiar_o_importante_de_2_para_1(matriz4, matriz3, qtde_cidades_diferentes);
    desalocar_matriz(matriz3, qtde_linhas_consideraveis);
    return matriz4;
}

int fatorial(int x){//retorna o fatorial de um número
    int resultado = 1;
    for (int i = 2; i <= x; ++i) {
        resultado*=i;
    }
    return resultado;
}

int combinacao(int A, int B){//retorna a combinacao de A pra B
    return fatorial(A)/(fatorial(B)*fatorial(A - B));
}

void preencher_diagonal_principal_com_0(int **m){
    for (int i = 0; i < qtde_cidades_diferentes; ++i) {
        m[i][i] = 0;
    }
}

int tem_conexao(char *cidade1, char *cidade2, cidadesLigadas *ligadas){
    for (int i = 0; i < tamanho_struct_cidades_ligadas; ++i) {
        if(strings_iguais(cidade1, ligadas[i].cidade1) && strings_iguais(cidade2, ligadas[i].cidade2)){
            return 1;
        }
    }
    return 0;
}

int identifica_posicao_da_cidade1_na_linha(char *cidade1, char **cidades){
    for (int i = 0; i < tamanho_struct_cidades_ligadas; ++i) {
        if(strings_iguais(cidade1, cidades[i])){
            return i;
        }
    }
    return CONDICAO_PROIBIDA;
}

int identifica_posicao_da_cidade2_na_coluna(char *cidade2, char **cidades){
    for (int i = 0; i < tamanho_struct_cidades_ligadas; ++i) {
        if(strings_iguais(cidade2, cidades[i])){
            return i;
        }
    }
    return CONDICAO_PROIBIDA;
}

int identifica_na_struct_a_distancia_entre_as_cidades(cidadesLigadas *ligadas, char *cidade1, char *cidade2){
    for (int i = 0; i < tamanho_struct_cidades_ligadas; ++i) {
        if(strings_iguais(cidade1, ligadas[i].cidade1) && strings_iguais(cidade2, ligadas[i].cidade2)){
            return ligadas[i].distancia;
        }
    }
    return CONDICAO_PROIBIDA;
}

void preencher_matriz_de_adjacencia_com_os_valores_corretos_de_distancia(int **matriz_de_adjacencia, char **vetor_cidades, cidadesLigadas *ligadas){
    preencher_diagonal_principal_com_0(matriz_de_adjacencia);
    int pos_c1, pos_c2, distancia;
    for (int i = 0; i < qtde_cidades_diferentes; ++i) {
        for (int j = i+1; j < qtde_cidades_diferentes; ++j) {
            if(tem_conexao(vetor_cidades[i], vetor_cidades[j], ligadas)){
                pos_c1 = identifica_posicao_da_cidade1_na_linha(vetor_cidades[i], vetor_cidades);
                pos_c2 = identifica_posicao_da_cidade2_na_coluna(vetor_cidades[j], vetor_cidades);
                distancia = identifica_na_struct_a_distancia_entre_as_cidades(ligadas, vetor_cidades[i], vetor_cidades[j]);
                matriz_de_adjacencia[pos_c1][pos_c2] = distancia;
                matriz_de_adjacencia[pos_c2][pos_c1] = distancia;
            }
        }
    }
}

int* dijkstra(int **G,int n, int startnode, int endnode, int max, int soma){
    //Função adaptada do site: https://www.thecrazyprogrammer.com/2014/03/dijkstra-algorithm-for-finding-shortest-path-of-a-graph.html
    int **cost, *distance, *pred, *visited, count, mindistance, nextnode, i, j, cont, *vetor_posicoes_resposta, k;
    nextnode = cont = k = 0;
    cost = Aloca_matriz(max, max);
    distance = malloc(sizeof(int)*max);
    pred = malloc(sizeof(int)*max);
    visited = malloc(sizeof(int)*max);

    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(G[i][j]==0)
                cost[i][j] = soma;
            else
                cost[i][j]=G[i][j];

    for(i=0;i<n;i++){
        distance[i]=cost[startnode][i];
        pred[i]=startnode;
        visited[i]=0;
    }

    distance[startnode]=0;
    visited[startnode]=1;
    count=1;

    while(count<n-1){
        mindistance = soma;

        for(i=0;i<n;i++)
            if(distance[i]<mindistance&&!visited[i]){
                mindistance=distance[i];
                nextnode=i;
            }
        visited[nextnode]=1;
        for(i=0;i<n;i++)
            if(!visited[i])
                if(mindistance+cost[nextnode][i]<distance[i]){
                    distance[i]=mindistance+cost[nextnode][i];
                    pred[i]=nextnode;
                }
        count++;
    }
    for(i = 0; i < n; i++) {
        if (i == endnode) {
            cont++;
            distancia_final = distance[i];
            j = i;
            do {
                cont++;
                j = pred[j];
            } while (j != startnode);
        }
    }
    vetor_posicoes_resposta = malloc(sizeof(int)*cont);
    for(i = 0; i < n; i++) {
        if (i == endnode) {
            j = vetor_posicoes_resposta[k] = i;
            do {
                k++;
                j = pred[j];
                vetor_posicoes_resposta[k] = j;
            } while (j != startnode);
        }
    }
    tamanho_vetor_posicoes = cont;
    return vetor_posicoes_resposta;
}

void inverter_vetor(int *v, int t){//A função inverte um vetor de tamanho t;
    for (int aux, i = 0, j = t - 1; i < t/2; ++i, --j) {
        aux = v[i];
        v[i] = v[j];
        v[j] = aux;
    }
}

void menor_percurso(const int *vetor_posicoes, char **cidades){
    for (int i = 0; i < tamanho_vetor_posicoes; ++i) {
        if(i != tamanho_vetor_posicoes - 1){
            printf("%s ", cidades[vetor_posicoes[i]]);
        }
        else{
            printf("%s\n", cidades[vetor_posicoes[i]]);
        }
    }
}

int main(){
    char nome_arquivo[100];
    FILE *f;
    int qtde_ligacoes, **matriz_de_adjacencia, soma_distancias, p1, p2, *vetor_posicoes;
    cidadesLigadas *cidades_ligadas;
    cidadesPesquisa *pesquisa;
    char **cidades_diferentes;
    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s", nome_arquivo);
    f = abre_arquivo(nome_arquivo);
    tamanho_struct_cidades_ligadas = qtde_ligacoes = identifica_quantidade_de_ligacoes(f);
    pesquisa = montar_struct_cidades_pesquisa(f, qtde_ligacoes);
    cidades_ligadas = montar_struct_cidades_ligadas(f, qtde_ligacoes);
    soma_distancias = somar_distancias_da_struct_cidades_ligadas(cidades_ligadas);
    qtde_comb_possiveis = combinacao(tamanho_struct_cidades_ligadas, 2);
    cidades_diferentes = identifica_quantidade_de_cidades_diferentes(cidades_ligadas);
    matriz_de_adjacencia = Aloca_matriz(qtde_cidades_diferentes, qtde_cidades_diferentes);
    preencher_matriz_de_adjacencia(matriz_de_adjacencia, soma_distancias);
    preencher_matriz_de_adjacencia_com_os_valores_corretos_de_distancia(matriz_de_adjacencia, cidades_diferentes, cidades_ligadas);
    p1 = identifica_posicao_da_cidade1_na_linha(pesquisa->cidade1, cidades_diferentes);
    p2 = identifica_posicao_da_cidade2_na_coluna(pesquisa->cidade2, cidades_diferentes);
    vetor_posicoes = dijkstra(matriz_de_adjacencia, qtde_cidades_diferentes, p1, p2, qtde_cidades_diferentes, soma_distancias);
    inverter_vetor(vetor_posicoes, tamanho_vetor_posicoes);
    printf("Menor percurso: ");
    menor_percurso(vetor_posicoes, cidades_diferentes);
    printf("Distancia total: %d Km", distancia_final);
    return 0;
}
