/*
 * Nome: Antônio Pierre Martins Vieira
 * Data: 03/11/2019
 * JetBrains --> Clion IDE
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXTAM 70
#define TAM_VET_PILHA1 26
#define TAM_VET_PILHA2 11

typedef int TipoApontador;
typedef char TipoChave[100];

typedef struct {
    TipoChave Nome;
    int Nota;
} Aluno;

typedef struct {
    Aluno* alunos;
    int qtde_alunos;
    TipoApontador Topo;
}PilhaAlunos;

void FPVazia(PilhaAlunos *Pilha){
    Pilha->Topo = 0;
}

void Empilha(Aluno x, PilhaAlunos *Pilha){
    if (Pilha->Topo == MAXTAM){
        printf(" Erro   pilha est  a  cheia\n");
    }
    else {
        Pilha->Topo++;
        Pilha->alunos[Pilha->Topo - 1].Nota = x.Nota;
        strcpy(Pilha->alunos[Pilha->Topo - 1].Nome, x.Nome);
    }
}

void imprimirPilha(PilhaAlunos pilhaAlunos){
    for (int i = 0; i < pilhaAlunos.qtde_alunos; ++i) {
        printf("%s\n%d\n", pilhaAlunos.alunos[i].Nome, pilhaAlunos.alunos[i].Nota);
    }
}

int le_do_arquivo(Aluno *alunos2, const char *nome_arquivo){
    FILE *arq;
    int result;
    arq = fopen(nome_arquivo, "rb");
    if (arq == NULL){// Se houve erro na abertura
        printf("Problemas na abertura do arquivo\n");
        exit(0);
    }
    result = fread (alunos2, sizeof(Aluno), MAXTAM, arq);
    fclose(arq);
    printf("\n");
    return result;
}

void prepara_pilhas1(PilhaAlunos *pilhas, const int *v_qtde){
    for (int i = 0; i < TAM_VET_PILHA1; ++i) {
        FPVazia(&pilhas[i]);
        pilhas[i].alunos = malloc(sizeof(Aluno)*v_qtde[i]);
        pilhas[i].qtde_alunos = v_qtde[i];
        pilhas[i].Topo = 0;
    }
}

void prepara_pilhas2(PilhaAlunos *pilhas, const int *vet_notas){
    for (int i = 0; i < TAM_VET_PILHA2; ++i) {
        pilhas[i].alunos = malloc(sizeof(Aluno)*vet_notas[i]);
        pilhas[i].qtde_alunos = vet_notas[i];
        pilhas[i].Topo = 0;
    }
}

int converte_ascII_em_posicao_vetorial(char caractere){
    int posicao = -1;
    if(caractere >= 65 && caractere <= 90){
        posicao = caractere - 65;
    }
    else if(caractere >= 97 && caractere <= 122){
        posicao = caractere - 97;
    }
    return posicao; //se retornar -1 é pq deu merda
}

void preenche_vet_qtde_alunos(const Aluno *aluno, int q, int *v){
    for (int i = 0; i < q; ++i) {
        v[converte_ascII_em_posicao_vetorial(aluno[i].Nome[0])]++;
    }
}

void bucket_sort_alunos(Aluno *alunos, PilhaAlunos *pilhas, int qtde_alunos){
    //Joga cada aluno em uma posição do vetor de pilhas, fazendo-se então um bucket sort
    int pos_vet_pilha;
    for (int i = 0; i < qtde_alunos; ++i) {
        pos_vet_pilha = converte_ascII_em_posicao_vetorial(alunos[i].Nome[0]);
        Empilha(alunos[i], &pilhas[pos_vet_pilha]);
    }
}

void ordenar_pilha(PilhaAlunos *pilha){//Inserção
    Aluno aluno_aux;
    for (int i = 0; i < pilha->qtde_alunos; ++i) {
        for (int j = i+1; j < pilha->qtde_alunos; ++j) {
            if(pilha->alunos[i].Nota > pilha->alunos[j].Nota){
                aluno_aux = pilha->alunos[i];
                pilha->alunos[i] = pilha->alunos[j];
                pilha->alunos[j] = aluno_aux;
            }
        }
    }
}

void ordenar_pilhas_separado(PilhaAlunos *pilhas){
    for (int i = 0; i < TAM_VET_PILHA1; ++i) {
        if(pilhas[i].qtde_alunos > 0){
            ordenar_pilha(&pilhas[i]);
        }
    }
}

void imprimirPilhas(PilhaAlunos *pilhas, int q){
    for (int i = 0; i < q; ++i) {
        imprimirPilha(pilhas[i]);
    }
}

void tira_de_uma_pilha_e_taca_na_outra(PilhaAlunos *pilhas1, PilhaAlunos *pilhas2){
    int aux;
    for (int pos_pilha1 = 0; pos_pilha1 < TAM_VET_PILHA1; ++pos_pilha1) {
        aux = pilhas1[pos_pilha1].qtde_alunos;
        while(aux > 0){
            aux--;
            Empilha(pilhas1[pos_pilha1].alunos[aux], &pilhas2[pilhas1[pos_pilha1].alunos[aux].Nota]);
        }
    }
}

void ordenar_alunos(Aluno *alunos, PilhaAlunos *pilhas, PilhaAlunos *pilhas2, int qtde_alunos){
    bucket_sort_alunos(alunos, pilhas, qtde_alunos);//bukcket
    ordenar_pilhas_separado(pilhas);//ordenação entre cada pilha
    tira_de_uma_pilha_e_taca_na_outra(pilhas, pilhas2);
}

void preenche_vet_qtde_notas(Aluno *alunos, int q, int *v){
    for (int i = 0; i < q; ++i) {
        v[alunos[i].Nota]++;
    }
}

int main(int args, char *arg[]){
    int qtde_alunos, *vet_qtde_alunos, *vet_qtde_notas;
    PilhaAlunos *pilhas, *pilhas2;
    Aluno *alunos;
    char nome_arquivo[100];
    pilhas = malloc(sizeof(PilhaAlunos)*TAM_VET_PILHA1); //26 A - Z
    pilhas2 = malloc(sizeof(PilhaAlunos)*TAM_VET_PILHA2);
    alunos = malloc(sizeof(Aluno)*MAXTAM);
    vet_qtde_alunos = calloc(TAM_VET_PILHA1, sizeof(int));
    vet_qtde_notas = calloc(TAM_VET_PILHA2, sizeof(int));
    printf("Digite o nome do arquivo: ");
    scanf("%s", nome_arquivo);
    qtde_alunos = le_do_arquivo(alunos, nome_arquivo);
    preenche_vet_qtde_alunos(alunos, qtde_alunos, vet_qtde_alunos);
    preenche_vet_qtde_notas(alunos, qtde_alunos, vet_qtde_notas);
    prepara_pilhas1(pilhas, vet_qtde_alunos);
    prepara_pilhas2(pilhas2, vet_qtde_notas);
    ordenar_alunos(alunos, pilhas, pilhas2, qtde_alunos);
    imprimirPilhas(pilhas2, TAM_VET_PILHA2);
    free(pilhas);
    free(pilhas2);
    return 0;
}
