#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define N_MAX 5001

int DP1[N_MAX][N_MAX] = {0};
int DP2[N_MAX][N_MAX] = {0};

int main(void){
    int i, j;
    int N, Q;
    int l, r, cnt, max, range;
    char *inputStr;

    scanf("%d", &N);
    inputStr = (char*)malloc(sizeof(char)*(N+1));
    scanf("%s", inputStr);

    // make DP
    for(i = 0; i < N-1; i++){
        range = MIN(i, (N-1) - (i+1)) + 1;
        cnt = 0;
        for(j = 0; j < range; j++){
            if(inputStr[i-j] == inputStr[i+1+j]) cnt++;
            DP1[i][j] = cnt;
        }
    }
    memcpy(DP2, DP1, sizeof(DP1));
    for(i = 0; i < (N-1); i++){
        range = MIN(i, (N-1) - (i+1)) + 1;
        for(j = 0; j < range; j++){
            if(i > 0 && j > 0 && DP1[i][j] < DP1[i-1][j-1]) DP1[i][j] = DP1[i-1][j-1]; // i, j
            if((N-1) > (N-1)-(i+1) + 1 && j > 0 && DP2[(N-1)-(i+1)][j] < DP2[(N-1)-(i+1)+1][j-1]) DP2[(N-1)-(i+1)][j] = DP2[(N-1)-(i+1)+1][j-1]; // (N-1)-(i+1), j
        }
    }

    scanf("%d", &Q);
    while(Q--){        
        scanf("%d %d", &l, &r);
        l--; r--;

        int mid = (l + r)/2;
        range = MIN(mid - l, r - (mid+1));

       // printf("%d %d\n", mid, range);
        max = 0;
        if((l + r) % 2) max = MAX(DP1[mid][range], DP2[mid][range]);
        else if(mid > 0) max = MAX(DP1[mid-1][range], DP2[mid][range]);
        printf("%d\n", max);
    }

    return 0;
} 