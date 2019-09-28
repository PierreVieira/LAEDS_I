#include <stdio.h>
#include <stdlib.h>
//PROXIMO PASSO: CRIAR VETOR CIDADE LINHA E VETOR CIDADE COLUNA e depois ordená-los por ordem alfabética
int tamanho_matriz;
typedef struct{
    char cidade1[20], cidade2[20];
    int distancia;
}LIGACAO;

typedef struct{
    char cidade1[20], cidade2[20];
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

void copia_string(char *s1, const char *s2){//Copia o conteúdo de s2 pra s1
    int i;
    for (i = 0; s2[i] != '\0'; ++i) {
        s1[i] = s2[i];
    }
    s1[i] = '\0';
}

int ** Aloca_matriz(int lin, int col){//Retorna a matriz alocada
    int **matriz;
    matriz = calloc(sizeof(int*), lin);
    for (int i = 0; i < col; ++i) {
        matriz[i] = calloc(lin, sizeof(int));
    }
    return matriz;
}

int retorna_tamanho_da_matriz(FILE *f){//Aqui irei retornar o tamanho da matriz
    int t;
    fscanf(f, "%d", &t);
    return t;
}

void printa_matriz_quadrada(int **matriz){//Essa função printa a matriz formatada
    for (int i = 0; i < tamanho_matriz; ++i) {
        for (int j = 0; j <tamanho_matriz ; ++j) {
            printf("[%d] ", matriz[i][j]);
        }
        printf("\n");
    }
}

LIGACAO *aloca_struct(LIGACAO *ligacoes){
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
    for (i = 0; qtde_espacos != 2 ; ++i) {
        if(pode_contar){ //Se eu posso contar, então meu contador é incrementado, ou seja começo a contar quantos espaço irei precisar para alocar o meu ponteiro de caracteres
            cont++;
        }
        if(string_line[i] == ' '){ //Se eu cheguei no espaço que dizer qeu eu já posso inicializar a contagem para começar a alocação
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

int encontra_distancia(char *s){ //Aqui irei encontrar o valor da distancia e jogar pra inteiro;
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
    char *string_line, *cidade1, *cidade2, *string_distancia;
    int numero_distancia;
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
    cidade2 = encontra_cidade2(string_line);
    copia_string(cidadesPesquisa->cidade1, cidade1);
    copia_string(cidadesPesquisa->cidade2, cidade2);
}

void printa_estutura(LIGACAO *l){
    for (int i = 0; i < tamanho_matriz; ++i) {
        printf("========== POSICAO ANALISADA %d ==========\n", i);
        printf("CIDADE 1 = %s\nCIDADE 2 = %s\nDistancia = %d\n", l[i].cidade1, l[i].cidade2, l[i].distancia);
    }
}


int main() {
    FILE *f;
    f = abre_arquivo("m.txt");
    int **matriz_distancias;
    LIGACAO *ligacoes;
    CIDADES_PESQUISA *cidadesPesquisa;
    cidadesPesquisa = malloc(sizeof(cidadesPesquisa));
    //    char nome_arquivo[100];
//    printf("Digite o nome do arquivo de entrada: ");
//    scanf(" %[^\n]s", nome_arquivo);
    tamanho_matriz = retorna_tamanho_da_matriz(f);
    matriz_distancias = Aloca_matriz(tamanho_matriz, tamanho_matriz);
    //printa_matriz_quadrada(matriz_distancias);
    ligacoes = aloca_struct(ligacoes);
    preenche_struct(ligacoes, cidadesPesquisa, f, "m.txt");
    printa_estutura(ligacoes);
    printf("\nCIDADES DE PESQUISA\n%s || %s", cidadesPesquisa->cidade1, cidadesPesquisa->cidade2);
    return 0;
}
