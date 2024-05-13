#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000000

int gcd(int a, int b){
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(void){    
    int i;
    int N, K;
    int *arr, r, idx, tmp;
    long long res;

    scanf("%d %d", &N, &K);

    K -= 1;
    N += K;
    K = (N-K > K ? K : N-K);

    arr = (int*)malloc(sizeof(int)*K);
    for(i = 0; i < K; i++) arr[i] = N - i;
    for(i = K; i > 0; i--) {
        r = i;
        idx = N % i;
        while(r > 1) {
            if(arr[idx] % r == 0) {
                arr[idx] /= r;
                break;
            }
            tmp = gcd(r, arr[idx]);
            arr[idx] /= tmp;
            r /= tmp;
            idx = (idx + r) % K;
        }
    }

    for(i = 0, res = 1; i < K; i++) res = (res * arr[i]) % MOD;

    printf("%lld\n", res);

    return 0;
}