#include <stdlib.h>
#include <stdio.h>
#define TAM 20
int tamanho_matriz, qtde_cidades_diferentes = 0;

typedef struct{
    char cidade1[TAM], cidade2[TAM];
    int distancia;
}LIGACAO;

typedef struct{
    char cidade1[TAM], cidade2[TAM];
}CIDADES_PESQUISA;

FILE *abre_arquivo(char *nome_arquivo){
    FILE *f;
    f = fopen(nome_arquivo, "r");
    if(f == NULL){
        printf("Deu ruim ae man kkkkjkkjjkj");
    }
    return f;
}

int myPow(int n1, int n2){//Faz n1 elvado a n2
    int resultado = 1;
    while(n2 > 0){
        resultado *= n1;
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

void copia_string(char *s1, const char *s2){//Copia o conteúdo de s2 pra s1
    int i;
    for (i = 0; s2[i] != '\0'; ++i) {
        s1[i] = s2[i];
    }
    s1[i] = '\0';
}

int ** Aloca_matriz(int lin, int col){//Retorna a matriz alocada
    int **matriz;
    matriz = calloc(lin, sizeof(int*));
    for (int i = 0; i < col; ++i) {
        matriz[i] = calloc(lin, sizeof(int));
    }
    return matriz;
}

char ** Aloca_matriz_char(int lin, int col){//Retorna a matriz alocada
    char **matriz;
    matriz = calloc(lin, sizeof(char*));
    for (int i = 0; i < col; ++i) {
        matriz[i] = calloc(col, sizeof(char));
    }
    //Colocando 0 em todas as posições da matriz
    for (int i = 0; i < lin; ++i) {
        for (int j = 0; j < col; ++j) {
            matriz[i][j] = '0';
        }
    }
    return matriz;
}

int retorna_tamanho_da_matriz(FILE *f){//Aqui irei retornar o tamanho da matriz
    int t;
    fscanf(f, "%d", &t);
    return t;
}

LIGACAO *aloca_struct(){
    return malloc(sizeof(LIGACAO)*tamanho_matriz);
}

char *pega_linha(FILE *f, int linha_interesse){ //Essa pega linha irá retornar o conteúdo (em formato de string) de uma linha passada como parâmetro do arquvio texto
    char *linha;
    int cont = 1;//Contado começa com 1
    linha = malloc(100*sizeof(char));
    while(fgets(linha, 100, f) != NULL){//Enquanto estiver lendo coisas do arquivo
        if(cont == linha_interesse){//Se o contador atingir o valor da linha de interesse
            if(linha_interesse != tamanho_matriz+2){
                linha[quantidade_de_caracteres(linha)-1] = '\0';//Pra tirar o \n
            }
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

char * encontra_cidade1(const char *string_line){ //Essa função irá converter a cidade 1 que está no arquivo em uma determinada linha para string
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
    return s;//Retorna o ponteiro já com a cidade
}

char * encontra_cidade2(const char *string_line) { //Semelhante à função anterior: aqui irei pegar o valor, ou seja o que está depois do ' '
    char *s;//Um ponteiro de char é declarado pois eu não sei quantos caracteres irei precisar alocar
    int cont = 0, pode_contar = 0, pode_copiar = 0, i, j, qtde_espacos = 0, qtde_espacos_pro_segundo_for = 0;
    for (i = 0; qtde_espacos != 2; ++i) {
        if(pode_contar){ //Se eu posso contar, então meu contador é incrementado, ou seja começo a contar quantos espaço irei precisar para alocar o meu ponteiro de caracteres
            cont++;
        }
        if(string_line[i] == ' '){ //Se eu cheguei no espaço que dizer que eu já posso inicializar a contagem para começar a alocação
            pode_contar = 1;
            qtde_espacos++;
        }
    }
    s = malloc(cont*sizeof(char));//Depois de todas essas verificações posso finalmente alocar o meu ponteiro
    for (j = i = 0; qtde_espacos_pro_segundo_for != 2; ++i) {//Inicializa 'j' e 'i' com 0, porém perceba que 'j' não cresce com 'i'
        if(string_line[i] == ' '){//Se eu estou no espaço, que dizer que já posso inicializar a cópia
            pode_copiar = 1;
            qtde_espacos_pro_segundo_for++;
        }
        if(pode_copiar && string_line[i] != ' '){
            s[j] = string_line[i];//Simplesmente vai copiando o que tá na string_line depois do ' ' para s
            j++;
        }
    }
    s[j] = '\0';//Tira os lixos de memória
    return s;//Retorna o ponteiro já com o valor do valor no formato de string
}

char * encontra_cidade2Especial(char *string_line){
    if(string_line[quantidade_de_caracteres(string_line)-1] == '\n'){
        string_line[quantidade_de_caracteres(string_line)-1] = '\0';
    }
    char *s;//Um ponteiro de char é declarado pois eu não sei quantos caracteres irei precisar alocar
    int cont = 0, i = 0, j = 0, k;
    while(1){
        if(string_line[i] == ' '){ //Se eu cheguei no espaço que dizer que eu já posso inicializar a contagem para começar a alocação
            i++;
            break;
        }
        i++;
    }
    k = i;
    for (; string_line[i] != '\0'; ++i) {
        cont++;
    }
    s = malloc(cont*sizeof(char));//Depois de todas essas verificações posso finalmente alocar o meu ponteiro
    for (; string_line[k] != '\0' ; ++k, ++j) {
        s[j] = string_line[k];
    }
    s[j] = '\0';//Tira os lixos de memória
    return s;//Retorna o ponteiro já com o valor do valor no formato de string
}

int encontra_distancia(const char *s){ //Aqui irei encontrar o valor da distancia e jogar pra inteiro;
    int ascii, cont = 0, distancia, i, j;
    char *s2;
    for (i = 0; s[i] != '\0'; ++i) {//Aqui irei percorrer a string toda para saber quantos chars tenho que alocar
        ascii = s[i];
        if(ascii >= 48 && ascii <= 57){//Se for um numero, incremento o contador
            cont++;
        }
    }
    s2 = malloc(sizeof(cont));
    for (i = j = 0; s[i] != '\0'; ++i) {//Aqui irei percorrer a string toda para saber quantos chars tenho que alocar
        ascii = s[i];
        if(ascii >= 48 && ascii <= 57){//Se for um numero, taco na string
            s2[j] = s[i];
            j++;
        }
    }
    s2[j] = '\0';
    distancia = converte_para_int(s2);
    return distancia;
}

void preenche_struct(LIGACAO *ligacoes, CIDADES_PESQUISA *cidadesPesquisa, FILE *f, char *nome_arquivo){ //Aqui irei preencher os dados da struct que já está previamente alocada
    char *string_line, *cidade1, *cidade2;
    int linha_interesse = 2;//Linha interesse é a linha que quero ler do arquivo naquele momento, começa em 3
    for (int i = 0; i < tamanho_matriz; ++i){
        f = abre_arquivo(nome_arquivo);
        string_line = pega_linha(f, linha_interesse);//Vou lendo linha a linha do arquivo a partir da linha 3
        cidade1 = encontra_cidade1(string_line);
        cidade2 = encontra_cidade2(string_line);
        copia_string(ligacoes[linha_interesse-2].cidade1, cidade1);
        copia_string(ligacoes[linha_interesse-2].cidade2, cidade2);
        ligacoes[linha_interesse-2].distancia = encontra_distancia(string_line);
        linha_interesse++;//A linha de interesse (a linha que quero ler do arquivo) é acrementada
    }//Os dados são então recebidos, convertidos e inseridos na minha estrutura de dados
    f = abre_arquivo(nome_arquivo);
    string_line = pega_linha(f, tamanho_matriz+2);
    cidade1 = encontra_cidade1(string_line);
    cidade2 = encontra_cidade2Especial(string_line);
    copia_string(cidadesPesquisa->cidade1, cidade1);
    copia_string(cidadesPesquisa->cidade2, cidade2);
}

int strings_iguais(char *s1, char *s2){
    if(quantidade_de_caracteres(s1) != quantidade_de_caracteres(s2)){
        return 0;
    }
    for (int i = 0; s1[i] != '\0'; ++i) {
        if(s1[i] != s2[i]){
            return 0;
        }
    }
    return 1;
}

int tem_a_cidade(char *cidade1, char cidades[TAM][TAM]){
    for (int i = 0; i < tamanho_matriz; ++i) {
        if(strings_iguais(cidade1, cidades[i])){
            return 1;
        }
    }
    return 0;
}

int encaixa_se_nao_repetiu(char cidades[TAM][TAM], char *cidade_a_ser_alocada, char *cidade){
    if(!tem_a_cidade(cidade, cidades)){
        copia_string(cidade_a_ser_alocada, cidade);
        return 1;
    }
    return 0;
}

void zera_geral(char vetor_cidades[TAM][TAM]){
    int i, j;
    for (i = 0; i < TAM; ++i) {
        for (j = 0; j < TAM; ++j) {
            vetor_cidades[i][j] = '0';
        }
    }
}

void copia_matrizes(char vetor_cidades[TAM][TAM], char **vetor_cidades2, int pos_final){
    for (int i = 0; i <= pos_final ; ++i) {
        for (int j = 0; j < TAM; ++j) {
            vetor_cidades2[i][j] = vetor_cidades[i][j];
        }
    }
}

char **diferentes_cidades_na_struct(LIGACAO *ligacoes){
    char vetor_cidades[TAM][TAM], **vetor_cidades2;
    int i, j;
    zera_geral(vetor_cidades);
    for (i = j = 0; i < tamanho_matriz; ++i) {
        if(encaixa_se_nao_repetiu(vetor_cidades, vetor_cidades[j], ligacoes[i].cidade1)){
            j++;
        }
    }
    for (i = 0; i < tamanho_matriz; ++i) {
        if(i >= j){
            if(encaixa_se_nao_repetiu(vetor_cidades, vetor_cidades[j], ligacoes[i].cidade2)){
                j++;
            }
        }
    }
    qtde_cidades_diferentes = j;
    vetor_cidades2 = Aloca_matriz_char(j, TAM);
    copia_matrizes(vetor_cidades, vetor_cidades2, j-1);
    return vetor_cidades2;
}

int encontra_distancia_entre_cidades(char *cidade1, char *cidade2, LIGACAO *ligacoes){
    for (int i = 0; i < tamanho_matriz; ++i) {
        if((strings_iguais(ligacoes[i].cidade1, cidade1) || strings_iguais(ligacoes[i].cidade1, cidade2)) && ((strings_iguais(ligacoes[i].cidade2, cidade1) || strings_iguais(ligacoes[i].cidade2, cidade2)))){
            return ligacoes[i].distancia;
        }
    }
    return 0;
}

void preenche_linha_da_matriz_de_adjacencia_ate_a_diagonal_principal(int *linha_da_matriz_de_adjacencia, char *linha_do_vetor_cidades, int pos_passada_como_parametro, char **vetor_cidades, LIGACAO *ligacoes){
    int i, j;
    for (i = j = 0; i < qtde_cidades_diferentes; ++i, ++j) {
        if(pos_passada_como_parametro == i){
            linha_da_matriz_de_adjacencia[i] = 0;
            break;
        }
        else{
            linha_da_matriz_de_adjacencia[i] = encontra_distancia_entre_cidades(linha_do_vetor_cidades, vetor_cidades[j], ligacoes);
        }
    }
}

void espelhar_matriz_adjacencia_pra_cima(int **matriz_de_adjacencia){
    for (int i = 0; i < qtde_cidades_diferentes; ++i) {
        for (int j = i+1; j < qtde_cidades_diferentes; ++j) {
            matriz_de_adjacencia[i][j] = matriz_de_adjacencia[j][i];
        }
    }
}

void preenche_matriz_de_adjacencia(int **matriz_de_adjacencia, char **vetor_cidades, LIGACAO *ligacoes){
    for (int i = 0; i < qtde_cidades_diferentes; ++i) {//Percorrendo a coluna
        preenche_linha_da_matriz_de_adjacencia_ate_a_diagonal_principal(matriz_de_adjacencia[i], vetor_cidades[i], i, vetor_cidades, ligacoes);
    }
    espelhar_matriz_adjacencia_pra_cima(matriz_de_adjacencia);
}

void dijkstra(int **matriz, int p){
    int *visitados, n = qtde_cidades_diferentes;
    visitados = calloc(qtde_cidades_diferentes, sizeof(int));
    // O valor 'i' do for abaixo não é utilizado, pois o for serve apenas para percorrer o número de colunas da matriz
    for(int i = 1; i < n; i++){ // Começa em 1 pois não precisa comparar o vértice com ele mesmo

        int min = -1; // Variável que guarda a posição do menor valor, inicia em -1 pois é uma posição inválida
        unsigned long int MinValor = 4294967295; // Variável que guarda o menor valor encontrado, inicia com 'infinito', assim, sempre na primeira passada o valor será menor que esta variável

        // For que percorre todas as linhas na coluna [0]
        for(int j = 1; j < n; j++){
            // Se o vertice ainda não foi visitado e o valor for menor que o 'MinValor'
            if( !visitados[j] && matriz[j][p] < MinValor ){
                min = j; // Guarda a posição do menor
                MinValor = matriz[j][p]; // Guarda o menor valor
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
}

int acha_pos(char *s1, char **s2){//Encontra onde s1 tá em s2;
    for (int i = 0; i < qtde_cidades_diferentes; ++i) {
        if(strings_iguais(s1, s2[i])){
            return i;
        }
    }
    return -1;//Quer dizer que não tem
}

//void printar(int **v){
//    for (int i = 0; i < qtde_cidades_diferentes; ++i) {
//        for (int j = 0; j < qtde_cidades_diferentes; ++j) {
//            printf("[%d] ", v[i][j]);
//        }
//        printf("\n");
//    }
//}

void menor_percurso(int menor_distancia, char **vetor_cidades, int **matriz_de_adjacencia, int p_origem, int p_destino){
    int aux, soma, p_origem2, i, j;
    if(p_origem > p_destino){
        aux = p_origem;
        p_origem = p_destino;
        p_destino = aux;
    }
    p_origem2 = p_origem+1;
    soma = matriz_de_adjacencia[0][p_origem2];
    printf("%s ", vetor_cidades[p_origem]);
    for (i = 0, j = 1; soma < menor_distancia; i++, j++) {
        if(j >= qtde_cidades_diferentes){
            break;
        }
        else if(soma + matriz_de_adjacencia[i][j]){
            soma += matriz_de_adjacencia[i][j];
            printf("%s ", vetor_cidades[j]);
        }
    }
    printf("%s\n", vetor_cidades[p_destino]);
}

int main() {
    FILE *f;
    int **matriz_de_adjacencia, pos1, pos2, menor_distancia;
    char **vetor_cidades, nome_arquivo[100];
    LIGACAO *ligacoes;
    CIDADES_PESQUISA *cidadesPesquisa;
    printf("Digite o nome do arquivo de entrada: ");
    scanf(" %[^\n]s", nome_arquivo);
    f = abre_arquivo(nome_arquivo);
    cidadesPesquisa = malloc(sizeof(cidadesPesquisa));
    tamanho_matriz = retorna_tamanho_da_matriz(f);
    ligacoes = aloca_struct();
    preenche_struct(ligacoes, cidadesPesquisa, f, nome_arquivo);
    vetor_cidades = diferentes_cidades_na_struct(ligacoes);
    matriz_de_adjacencia = Aloca_matriz(qtde_cidades_diferentes, qtde_cidades_diferentes);
    preenche_matriz_de_adjacencia(matriz_de_adjacencia, vetor_cidades, ligacoes);
    pos1 = acha_pos(cidadesPesquisa->cidade1, vetor_cidades);
    pos2 = acha_pos(cidadesPesquisa->cidade2, vetor_cidades);
    //printar(matriz_de_adjacencia);
    //printf("======= LA VEM O DAISKRA =======\n");
    dijkstra(matriz_de_adjacencia, pos1);
    menor_distancia = matriz_de_adjacencia[pos2][pos1];
    //printar(matriz_de_adjacencia);
    //Menor percurso: A B C D;
    printf("Menor percurso: ");
    menor_percurso(menor_distancia, vetor_cidades, matriz_de_adjacencia, pos1, pos2);
    printf("Distancia total: %d Km\n", menor_distancia);
    //printf("%s", f->_IO_read_base);
    return 0;
}
