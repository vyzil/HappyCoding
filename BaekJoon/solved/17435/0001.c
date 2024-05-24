#include <stdio.h>
#include <stdlib.h>

#define N_LOG_MAX 20

int main(void){
    int i, j;
    int M, Q;
    int n, x, res, idx;
    int **preCompute;

    scanf("%d", &M);

    preCompute = (int**)malloc(sizeof(int*)*N_LOG_MAX);
    
    preCompute[0] = (int*)malloc(sizeof(int)*(M+1));
    for(j = 1; j <= M; j++) scanf("%d", &preCompute[0][j]);
    for(i = 1; i < N_LOG_MAX; i++) {
        preCompute[i] = (int*)malloc(sizeof(int)*M);
        for(j = 1; j <= M; j++) preCompute[i][j] = preCompute[i-1][preCompute[i-1][j]];
    }
    

    scanf("%d", &Q);
    while(Q--){
        scanf("%d %d", &n, &x);
        
        idx = 0;
        res = x;
        // printf("%d -> ", res);
        while(n){
            if(n & 1) res = preCompute[idx][res];
            // printf("%d -> ", res);
            n >>= 1;
            idx++;
        }

        printf("%d\n", res);
    }

    for(i = 0; i < N_LOG_MAX; i++) free(preCompute[i]);
    free(preCompute);

    return 0;
}