#include <stdio.h>
int Digitos(int n1){
    int cont = 1;
    n1 /= 10;
    if(n1 == 0){
        return 0;
    }
    if(n1 >= 10){
        cont += Digitos(n1);
    }
    return cont;
}

int main() {
    int n1, res = 0;
    printf("Digite um numero inteiro: ");
    scanf("%d", &n1);
    res = Digitos(n1);
    printf("Resultado: %d", res+1);
    return 0;
}
