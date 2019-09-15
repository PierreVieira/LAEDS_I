#include <stdio.h>
int mdc(int a, int b){
    int res;
    res = a%b;
    if(res != 0){
        return mdc(b, res);
    }
    return b;
}

int main() {
    int n1, n2;
    printf("Digite dois numeros inteiros: ");
    scanf("%d %d", &n1, &n2);
    if(n1 > n2){
        printf("Resultado: %d", mdc(n1, n2));
    } else{
        printf("Resultado: %d", mdc(n2, n1));
    }
    return 0;
}
