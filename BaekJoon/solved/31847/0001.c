#include <stdio.h>
#include <stdlib.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define N_MAX 5001

int DP[N_MAX][N_MAX] = {0};

int main(void){
    int i, j;
    int N, Q;
    int l, r, cnt, max, range;
    // int **DP;
    char *inputStr;

    scanf("%d", &N);
    inputStr = (char*)malloc(sizeof(char)*(N+1));
    scanf("%s", inputStr);

    // DP[i] = (int**)malloc(sizeof(int*)*N);
    // for(i = 0; i < N; i+ = (int*)calloc((N/2+1), sizeof(int));

    // make DP
    for(i = 0; i < N; i++){
        range = MIN(i, N - (i+1)) + 1;
        cnt = 0;
        for(j = 0; j < range; j++){
            if(inputStr[i-j] == inputStr[i+1+j]) cnt++;
            DP[i][j] = cnt;
        }
    }

    scanf("%d", &Q);
    while(Q--){        
        scanf("%d %d", &l, &r);
        l--; r--;

        max = 0;
        for(i = l; i < r; i++){
            range = MIN(i - l, r - (i + 1));
            if(max < DP[i][range]) max = DP[i][range];
        }
        printf("%d\n", max);
    }

    // // free
    // for(i = 0; i < N; i++) free(DP[i]);
    // free(DP);

    return 0;
} 