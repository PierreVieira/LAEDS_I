/*
 * Nome do autor: Antônio Pierre Martins Vieira
 * Data de início do código: 23/08/2019
 * Data de conclusão do código: 24/08/2019
 * JetBrains ---> Clion IDE
 * A ideia principal do código está no escopo da solve_step
 */
#include <stdio.h>
#include <stdlib.h>
void the_last_print(int n){
    for (int i = 0; i <n ; ++i) {
        if (i != n-1){
            printf("1 + ");
        }
    }
    printf("1");
}

int soma_elementos_vetor(int *vetor, int tamanho_vetor){
    int soma = 0;
    for (int i = 0; i < tamanho_vetor; ++i) {
        soma += vetor[i];
    }
    return soma;
}
int soma_anteriores(int *vetor, int i){
    int soma = 0;
    for (int j = 0; j <= i; ++j) {
        soma += vetor[j];
    }
    return soma;
}

void printa_vetor(int *vetor, int tamanho_vetor){
    int soma_do_vetor;
    soma_do_vetor = soma_elementos_vetor(vetor, tamanho_vetor);
    for (int i = 0; i < tamanho_vetor; ++i) {
        if(vetor[i] != 0){
            if(i == 0){
                printf("%d + ", vetor[i]);
            }
            else if(soma_anteriores(vetor, i) < soma_do_vetor){
                printf("%d + ", vetor[i]);
            }
            else{
                printf("%d\n", vetor[i]);
            }
        }
    }
}

void modifica_vetor(int *vetor, int numero, int pos, int tamanho_vetor){
    int soma_vetor, o_tanto_que_falta;
    for (int i = 0; i <tamanho_vetor ; ++i) {
        soma_vetor = soma_elementos_vetor(vetor, tamanho_vetor);
        o_tanto_que_falta = numero - soma_vetor;
        if (vetor[i] == 0){
            if(o_tanto_que_falta > vetor[pos-1]){
                vetor[i] = vetor[pos-1];
            }
            else{
                vetor[i] = o_tanto_que_falta;
            }
        }
    }
}

int todo_mundo_eh_1(int *vetor, int t){
    for (int i = 1; i < t ; ++i) {
        if(vetor[i] != 1){
            return 0; //return False
        }
    }
    return 1; //return True
}
int maior_valor(int *vetor, int tamanho_vetor){
    int maior = vetor[0];
    for (int i = 0; i < tamanho_vetor ; ++i) {
        if (vetor[i] > maior){
            maior = vetor[i];
        }
    }
    return maior;
}

int so_tem_maior_zero_e_1(int *vetor, int maior, int tamanho_vetor){
    for (int i = 0; i < tamanho_vetor; ++i) {
        if (vetor[i] != 0 && vetor[i] != 1 && vetor[i] != maior){
            return 0;//False
        }
    }
    return 1;//True
}

int ultima_aparicao_do_maximo(int *vetor, int maior, int tamanho_vetor){
    int ultima_pos = 0;
    for (int i = 0; i < tamanho_vetor; ++i) {
        if(vetor[i] == maior){
            ultima_pos = i;
        }
    }
    return ultima_pos;
}

int so_tem_repetidos_no_vetor_diferentes_de_0(int *vetor, int tamanho_vetor){
    int n = vetor[0];
    for (int i = 0; i < tamanho_vetor; ++i) {
        if(vetor[i] != n && vetor[i] != 0){
            return 0; //return False
        }
    }
    return 1; //return True
}

int identifica_menor_maior_que_1(int *vetor, int tamanho_vetor){
    int menor_maior_que_1 = vetor[0];
    for (int i = 0; i < tamanho_vetor; ++i) {
        if(vetor[i] < menor_maior_que_1 && vetor[i] > 1){
            menor_maior_que_1 = vetor[i];
        }
    }
    return menor_maior_que_1;
}

int identifica_pos_decremento(int *vetor, int tamanho_vetor){
    int maior, pos_decremento, menor_maior_que_1;
    maior = maior_valor(vetor, tamanho_vetor);
    if(so_tem_maior_zero_e_1(vetor, maior, tamanho_vetor)){
        pos_decremento = ultima_aparicao_do_maximo(vetor, maior, tamanho_vetor);
    }
    else{
        if(so_tem_repetidos_no_vetor_diferentes_de_0(vetor, tamanho_vetor)){
            menor_maior_que_1 = maior;
        }
        else{
            menor_maior_que_1 = identifica_menor_maior_que_1(vetor, tamanho_vetor);
        }
        pos_decremento = 1;
        for (int i = 0; i < tamanho_vetor; ++i) {
            if(vetor[i] == menor_maior_que_1){
                pos_decremento = i;
            }
        }
    }
    return pos_decremento;
}

