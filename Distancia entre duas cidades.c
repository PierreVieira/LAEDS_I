#include <stdio.h>
#include <stdlib.h>
#define MAX_NOME_CIDADE 20
#define TAM_VET_POSICOES 30
#define CONDICAO_PROIBIDA -1

typedef struct{
    char cidade1[MAX_NOME_CIDADE], cidade2[MAX_NOME_CIDADE];
    int distancia;
}cidadesLigadas;

typedef struct{
    char cidade1[MAX_NOME_CIDADE], cidade2[MAX_NOME_CIDADE];
}cidadesPesquisa;

int tamanho_struct_cidades_ligadas, qtde_cidades_diferentes, qtde_comb_possiveis;

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

void printar_struct_cidades_pesquisa(cidadesPesquisa *pesquisa){
    printf("========= PESQUISA =========\n");
    printf("Cidade 1: %s\nCidade 2: %s\n", pesquisa->cidade1, pesquisa->cidade2);
    printf("============================\n");
}

void printar_struct_cidades_ligadas(cidadesLigadas *ligadas){
    printf("========= CIDADES LIGADAS =========\n");
    for (int i = 0; i < tamanho_struct_cidades_ligadas; ++i) {
        printf("Cidade 1: %s\nCidade2: %s\nDistancia: %d\n", ligadas[i].cidade1, ligadas[i].cidade2, ligadas[i].distancia);
        printf("-----------------------------------\n");
    }
    printf("===================================\n");
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

void printar_matriz_de_adjacencia(int **matriz){
    printf("======== MATRIZ ========\n");
    for (int i = 0; i < qtde_cidades_diferentes; ++i) {
        for (int j = 0; j < qtde_cidades_diferentes; ++j) {
            printf("[%2d]", matriz[i][j]);
        }
        printf("\n");
    }
    printf("========================\n");
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

void printar_matriz_de_caracteres(char **matriz, int t){
    for (int i = 0; i < t; ++i) {
        printf("%s\n", matriz[i]);
    }
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

int em_maiusuculo(char c){
    if(c >= 97 && c <= 122){
        c -= 32;
    }
    return c;
}

int o_caractere_esta_em_conformidade(char c1, char c2){//verifica se o caractere 1 etá em conformidade alfabética com o caractere2
    if(c1 > c2){
        return 0;
    }
    return 1;
}

int verifica_ordem(char *s1, char *s2){
    //Sendo a quantidade de caracteres de s1 maior que a quantidade de caracteres de s2, verifica-se se s1 está em conformidade
    //de ordem alfabética em relação à s2
    int q1, q2, q;
    q1 = quantidade_de_caracteres(s1);
    q2 = quantidade_de_caracteres(s2);
    if(q1 < q2){
        q = q1;
    }
    else{
        q = q2;
    }
    for (int i = 0; i < q ; ++i) {
        if(em_maiusuculo(s1[i]) != em_maiusuculo(s2[i])){
            if(!o_caractere_esta_em_conformidade(s1[i], s2[i])){
                return 0;//Quer dizer que não está em conformidade com a ordem alfabética
            }
            else{
                return 1;
            }
        }
    }
    return 1;//Quer dizer que está em conformidade com a ordem alfabética
}

int esta_em_ordem_alfabetica(char *s1, char *s2){//Verifica se s1 está em ordem alfabética se comparado à s2
    int retorno = -2;
    retorno = verifica_ordem(s1, s2);
    return retorno;
}

void ordenar_por_ordem_alfabetica(char **vetor_de_strings){
    char aux[20]; //vetor auxiliar para fazer a troca
    for (int i = 0; i < qtde_cidades_diferentes; ++i) {
        for (int j = i+1; j < qtde_cidades_diferentes; ++j) {
            if((!esta_em_ordem_alfabetica(vetor_de_strings[i], vetor_de_strings[j]))){
                copiar_string(aux, vetor_de_strings[i]);
                copiar_string(vetor_de_strings[i], vetor_de_strings[j]);
                copiar_string(vetor_de_strings[j], aux);
            }
        }
    }
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

int *inicializa_vet_posicoes(int p_origem){
    int *v;
    v = malloc(sizeof(int)*TAM_VET_POSICOES);
    v[0] = p_origem; //marca como visitado
    for (int i = 1; i < TAM_VET_POSICOES; ++i) {
        v[i] = CONDICAO_PROIBIDA; //quer dizer que essa posição ainda não foi visitada
    }
    return v;
}

int *dijkstra(int **matriz, int p, char **cidades_diferentes){
    int *visitados, n = qtde_cidades_diferentes, *vetor_posicoes, k = 1;
    visitados = calloc(qtde_cidades_diferentes, sizeof(int));
    vetor_posicoes = inicializa_vet_posicoes(p);
    // O valor 'i' do for abaixo não é utilizado, pois o for serve apenas para percorrer o número de colunas da matriz
    for(int i = 1; i < n; i++){ // Começa em 1 pois não precisa comparar o vértice com ele mesmo
        int min = CONDICAO_PROIBIDA; // Variável que guarda a posição do menor valor, inicia em CONDICAO_PROIBIDA pois é uma posição inválida
        unsigned long int MinValor = 4294967295; // Variável que guarda o menor valor encontrado, inicia com 'infinito', assim, sempre na primeira passada o valor será menor que esta variável
        // For que percorre todas as linhas na coluna [0]
        for(int j = 1; j < n; j++){
            // Se o vertice ainda não foi visitado e o valor for menor que o 'MinValor'
            if( !visitados[j] && matriz[j][p] < MinValor ){
                min = j; // Guarda a posição do menor
                MinValor = matriz[j][p]; // Guarda o menor valor
                vetor_posicoes[k] = j;
                k++;
            }
        }
        visitados[min] = 1; // Marca o valor a posição do minimo como visitado
        // For de 1 até n
        for(int j = 1; j < n; j++){
            // Se o valor da coluna [0] + o valor da coluna que está passando for menor que o valor da linha que está passando e coluna [0]
            // Atualiza a primeira coluna da matriz, que será utilizado para as próximas iterações
            if( (matriz[min][p] + matriz[min][j]) < matriz[j][p] ){
                matriz[j][p] = matriz[min][p] + matriz[min][j];
            }
        }
    }
    return vetor_posicoes;
}

void printar_menor_caminho(char **vetor_cidades, const int *vet_posicoes){
    for (int i = 0; vet_posicoes[i] != CONDICAO_PROIBIDA; ++i) {
        if(vet_posicoes[i+1] != CONDICAO_PROIBIDA){
            printf("%s ", vetor_cidades[vet_posicoes[i]]);
        }
        else{
            printf("%s\n", vetor_cidades[vet_posicoes[i]]);
            break;
        }
    }
}

//void menor_caminho(int menor_distancia, char **vetor_cidades, int **matriz_de_adjacencia, int p_origem, int p_destino){
//    int soma, aux, i, j, k, termo, origem_coluna = 1;
//    int *vet_posicoes;
//    vet_posicoes = inicializa_vet_posicoes(p_origem);
//    soma = 0;
//    k = 1;
//    i = p_origem;
//    j = origem_coluna;
//    while(1){
//        if(i == j){
//            j++;
//        }
//        termo = matriz_de_adjacencia[i][j];
//        if((soma + termo < menor_distancia)){
//            soma += termo;
//            vet_posicoes[k] = j;
//            k++;
//            //i troca com j e anda 1 com j
//            aux = i;
//            i = j;
//            j = aux;
//            j++;
//        }
//        else if((soma + matriz_de_adjacencia[i][j] == menor_distancia) && strings_iguais(vetor_cidades[j], vetor_cidades[p_destino])){
//            vet_posicoes[k] = j;
//            break;
//        }
//        else{
//            soma = 0;
//            vet_posicoes = inicializa_vet_posicoes(p_origem);
//            k = 1;
//            //volta para a oposição de origem e tenta a próxima ligação
//            i = p_origem;
//            origem_coluna++;
//            j = origem_coluna;
//        }
//    }
//    printar_menor_caminho(vetor_cidades, vet_posicoes);
//}

int encontra_tamanho_fake(int *v){
    int i = 0;
    while(v[i] != -1){
        i++;
    }
    return i;
}

void preenche_matriz_possibilidades(int **matriz_tentativa_e_erro, int linhas, int colunas){
    //Deve-se fixar a coluna e percorrer as linhas
    printf("Quantidade de linhas: %d\nQuantidade de colunas: %d\n", linhas, colunas);
    int numero, alternancia, cont;
    alternancia = 1;
    for (int j = colunas-1; j >= 0; --j) {
        numero = cont = 0;
        for (int i = 0; i < linhas; ++i) {
            if(cont == alternancia){
                numero = !numero;
                cont = 0;
            }
            matriz_tentativa_e_erro[i][j] = numero;
            cont++;
        }
        alternancia*=2;
    }
}

int* testar_matriz_tentativa_e_erro(int **matriz, int linha, int coluna, int *caminho_fake){
    //PAREI AQUI
}

int* criar_menor_caminho_true(int *caminho_fake, char **vetor_cidades){
    int tamano_fake, numero_possibilidades_tabela_verdade, **matriz_tentativa_e_erro, *vetor_solucao;
    tamano_fake = encontra_tamanho_fake(caminho_fake);
    numero_possibilidades_tabela_verdade = myPow(2, tamano_fake);
    matriz_tentativa_e_erro = Aloca_matriz(numero_possibilidades_tabela_verdade, tamano_fake);
    preenche_matriz_possibilidades(matriz_tentativa_e_erro, numero_possibilidades_tabela_verdade, tamano_fake);
    vetor_solucao = testar_matriz_tentativa_e_erro(matriz_tentativa_e_erro, numero_possibilidades_tabela_verdade, tamano_fake, caminho_fake);
}

void ordenar_por_ordem_alfabetica_cidades_pesquisa(cidadesPesquisa *pesquisa){
    if((!esta_em_ordem_alfabetica(pesquisa->cidade1, pesquisa->cidade2))){
        char aux[20];
        copiar_string(aux, pesquisa->cidade1);
        copiar_string(pesquisa->cidade1,  pesquisa->cidade2);
        copiar_string(pesquisa->cidade2, aux);
    }
}

int main(){
    char nome_arquivo[100] = {'m', '.', 't', 'x', 't'};
    //char nome_arquivo[100];
    FILE *f;
    int qtde_ligacoes, **matriz_de_adjacencia, soma_distancias, dist, p1, p2, *caminho_fake, *caminho_true;
    cidadesLigadas *cidades_ligadas;
    cidadesPesquisa *pesquisa;
    char **cidades_diferentes;
    //printf("Digite o nome do arquivo de entrada: ");
    //scanf("%s", nome_arquivo);
    f = abre_arquivo(nome_arquivo);
    tamanho_struct_cidades_ligadas = qtde_ligacoes = identifica_quantidade_de_ligacoes(f);
    //printf("Quantidade de ligacoes: %d\n", qtde_ligacoes);
    pesquisa = montar_struct_cidades_pesquisa(f, qtde_ligacoes);
   // printar_struct_cidades_pesquisa(pesquisa);
    cidades_ligadas = montar_struct_cidades_ligadas(f, qtde_ligacoes);
   // printar_struct_cidades_ligadas(cidades_ligadas);
    soma_distancias = somar_distancias_da_struct_cidades_ligadas(cidades_ligadas);
    //printf("Soma das distancias = %d\n", soma_distancias);
    qtde_comb_possiveis = combinacao(tamanho_struct_cidades_ligadas, 2);
    cidades_diferentes = identifica_quantidade_de_cidades_diferentes(cidades_ligadas);
    //printar_matriz_de_caracteres(cidades_diferentes, qtde_cidades_diferentes);
    matriz_de_adjacencia = Aloca_matriz(qtde_cidades_diferentes, qtde_cidades_diferentes);
    preencher_matriz_de_adjacencia(matriz_de_adjacencia, soma_distancias);
    //printar_matriz_de_adjacencia(matriz_de_adjacencia);
    ordenar_por_ordem_alfabetica(cidades_diferentes);
    ordenar_por_ordem_alfabetica_cidades_pesquisa(pesquisa);
    //printar_matriz_de_caracteres(cidades_diferentes, qtde_cidades_diferentes);
    preencher_matriz_de_adjacencia_com_os_valores_corretos_de_distancia(matriz_de_adjacencia, cidades_diferentes, cidades_ligadas);
    //printar_matriz_de_adjacencia(matriz_de_adjacencia);
    caminho_fake = dijkstra(matriz_de_adjacencia, identifica_posicao_da_cidade1_na_linha(pesquisa->cidade1, cidades_diferentes), cidades_diferentes);
    //printar_matriz_de_adjacencia(matriz_de_adjacencia);
    p1 = identifica_posicao_da_cidade1_na_linha(pesquisa->cidade1, cidades_diferentes);
    p2 = identifica_posicao_da_cidade2_na_coluna(pesquisa->cidade2, cidades_diferentes);
    dist = matriz_de_adjacencia[p2][p1];
    printf("Menor percurso: ");
    printar_menor_caminho(cidades_diferentes, caminho_fake);
    caminho_true = criar_menor_caminho_true(caminho_fake, cidades_diferentes);
    //menor_caminho(dist, cidades_diferentes, matriz_de_adjacencia, p1, p2);
    printf("Distancia total: %d Km", dist);
    return 0;
}
