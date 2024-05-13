#include <stdio.h>
#include <stdlib.h> 

#define N_MAX 100000
#define false 0
#define true 1

typedef struct _NODE{
    int num;
    struct _NODE *next;
} NODE;

NODE *adjList;
int *heightList;
int *heightNum;

int dfsCheck(int N){
    int i;
    int curNum;
    int height;
    NODE* curNode;

    scanf("%d", &curNum); curNum--;
    if (curNum != 0) return 0;

    height = 1;
    heightList[curNum] = height;
    heightNum[height-1]++;

    curNode = &adjList[curNum];
    height++;
    while(curNode->next){
        if(heightList[curNode->next->num] == false) {
            heightList[curNode->next->num] = height;
            heightNum[height]++;
        }
        curNode = curNode->next;
    }

    for(i = 1; i < N; i++){
        while(heightNum[height] == 0) height--;
        scanf("%d", &curNum); curNum--;
        if(heightList[curNum] != height) return 0;

        curNode = &adjList[curNum];
        height++;
        while(curNode->next){
            if(heightList[curNode->next->num] == false) {
                heightList[curNode->next->num] = height;
                heightNum[height]++;
            }
            curNode = curNode->next;
        }

        while(heightNum[height] == 0){
            height--;
            heightNum[height]--;
        }

    }
    
    return 1;
}

int main(void){
    int i;
    int N, src, dst;
    NODE *newNode;

    scanf("%d", &N);

    adjList = (NODE*)malloc(sizeof(NODE)*N);
    heightList = (int*)malloc(sizeof(int)*N);
    heightNum = (int*)malloc(sizeof(int)*N);

    for(i = 0; i < N; i++) {
        adjList[i].num = 0;
        adjList[i].next = NULL;
        heightList[i] = 0;
        heightNum[i] = 0;
    }
    
    for(i = 0; i < N-1; i++){
        scanf("%d %d", &src, &dst);
        src--; dst--;
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->num = dst;
        newNode->next = adjList[src].next;
        adjList[src].next = newNode;
        adjList[src].num++;
        
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->num = src;
        newNode->next = adjList[dst].next;
        adjList[dst].next = newNode;
        adjList[dst].num++;

    }
    
    printf("%d\n", dfsCheck(N));

    // free should be done..
    
    return 0;
}