#include <stdio.h>
#include <stdlib.h>

typedef struct POINT{
    int x;
    int y;
} point;

int distance(point A, point B){
    
    return abs(A.x - B.x) + abs(A.y - B.y);
}

int main(void){
    int i, j;
    int N, W;
    point *caseArr, car1Init, car2Init;
    point start, end, curP;
    int **DP;
    int minA, minB, tmpDis;
    int *historyA, *historyB, idxA, idxB;
    int min;
    char* res;

    scanf("%d", &N);        
    car1Init.x = 1; car1Init.y = 1;
    car2Init.x = N; car2Init.y = N;

    scanf("%d", &W);
    caseArr = (point*)malloc(sizeof(point)*(W+1));
    for(i = 1; i <= W; i++) scanf("%d %d", &caseArr[i].x, &caseArr[i].y);

    DP = (int**)malloc(sizeof(int*)*(W+1));
    for(i = 0; i <= W; i++) DP[i] = (int*)calloc(W+1, sizeof(int));

    historyA = (int*)malloc(sizeof(int)*W);
    historyB = (int*)malloc(sizeof(int)*W);
    res = (char*)malloc(sizeof(char)*W);


    for(i = 0; i < W; i++){        
        // DP[i][i+1] & DP[i+1][i]
        if(i == 0) {
            minA = 0;
            minB = 0;
        }
        else {
            minA = DP[i][0];
            minB = DP[0][i];
        }   
        minA += distance(car1Init, caseArr[i+1]);
        minB += distance(car2Init, caseArr[i+1]);      

        idxA = 0;
        idxB = 0;  
        
        for(j = 1; j < i; j++){
            tmpDis = distance(caseArr[j], caseArr[i+1]);
            if(minA > DP[i][j] + tmpDis) {
                minA = DP[i][j] + tmpDis;
                idxA = j;
            }
            if(minB > DP[j][i] + tmpDis){
                minB = DP[j][i] + tmpDis;
                idxB = j;
            } 
        }

        historyA[i] = idxA;
        historyB[i] = idxB;

        DP[i][i+1] = minA;
        DP[i+1][i] = minB;
        // DP[i][~] & DP[~][i]
        for(j = i+2; j <= W; j++){
            tmpDis = distance(caseArr[j-1], caseArr[j]);
            DP[i][j] = DP[i][j-1] + tmpDis;
            DP[j][i] = DP[j-1][i] + tmpDis;
        }
    }


    for(i = 0; i <= W; i++){
        for(j = 0; j <= W; j++) printf("%4d ", DP[i][j]);
        printf("\n");
    }

    min = DP[0][W];
    for(j = 0; j < W; j++){
        if(min > DP[j][W]){
            min = DP[j][W];            
            curP.x = j;
            curP.y = W;
        }
        if(min > DP[W][j]){
            min = DP[W][j];
            curP.x = W;
            curP.y = j;
        }
    }
    printf("%d\n", min);

    for(j = W-1; j >= 0; j--){
        if(curP.x > curP.y) {
            res[j] = '2';
            curP.x--;
            if(curP.x == curP.y){
                curP.x = historyB[curP.y];
            }
        }
        else {
            res[j] = '1';
            curP.y--;            
            if(curP.x == curP.y){
                curP.y = historyA[curP.x];
                
            }
        }
    }
    
    for(i = 0; i < W; i++) printf("%c\n", res[i]);

    return 0;
}
