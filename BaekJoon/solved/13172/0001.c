#include <stdio.h>

#define P 1000000007

// a/b to int
int redc(int a, int b){
    int i;
    long long res, tmp;

    tmp = b;
    res = 1;
    for(i = P - 2; i > 0; i >>= 1){
        if(i & 1) res = (res * tmp) % P;
        tmp = (tmp * tmp) % P;
    }
    res = (res * a) % P;
    
    return (int)res;
}

int main(void){
    int i;
    int iM, iN, iS;
    int sum;

    scanf("%d", &iM);
    sum = 0;
    for(i = 0; i < iM; i++) {
        scanf("%d %d", &iN, &iS);
        sum = (sum + redc(iS, iN) )% P;
    }

    printf("%d\n", sum);

    return 0;
}