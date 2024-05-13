#include <stdio.h>

#define ll long long
#define MOD 1000000007

int main(void) {
    ll N, M, tmp, sumN, sumM, res;
    scanf("%lld %lld", &N, &M);

    tmp = 2;
    sumN = 1;
    sumM = 1;
    while(N || M){
        if(N&1) sumN = (sumN * tmp) % MOD;
        if(M&1) sumM = (sumM * tmp) % MOD;
        tmp = (tmp * tmp) % MOD;
        N >>= 1;
        M >>= 1;
    }

    res = (sumN + sumM - 2) % MOD;
    if(res < 0) res += MOD;
    printf("%lld\n", res);

    return 0;
}