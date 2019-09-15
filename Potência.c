#include <stdio.h>
int mult(int base, int exp){
    if(exp != 0){
        exp--;
        base *= mult(base, exp);
        return base;
    }
    return 1;
}

int main() {
    int base, expoente;
    printf("Digite a base e o expoente inteiros: ");
    scanf("%d %d", &base, &expoente);
    printf("Resultado: %d", mult(base, expoente));
    return 0;
}
