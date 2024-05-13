#include <stdio.h>
#include <stdlib.h>

#define COST_MAX 10000000

int main(void){
    int i, j;
    int iN, iM;
    int iA, iB, iC;
    int src, dst, mid;
    int **costArr;

    scanf("%d", &iN);   // Number of Cities
    scanf("%d", &iM);   // Number of Buses

    costArr = (int**)malloc(sizeof(int*)*iN);
    for(i = 0; i < iN; i++){
        costArr[i] = (int*)malloc(sizeof(int)*iN);
        for(j = 0; j < iN; j++) costArr[i][j] = COST_MAX;
    }

    for(i = 0; i < iM; i++){
        scanf("%d %d %d", &iA, &iB, &iC);
        iA--; 
        iB--;
        if (costArr[iA][iB] > iC) costArr[iA][iB] = iC;
    }

    for(mid = 0; mid < iN; mid++){
        for(src = 0; src < iN; src++){
            if(src == mid) continue;
            for(dst = 0; dst < iN; dst++){
                if(dst == src || dst == mid) continue;
                if(costArr[src][dst] > costArr[src][mid] + costArr[mid][dst]){
                    costArr[src][dst] = costArr[src][mid] + costArr[mid][dst];
                }
            }
        }
    }

    for(i = 0; i < iN; i++){
        for(j = 0; j < iN; j++){
            if(costArr[i][j] == COST_MAX) printf("0 ");
            else printf("%d ", costArr[i][j]);
        }
        printf("\n");
    }


}