void zera_posicoes_desejadas(int *vetor, int pos_decremento, int tamanho_vetor){
    for (int i = pos_decremento+1; i < tamanho_vetor ; ++i) {
        vetor[i] = 0;
    }
}

int pos_primeiro_zero_encontrado(int *vetor, int tamanho_vetor){
    for (int i = 0; i < tamanho_vetor ; ++i) {
        if(vetor[i] == 0){
            return i;
        }
    }
    return tamanho_vetor - 1;//Quer dizer que não tem 0 no vetor
}

int solve_step(int numero, int aux){
    /*
     * Encher o código de comentários não é produtivo ao meu ponto de vista, e também já são 3:00 AM, serei breve. Desculpa aí Natália rsrs
     * Bom, quando eu estava resolvendo essa questão percebi dois padrões essenciais para minha lógica
     * 1 --> Sempre que eu for passar para um decremento de um numero x para outro (por exemplo, o usuario digitou 6) acontece o seguinte padrão
     * ===============
     * 6
     * ----------
     * 5 + 1
     * ----------
     * 4 + 2
     * 4 + 1 + 1
     * ----------
     * 3 + 3
     * 3 + 2 + 1
     * 3 + 1 + 1 + 1
     * ----------
     * 2 + 2 + 2
     * 2 + 2 + 1 + 1
     * 2 + 1 + 1 + 1 + 1
     * ----------
     * 1 + 1 + 1 + 1 + 1 + 1
     * ===============
     * Processo = o que está entre linhas simples como observado acima
     * Perceba que o que está entre --------- é um padrão, ou seja para passar para o proximo numero, eu necessariamente tenho que terminar o meu "print" de numeros 1 do processo anterior
     * 2 ---> O máximo de posições que o meu vetor do processo terá será o número digitado pelo usuário - o número do processo enterior + 1
     * Logo, quando estou em 2 (isso quando o usuario digita 6) preciso alocar um vetor de 5 posições ---> 6 - 2 + 1
     * O resto, é para sustentar minha lógica. Não tem muito o que dizer mesmo
     */
    int pos, *vetor, tamanho_vetor, pos_decremento;
    pos = 1;
    tamanho_vetor = aux - numero + 1;
    vetor = calloc(tamanho_vetor, sizeof(int));
    vetor[0] = numero;
    while(1){
        if(tamanho_vetor == 1){
            printf("%d\n", vetor[0]);
            break;
        }
        else{
            modifica_vetor(vetor, aux, pos, tamanho_vetor);
            printa_vetor(vetor, tamanho_vetor);
        }
        if (todo_mundo_eh_1(vetor, tamanho_vetor)){
            break;
        }
        pos_decremento = identifica_pos_decremento(vetor, tamanho_vetor);
        vetor[pos_decremento] = vetor[pos_decremento] - 1;
        zera_posicoes_desejadas(vetor, pos_decremento, tamanho_vetor);
        pos = pos_primeiro_zero_encontrado(vetor, tamanho_vetor);
    }
    return numero - 1;//O numero vai receber como retorno ele -1
}

int main(){
    int numero, aux;
    printf("Digite um numero inteiro: ");
    scanf("%d", &numero);
    aux = numero;
    printf("Decomposicao: \n");
    if(numero <= 0){//Se o número for 0 ou 1 não é necessário realizar nenhuma operação, só printa o número e pronto. Acredite, isso evita problemas futuros
        printf("%d\n", numero);
    }
    else{//Se não for, aí o negócio ja complica um pouquinho...
        while(1){//Loop "infinito"
            numero = solve_step(numero, aux);//Essa solve_step vai resolvendo aos poucos o problema, diminuindo o numero em questão de 1 em 1
            if(numero == 1){//Se o número for 1 eu saio do loop
                break;
            }
        }
        the_last_print(aux);//Então, após sair do loop tenho certeza que o número em questão é 1, logo é só printar N números 1 somando, onde N é o número digitado pelo usuário
    }
    return 0;
}
