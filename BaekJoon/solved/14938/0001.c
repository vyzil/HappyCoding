#include <stdio.h>
#include <stdlib.h>

#define LEN_MAX 100*100

typedef struct NODE {
    int dst;
    int len;
} node;

int main(void){
    int i, j, k;
    int iN, iM, iR;
    int iA, iB, iL;
    int *itemArr;
    int itemCount, maxItemCount;
    node **roadArr;

    scanf("%d %d %d", &iN, &iM, &iR);

    itemArr = (int*)malloc(sizeof(int)*iN);
    for(i = 0; i < iN; i++) scanf("%d", &itemArr[i]);

    roadArr = (node**)malloc(sizeof(node)*iN);
    for(i = 0; i < iN; i++){
        roadArr[i] = (node*)malloc(sizeof(node)*iN);
        for(j = 0; j < iN; j++) roadArr[i][j].len = LEN_MAX;
        roadArr[i][i].len = 0;
    }

    for(i = 0; i < iR; i++){
        scanf("%d %d %d", &iA, &iB, &iL);
        iA--; iB--;
        roadArr[iA][iB].len = iL;
        roadArr[iB][iA].len = iL;
    }

    for(i = 0; i < iN; i++) { // Select Row
        for(j = 0; j < iN; j++) { // update rest of the row 
            if(i == j) continue;
            for(k = 0; k < iN; k++){ // if(j -> i -> k) is better? update
                if(roadArr[j][i].len + roadArr[i][k].len < roadArr[j][k].len ) {
                    roadArr[j][k].len = roadArr[j][i].len + roadArr[i][k].len;
                }
            }
        }
    }

    maxItemCount = 0;
    
    for(i = 0; i < iN; i++){
        itemCount = 0;
        for(j = 0; j < iN; j++){
            if(roadArr[i][j].len <= iM) itemCount += itemArr[j];
        }
        free(roadArr[i]);
        if(maxItemCount < itemCount) maxItemCount = itemCount;
    }
    free(roadArr);

    printf("%d\n", maxItemCount);
    
    return 0;
}