#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000000

int main(void){
    int i, j;
    int N, K;
    int* DP;

    scanf("%d %d", &N, &K);
    
    DP = (int*)malloc(sizeof(int)*(N+1));    
    DP[0] = 1;
    
    for(i = 0; i < K; i++){
        for(j = 0; j < N; j++) DP[j+1] = (DP[j] + DP[j+1]) % MOD;
    }

    printf("%d\n", DP[N]);

    return 0;
}