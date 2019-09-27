#include <stdio.h>
#include <stdlib.h>
typedef struct{
    char cidade1[20], cidade2[20];
    int distancia;
}LIGACAO;

FILE *abre_arquivo(){
    FILE *f;
    char nome_arquivo[100];
    printf("Digite o nome do arquivo de entrada: ");
    scanf(" %[^\n]s", nome_arquivo);
    f = fopen(nome_arquivo, "r");
    if(f == NULL){
        printf("Deu ruim ae man kkkkjkkjjkj");
    }
    return f;
}

int ** Aloca_matriz(int lin, int col){
    int **matriz;
    matriz = calloc(sizeof(int*), lin);
    for (int i = 0; i < col; ++i) {
        matriz[i] = calloc(lin, sizeof(int));
    }
    return matriz;
}

int retorna_tamanho_da_matriz(FILE *f){
    int t;
    fscanf(f, "%d", &t);
    return t;
}

void printa_matriz_quadrada(int **matriz, int tamanho_matriz){
    for (int i = 0; i < tamanho_matriz; ++i) {
        for (int j = 0; j <tamanho_matriz ; ++j) {
            printf("[%d] ", matriz[i][j]);
        }
        printf("\n");
    }
}

LIGACAO *aloca_struct(LIGACAO *ligacoes, int t){
    return malloc(sizeof(LIGACAO)*t);
}

void copia_string(char *s1, char *s2){
    int i;
    for (i = 0; s2[i] != '\0'; ++i) {
        s1[i] = s2[i];
    }
    s1[i] = '\0';
}

void preenche_posicao_struct(FILE *f, LIGACAO *ligacoes, int linha_do_arquivo){
    char cidade1[20], cidade2[20], distancia;
    fseek(f, SEEK_SET, linha_do_arquivo-1);
    fscanf(f,"%s %s %d", cidade1, cidade2, &distancia);
    copia_string(ligacoes[linha_do_arquivo-2].cidade1, cidade1);
    copia_string(ligacoes[linha_do_arquivo-2].cidade2, cidade2);
    ligacoes[linha_do_arquivo-2].distancia = distancia;
}

void taca_os_trem_do_arquivo_na_struct(FILE *f, LIGACAO *l, int t){
    for (int linha_do_arquivo = 2; linha_do_arquivo <= t+1; ++linha_do_arquivo) {
       preenche_posicao_struct(f, l, linha_do_arquivo);
    }
}

void printa_estutura(LIGACAO *l, int t){
    for (int i = 0; i < t; ++i) {
        printf("CIDADE 1 = %s\nCIDADE2 = %s\nDistancia = %d\n", l[i].cidade1, l[i].cidade2, l[i].distancia);
    }
}

int main() {
    FILE *f;
    f = abre_arquivo();
    int **matriz_distancias, tamanho_matriz;
    LIGACAO *ligacoes;
    tamanho_matriz = retorna_tamanho_da_matriz(f);
    printf("Tamanho da matriz = %d\n", tamanho_matriz);
    matriz_distancias = Aloca_matriz(tamanho_matriz ,tamanho_matriz);
    printa_matriz_quadrada(matriz_distancias, tamanho_matriz);
    ligacoes = aloca_struct(ligacoes, tamanho_matriz);
    taca_os_trem_do_arquivo_na_struct(f, ligacoes, tamanho_matriz);
    printa_estutura(ligacoes, tamanho_matriz);
    return 0;
}
