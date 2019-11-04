/*
 * Nome: Antônio Pierre Martins Vieira
 * Data: 04/11/2019
 * JetBrains --> Clion IDE
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXTAM 70
typedef char TipoChave[100];
typedef int TipoApontador;

typedef struct {
    TipoChave Nome;
    int Nota;
} Aluno;

typedef struct {
    Aluno Item[MAXTAM];
    TipoApontador Topo;
} TipoPilha;

int le_do_arquivo(const char *nome_arquivo, Aluno *alunos){
    FILE *arq;
    int result;
    // Abre um arquivo BINÁRIO para LEITURA
    arq = fopen(nome_arquivo, "rb");
    if (arq == NULL){// Se houve erro na abertura
        printf("Problemas na abertura do arquivo\n");
        exit(0);
    }
    result = fread (alunos, sizeof(Aluno), MAXTAM, arq);
    fclose(arq);
    printf("\n");
    return result;
}

void FPVazia(TipoPilha *Pilha){
    Pilha->Topo = 0;
}

int Vazia(TipoPilha Pilha){
    return (Pilha.Topo == 0);
}

void Empilha(Aluno x, TipoPilha *Pilha){
    if (Pilha->Topo == MAXTAM){
        printf(" Erro   pilha est  a  cheia\n");
    }
    else {
        Pilha->Topo++;
        Pilha->Item[Pilha->Topo - 1] = x;
    }
}

void Desempilha(TipoPilha *Pilha, Aluno *Item){
    if (Vazia(*Pilha)){
        printf(" Erro   pilha est  a  vazia\n");
    }
    else {
        *Item = Pilha->Item[Pilha->Topo - 1];
        Pilha->Topo--;
    }
}


void Imprime(TipoPilha *Pilha){
    TipoPilha Pilhaux;
    Aluno x;
    FPVazia(&Pilhaux);
    while (!Vazia(*Pilha)){
        Desempilha(Pilha, &x);
        Empilha(x, &Pilhaux);
    }
    while (!Vazia(Pilhaux)){
        Desempilha(&Pilhaux, &x);
        printf("%s\n%d\n", x.Nome, x.Nota);
    }
}

void bucket_sort(Aluno *alunos, int qtde, TipoPilha *pilha){
    for (int bucket_position = 0; bucket_position <= 10; ++bucket_position){//cada posição recorrente é a posição para um bucket
        for (int i = 0; i < qtde; ++i) {
            if(alunos[i].Nota == bucket_position){
                Empilha(alunos[i], pilha);
            }
        }
    }
}

int main(){
    Aluno *alunos;
    int qtde_alunos;
    char nome_arquivo[100];
    TipoPilha pilha;
    alunos = malloc(sizeof(Aluno)*MAXTAM);
    FPVazia(&pilha);
    printf("Digite o nome do arquivo: ");
    scanf("%s", nome_arquivo);
    qtde_alunos = le_do_arquivo(nome_arquivo, alunos);
    bucket_sort(alunos, qtde_alunos, &pilha);
    Imprime(&pilha);
    return 0;
}
