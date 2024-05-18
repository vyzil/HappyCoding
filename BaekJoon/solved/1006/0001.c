#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))

int main(void){
    int i, j;
    int T;
    int N, W;
    int *arr[2];
    int DP[2][4];
    int start, col, c, p, cState, pState, max;

    scanf("%d", &T);
    while(T--){
        scanf("%d %d", &N, &W);
        arr[0] = (int*)malloc(sizeof(int)*(N+1));
        arr[1] = (int*)malloc(sizeof(int)*(N+1));
        for(i = 0; i < N; i++) scanf("%d", &arr[0][i]);
        for(i = 0; i < N; i++) scanf("%d", &arr[1][i]);

        arr[0][N] = arr[0][0];
        arr[1][N] = arr[1][0];

        max = 0;
        for(start = 0b00; start < 0b100; start++){
            for(j = 0; j < 4; j++) DP[0][j] = -2;
            DP[0][start] = 0;
            for(col = 1; col <= N; col++){
                c = col % 2;
                p = 1 - c;
                for(j = 0; j < 4; j++) DP[c][j] = 0;
                for(pState = 0b00; pState < 0b100; pState++){
                    if((pState == 0b00) && arr[0][col-1] + arr[0][col] <= W && arr[1][col-1] + arr[1][col] <= W) DP[c][0b11]= MAX(DP[c][0b11], DP[p][pState] + 2);
                    if(((pState & 0b10) == 0) && arr[0][col-1] + arr[0][col] <= W) DP[c][0b10] = MAX(DP[c][0b10], DP[p][pState] + 1);
                    if(((pState & 0b01) == 0) && arr[1][col-1] + arr[1][col] <= W) DP[c][0b01] = MAX(DP[c][0b01], DP[p][pState] + 1);
                    if(arr[0][col] + arr[1][col] <= W) DP[c][0b11] = MAX(DP[c][0b11], DP[p][pState] + 1);
                    DP[c][0b00] = MAX(DP[c][0b00], DP[p][pState]);
                }
                // printf("%d : %d %d %d %d\n", col, DP[c][0], DP[c][1], DP[c][2], DP[c][3]);
            }
            max = MAX(max, DP[c][start]);
            // printf("%d\n", max);
        }

        printf("%d\n", 2 * N - max);

        free(arr[0]);
        free(arr[1]);
    }

}