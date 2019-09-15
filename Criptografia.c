#include <stdio.h>
#include <stdlib.h>
#define max_caracteres_no_arquivo 10000
#define max_caracteres_nome_do_arquivo 100

int qte_char(const char s[]) {
    int i = 0;
    while(s[i] != '\0'){
        i++;
    }
    return i;
}

char *step2(char * s){
    char aux[2];
    int qtde_s = qte_char(s);
    for (int i = 0; i < qtde_s/2; i+=4) {
        aux[0] = s[i];
        aux[1] = s[i+1];
        s[i] = s[qtde_s - i - 2];
        s[i+1] = s[qtde_s - i - 1];
        s[qtde_s - i - 2] = aux[0];
        s[qtde_s - i - 1] = aux[1];
    }
    return s;
}

char *step3(char *s){
    char aux;
    int qtde_s = qte_char(s);
    for (int i = 0; i < qtde_s-2; i+=2) {
        aux = s[i];
        s[i] = s[i+1];
        s[i+1] = aux;
    }
    aux = s[qtde_s-2];
    s[qtde_s-2] = s[qtde_s-1];
    s[qtde_s-1] = aux;
    return s;
}

char *step4(char *s){
    char *s2;
    int q = qte_char(s), asc, i;
    s2 = malloc(q*sizeof(int));
    for (i = 0; i < q; ++i) {
        asc = s[i];
        if(asc >= 65 && asc <= 90){
            if(asc <= 67){
                asc = 90 - (67 - asc);
            }
            else{
                asc -= 3;
            }
        }
        else if(asc >= 97 && asc <= 122){
            if(asc <= 99){
                asc = 122 - (99 - asc);
            }
            else{
                asc -= 3;
            }
        }
        s2[i] = asc;
    }
    s2[i] = '\0';
    return s2;
}
char *step5(char *s){
    int qtde_s;
    char *s2;
    qtde_s = qte_char(s);
    s2 = malloc(sizeof(char)*qtde_s);
    for (int i = 0; s[i] != '\0' ; ++i) {
        if(s[i] != '#'){
            s2[i] = s[i];
        }
        else{
            s[i] = ' ';
        }
    }
    return s;
}

void solve_this_problem(char *s){
    char *string_resposta;
    string_resposta = step2(s);
    string_resposta = step3(string_resposta);
    string_resposta = step4(string_resposta);
    string_resposta = step5(string_resposta);
    printf("%s", string_resposta);
}

char *le_do_arquivo(char *nome_arquivo){
    FILE *f;
    char *string_oq_tem_no_arquivo;
    string_oq_tem_no_arquivo = malloc(sizeof(char)*max_caracteres_no_arquivo);
    f = fopen(nome_arquivo, "r");
    fscanf(f, "%s", string_oq_tem_no_arquivo);
    fclose(f);
    return string_oq_tem_no_arquivo;
}

int main(){
    char *string_nome_arquivo, *veio_do_arquivo;
    string_nome_arquivo = malloc(sizeof(char)*max_caracteres_nome_do_arquivo);
    printf("Digite o nome do arquivo: ");
    scanf("%s", string_nome_arquivo);
    printf("\n--------------------\nMensagem codificada:\n--------------------\n");
    veio_do_arquivo = le_do_arquivo(string_nome_arquivo);
    printf("%s\n\n", veio_do_arquivo);
    printf("----------------------\nMensagem decodificada:\n----------------------\n");
    solve_this_problem(veio_do_arquivo);
    return 0;
}
