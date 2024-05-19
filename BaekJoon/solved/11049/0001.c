#include <stdio.h>
#include <stdlib.h>

#define I_MAX 2147483647
#define MIN(x, y) ((x) < (y) ? (x) : (y))

typedef struct _NODE{
    int r, c;
} NODE;

int main(void){
    int i, j, k;
    int N;
    int r, c;
    NODE *M;
    int **DP;

    scanf("%d", &N);
    M = (NODE*)malloc(sizeof(NODE)*N);
    for(i = 0; i < N; i++) scanf("%d %d", &M[i].r, &M[i].c);

    DP = (int**)malloc(sizeof(int*)*N);
    for(i = 0; i < N; i++) {
        DP[i] = (int*)calloc((N-i), sizeof(int));
        if(i == 0) k = 0;
        else k = I_MAX;
        for(j = 0; j < N-i; j++) DP[i][j] = k;
    }
    

    for(i = 0; i < N; i++){
        for(j = 0; j < N-i; j++){
            for(k = 0; k < i; k++){
                DP[i][j] = MIN(DP[i][j], DP[k][j] + DP[i-(k+1)][j+k+1] + M[j].r * M[j+k].c * M[j+i].c);
            }
        }
    }

    printf("%d\n", DP[N-1][0]);
    // free
    for(i = 0; i < N; i++) free(DP[i]);
    free(DP);

    return 0;
}