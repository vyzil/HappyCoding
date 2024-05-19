#include <stdio.h>

#define N_MAX 500
#define F_MAX 2000000000

#define MIN(x, y) ((x) < (y) ? (x) : (y))

typedef struct _NODE{
    int value;
    int fileSize;
} NODE;

int main(void){
    int i, j, k;
    int TC, N;
    NODE DP[N_MAX][N_MAX]; int num;
    int tmpValue;
    int tmpFileSize;

    scanf("%d", &TC);
    while(TC--){
        scanf("%d", &N);
        for(i = 0; i < N ;i++) scanf("%d", &DP[0][i].fileSize);
        for(i = 0; i < N; i++){
            if(i == 0) num = 0;
            else num = F_MAX;
            for(j = 0; j < N - i; j++) {
                DP[i][j].value = num;
            }
        }

        for(i = 1; i < N; i++){
            for(j = 0; j < N - i; j++){
                for(k = 0; k < i; k++){
                    tmpFileSize = DP[k][j].fileSize + DP[i-1-k][j+k+1].fileSize;
                    tmpValue = DP[k][j].value + DP[i-1-k][j+k+1].value + tmpFileSize;
                    if(tmpValue < DP[i][j].value) {
                        DP[i][j].value = tmpValue;
                        DP[i][j].fileSize = tmpFileSize;
                    }
                }
            }
        }
        printf("%d\n", DP[N-1][0].value);
    }

    return 0;
}