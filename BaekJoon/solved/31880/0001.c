#include <stdio.h>

#define ll long long

int main(void){
    int i;
    int N, M;
    int a, b;
    ll res;

    scanf("%d %d", &N, &M);
    res = 0;
    for(i = 0; i < N; i++) {
        scanf("%d", &a);
        res += (ll)a;
    }
    for(i = 0; i < M; i++){
        scanf("%d", &b);
        if(b) res *= (ll)b;
    }
    
    printf("%lld\n", res);

    return 0;
}