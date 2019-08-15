/*
 * Autor: Pierre Vieira
 * Data atual do sistema: 15/08/2019
 * Clion ------> JetBrains IDE
 * Observação: esse programa foi inicialmente feito na sexta-feira 09/08/2019
 * Foram úteis para o desenvolvimento de raciocínio dessa questão os seguintes links abaixo
 * https://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html
 * https://www.ime.usp.br/~fmario/mac2166/challenge/fatorial.html
 * https://youtu.be/ECIvoHU67Q4
 * Acesse meu canal no Youtube: https://www.youtube.com/channel/UCGF4Ag9zGp6newv-tkSkTcA/videos
 */
#include<stdio.h>
#include <stdlib.h>
#define maximoBits 36000

void printa_vetor(int *V, int tamanho){//Printa o vetor de trás pra frente já que inicialmente ele está invertido
    for(int i = tamanho; i >= 0; --i){
        printf("%d",V[i]);
    }
}

int cerebroBits(int n, int *vetor_resultado, int tamanho){//Essa função irá realizar a multiplicação de um único bit
    int i, resultado = 0, operacao;
    for(i = 0 ; i <= tamanho; ++i){
        operacao = vetor_resultado[i]*n + resultado;
        resultado = operacao/10;
        vetor_resultado[i] = operacao%10;
    }
    while(resultado!=0){//Se o resultado é 0, então precisamos tratar esse "bit"
        vetor_resultado[i]=resultado%10;
        resultado /= 10;
        ++i;
    }
    --i;//Por algum motivo se eu não der esse -- ele dá pau :(
    return i;
}

int main(){
    int numero, tamanho = 0, *vetor_resultado;
    printf("Digite um numero inteiro: ");
    scanf("%d",&numero);
    if(numero == 1 || numero == 0){//Se o número for 1 ou 0 não é necessário executar o resto do programa para saber que o vetor_resultadoorial é 1
        printf("1");
    }
    else{
        vetor_resultado = calloc(maximoBits, sizeof(int));//Aloca um vetor de maximoBits de tamanho incializando com 0
        vetor_resultado[0]=1;//Começa em 1
        for(int i=0; i <= numero; ++i){//Iremos percorrer de 1 até o numero e não da forma tradicional (do numero ate 1)
            if(i > 1){//Se não estamos mais no número 1, então o vatorial não é 1 mais
                tamanho = cerebroBits(i, vetor_resultado, tamanho);//E então as multiplicações são feitas
            }
        }
        printf("Resultado: ");
        printa_vetor(vetor_resultado, tamanho);//Depois que já ta tudo ok é só printar o vetor e correr pro abraço
    }
    free(vetor_resultado);//Libera memória do vetor_resultado
    return 0;
}