#include <stdio.h>
void dec2bin(int dec){
    int res; //variavel que vai colocar o binario
    res = dec%2;
    if(dec > 0){
        dec /= 2;
        dec2bin(dec);
        printf("%d", res);
    }
}

int main() {
    int n1;
    printf("Digite um numero inteiro: ");
    scanf("%d", &n1);
    printf("Resultado: ");
    if(n1 == 0){
        printf("0");
    }
    else{
        dec2bin(n1);
    }
    return 0;
}
