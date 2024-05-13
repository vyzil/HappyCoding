#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000000

int main(void){
    int i, j;
    int N, K;
    int** DP;

    scanf("%d %d", &N, &K);

    K -= 1;
    
    DP = (int**)malloc(sizeof(int*)*(N+1));
    for(i = 0; i <= N; i++) {
        DP[i] = (int*)malloc(sizeof(int)*(K+1));
        DP[i][0] = 1;
    }
    for(i = 1; i <= K; i++) DP[0][i] = 1;
    

    for(i = 1; i <= N; i++){
        for(j = 1; j <= K; j++) DP[i][j] = (DP[i-1][j] + DP[i][j-1]) % MOD;
    }

    printf("%d\n", DP[N][K]);

    return 0;
}