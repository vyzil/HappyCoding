#include <stdio.h>
#include <stdlib.h>

/* 
 *    0       1       2       3       4
 *  -|o|-   -|-|-   -|-|-   -|-|-   -|o|-
 *  -|o|-   o|o|-   -|o|-   -|o|o   o|-|-
 *  -|-|-   -|-|-   -|o|-   -|-|-   -|-|-
 *  [0,1]   [0,2]   [0,3]   [0,4]   [1,2]
 * 
 *    5       6       7       8       9
 *  -|o|-   -|o|-   -|-|-   -|-|-   -|-|-
 *  -|-|-   -|-|o   o|-|-   o|-|o   -|-|o
 *  -|o|-   -|-|-   -|o|-   -|-|-   -|o|-
 *  [1,3]   [1,4]   [2,3]   [2,4]   [3,4]
 * 
 *  -|1|- 
 *  2|0|4 
 *  -|3|- 
 */

#define COST_MAX 400000

const int COST[5][5] = 
{
    COST_MAX,   2,  2,  2,  2,
    COST_MAX,   1,  3,  4,  3, 
    COST_MAX,   3,  1,  3,  4,
    COST_MAX,   4,  3,  1,  3,
    COST_MAX,   3,  4,  3,  1
};


void updateDP(int ***dpPTR, int ***tmpPTR, int num){
    int i, j;
    int **dp, **tmp;

    dp = *dpPTR;
    tmp = *tmpPTR;
    
    for(i = 0; i < 5; i++){
        for(j = i+1; j < 5; j++) tmp[i][j] = COST_MAX;
    }
    
    for(i = 0; i < 5; i++){
        for(j = i+1; j < 5; j++){
            if(dp[i][j] == COST_MAX) continue;
            // Some non-used value can be updated, but doesn't matter
            tmp[i][num] = (tmp[i][num] > dp[i][j] + COST[j][num] ? dp[i][j] + COST[j][num] : tmp[i][num] );
            tmp[num][i] = (tmp[num][i] > dp[i][j] + COST[j][num] ? dp[i][j] + COST[j][num] : tmp[num][i] );
            tmp[j][num] = (tmp[j][num] > dp[i][j] + COST[i][num] ? dp[i][j] + COST[i][num] : tmp[j][num] );
            tmp[num][j] = (tmp[num][j] > dp[i][j] + COST[i][num] ? dp[i][j] + COST[i][num] : tmp[num][j] );
        }
    }

    *dpPTR  = tmp;
    *tmpPTR = dp;

    return;
}


int main(void){
    int i, j, min;
    int iNum;
    int **dp, **tmp;

    scanf("%d", &iNum);
    if(iNum == 0){
        printf("0\n");
        return 0;
    }

    dp  = (int**)malloc(sizeof(int*)*5);
    tmp = (int**)malloc(sizeof(int*)*5);
    for(i = 0; i < 5; i++){
        dp[i]  = (int*)malloc(sizeof(int)*5);
        tmp[i] = (int*)malloc(sizeof(int)*5);
        for(j = i+1; j < 5; j++) dp[i][j] = COST_MAX;
    }

    dp[0][iNum] = 2;
    while(scanf("%d", &iNum)) {
        if(iNum == 0) break;
        updateDP(&dp, &tmp, iNum);
    }

    // print
    min = COST_MAX;
    for(i = 0; i < 5; i++){
        for(j = i+1; j < 5; j++){
            if(min > dp[i][j]) min = dp[i][j];
        }
    }
    printf("%d\n", min);

    for(i = 0; i < 5; i++){
        free(dp[i]);
        free(tmp[i]);
    }    
    free(dp);
    free(tmp);

    return 0;
}