#include <stdio.h>

#define MOD 1000000000

int main(void){
    int i;
    int N, K;
    long long res;
    scanf("%d %d", &N, &K);

    K -= 1;
    N += K;
    K = (N-K > K ? K : N-K);
    for(i = 0, res = 1; i < K; i++ ) {
        res *= (N-i);
        res /= (i+1);
    }

    printf("%lld\n", res%MOD);

    return 0;
}