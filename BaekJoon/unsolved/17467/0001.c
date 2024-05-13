#include <stdio.h>

#define ll long long

int main(void){
    ll i;
    ll iN, iP;
    ll res;
    ll mu, k;

    scanf("%lld %lld", &iN, &iP);

    for(k = 1; ((ll)1 << k) < iP ; k++);
    mu = ((ll)1 << (2*k)) / iP;


    res = 1;
    for(i = 1; i <= iN; i++){
        res = (res * i ) % iP;
        res = res * i;
        if(res > iP){ // Barrett Reduction
            res = res - (((res >> k) * mu ) >> k ) * iP;
            if(res > iP) res -= iP;
            if(res > iP) res -= iP;
        }
    }
    printf("%lld\n", res);

    return 0;
}