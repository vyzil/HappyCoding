#include <stdio.h>
#include <stdlib.h>

#define DIST_MAX 10000*100

typedef struct NODE{
    int dst;
    int weight;
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
            if(distanceArr[j] < min && visited[j] == 0) {
                min = distanceArr[j];
                curIdx = j;
            }
        }
        visited[curIdx] = 1;
        curNode = treeNode[curIdx];
        while(curNode->next){
            if(distanceArr[curNode->next->dst] > min + curNode->next->weight){
                distanceArr[curNode->next->dst] = min + curNode->next->weight;
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
    int iN, iS, iE, iV;
    int *maxIdx, *maxValue;
    NODE **treeNode, *newNode;

    scanf("%d", &iN);

    treeNode = (NODE**)malloc(sizeof(NODE*)*iN);
    for(i = 0; i < iN; i++) {
        treeNode[i] = (NODE*)malloc(sizeof(NODE));
        treeNode[i]->next = NULL;
    }

    for(i = 0; i < iN-1; i++){
        scanf("%d %d %d", &iS, &iE, &iV);
        iS--; iE--;
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->dst = iE;
        newNode->weight = iV;
        newNode->next = treeNode[iS]->next;
        treeNode[iS]->next = newNode;
        
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->dst = iS;
        newNode->weight = iV;
        newNode->next = treeNode[iE]->next;
        treeNode[iE]->next = newNode;         
    }

    maxIdx = (int*)malloc(sizeof(int));
    maxValue = (int*)malloc(sizeof(int));
    Dijkstra(treeNode, 0, iN, maxIdx, maxValue);
    Dijkstra(treeNode, *maxIdx, iN, maxIdx, maxValue);
    
    printf("%d\n", *maxValue);

    return 0;
}