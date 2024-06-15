#include <stdio.h>

#define ll long long


int main(void){
    ll bitMax;
    ll N, K;
    ll res[2];

    scanf("%lld", &N);
    for(bitMax = 1; bitMax <= N; bitMax <<= 1);
    bitMax--;
    res[0] = bitMax ^ N;
    res[1] = N;

    if(res[0]) printf("2\n%lld\n%lld\n", res[0], res[1]);
    else printf("1\n%lld\n",res[1]);

    return 0;
}