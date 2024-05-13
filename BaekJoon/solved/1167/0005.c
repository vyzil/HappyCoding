#include <stdio.h>
#include <stdlib.h>

#define DIST_MAX 100000*10000

typedef struct NODE{
    int dst;
    int len;
    struct NODE *next;
}NODE;

void Dijkstra(NODE **treeNode, int start, int size, int* maxIdx, int* maxValue){
    int i, j;
    int *distanceArr, *visited;
    int curIdx, min;
    NODE *curNode;
    
    distanceArr = (int*)malloc(sizeof(int)*size);
    visited = (int*)calloc(size, sizeof(int));

    for(i = 0; i < size; i++) distanceArr[i] = DIST_MAX;
    distanceArr[start] = 0;
    for(i = 0; i < size; i++){
        min = DIST_MAX;
        for(j = 0; j < size; j++) {
            if( visited[j] == 0 && distanceArr[j] < min) {
                min = distanceArr[j];
                curIdx = j;
            }
        }
        visited[curIdx] = 1;
        curNode = treeNode[curIdx];
        while(curNode->next){
            if(visited[curNode->next->dst] == 0 && distanceArr[curNode->next->dst] > min + curNode->next->len){
                distanceArr[curNode->next->dst] = min + curNode->next->len;
            }
            curNode = curNode->next;
        }
    }

    *maxIdx = 0;
    *maxValue = 0;
    for(i = 0; i < size; i++){
        if(distanceArr[i] > *maxValue){
            *maxValue = distanceArr[i];
            *maxIdx = i;
        }
    }

    free(distanceArr);
    return;
}

int main(void){
    int i;
    int iN, iSrc, iDst, iLen;
    int *maxIdx, *maxValue;
    NODE **treeNode, *newNode;

    scanf("%d", &iN);

    treeNode = (NODE**)malloc(sizeof(NODE*)*iN);
    
    for(i = 0; i < iN; i++){
        scanf("%d", &iSrc);
        treeNode[iSrc-1] = (NODE*)malloc(sizeof(NODE));
        treeNode[iSrc-1]->next = NULL;
        for(scanf("%d", &iDst); iDst != -1; scanf("%d", &iDst)){
            scanf("%d", &iLen);            
            newNode= (NODE*)malloc(sizeof(NODE));
            newNode->dst = iDst-1;
            newNode->len = iLen;
            newNode->next = treeNode[iSrc-1]->next;
            treeNode[iSrc-1]->next = newNode;
        }
    }

    maxIdx = (int*)malloc(sizeof(int));
    maxValue = (int*)malloc(sizeof(int));
    Dijkstra(treeNode, 0, iN, maxIdx, maxValue);
    Dijkstra(treeNode, *maxIdx, iN, maxIdx, maxValue);
    
    printf("%d\n", *maxValue);

    return 0;
}