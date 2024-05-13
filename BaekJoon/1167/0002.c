#include <stdio.h>
#include <stdlib.h>

typedef struct NODE{    
    int dst;
    int len;
    struct NODE *next;
}NODE;

int main(void){
    int N, src, dst, len;
    int i, j;
    int max;
    NODE **root, *newNode, *curNode;
    int* visited, *stackData, *stackLen, stackTop;
    int curV, curL;
    int isEnd;

    scanf("%d", &N);
    root = (NODE**)malloc(sizeof(NODE*)*N);    
    for(i = 0; i < N; i++){
        scanf("%d", &src);
        root[src-1] = (NODE*)malloc(sizeof(NODE));
        root[src-1]->next = NULL;
        for(scanf("%d", &dst); dst != -1; scanf("%d", &dst)){
            scanf("%d", &len);            
            newNode= (NODE*)malloc(sizeof(NODE));
            newNode->dst = dst-1;
            newNode->len = len;
            newNode->next = root[src-1]->next;
            root[src-1]->next = newNode;
        }
    }

    max = 0;
    visited  = (int*)malloc(sizeof(int)*N);
    stackData = (int*)malloc(sizeof(int)*N);
    stackLen = (int*)malloc(sizeof(int)*N);
    stackTop = 0;
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++) visited[j] = 0;        
        stackTop = 0;
        stackData[stackTop] = i;
        stackLen[stackTop] = 0;
        while(stackTop >= 0){
            curV = stackData[stackTop];
            curL = stackLen[stackTop];
            visited[curV] = 1;
            curNode = root[curV]->next;
            isEnd = 1;
            while(curNode){
                if(visited[curNode->dst] == 0) {
                    isEnd = 0;
                    stackTop++;
                    stackData[stackTop] = curNode->dst;
                    stackLen[stackTop] = curL + curNode->len;
                }
                curNode = curNode->next;
            }
            if(isEnd){
                if(max < stackLen[stackTop]) max = stackLen[stackTop];
                stackTop--;
            }
        }

    }
    printf("%d\n", max);

    // free should be done..

    return 0;
}