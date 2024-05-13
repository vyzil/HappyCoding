#include <stdio.h>
#include <stdlib.h>


typedef struct NODE{
    // nodeList[i] : num is count
    // node        : num is building number
    int num;
    struct NODE *next;
} NODE;

typedef struct HEAP{
    int idx;
    int time;
} heap;


int insertQueue(heap *nodeQ, int idx, int time, int qLast){
    int qIdx;

    qIdx = ++qLast;
    while(qIdx > 1){
        if(nodeQ[qIdx/2].time < time) break;
        nodeQ[qIdx].idx = nodeQ[qIdx/2].idx;
        nodeQ[qIdx].time = nodeQ[qIdx/2].time;
        qIdx /= 2;
    }

    nodeQ[qIdx].idx = idx;
    nodeQ[qIdx].time = time;

    return qLast;
}

int deleteQueue(heap *nodeQ, int qLast){
    int curTime, curIdx, qIdx;
    int childMin, childMinIdx;
    
    if(qLast < 1) return 0;

    nodeQ[0].idx = nodeQ[1].idx;
    nodeQ[0].time = nodeQ[1].time;

    curIdx = nodeQ[qLast].idx;
    curTime = nodeQ[qLast].time;
    qLast--;
    qIdx = 1;
    while(2*qIdx <= qLast) {
        childMin = nodeQ[2*qIdx].time;
        childMinIdx = 2*qIdx;
        if((2*qIdx + 1 <= qLast) && (childMin > nodeQ[2*qIdx + 1].time)){
            childMin = nodeQ[2*qIdx+1].time;
            childMinIdx = 2*qIdx + 1;
        }
        if(curTime < childMin) break;
        nodeQ[qIdx].idx = nodeQ[childMinIdx].idx;
        nodeQ[qIdx].time = childMin;

        qIdx = childMinIdx;
    }
    nodeQ[qIdx].idx = curIdx;
    nodeQ[qIdx].time = curTime;
    return 1;
}


int solve(){
    int i;
    int iN, iK;
    int iX, iY, iW;
    int *delayList;
    NODE **nodeList, *newNode, *curNode, *delNode;
    heap *nodeQ;
    int  qLast, qIdx, curIdx, curEndingTime, totalTime;

    scanf("%d %d", &iN, &iK);
    delayList = (int*)malloc(sizeof(int)*iN);
    nodeList = (NODE**)malloc(sizeof(NODE)*iN);

    // Delay Information
    for(i = 0; i < iN; i++){
        scanf("%d", delayList + i);
        nodeList[i] = (NODE*)malloc(sizeof(NODE));
        nodeList[i]->num = 0;
        nodeList[i]->next = NULL;
    }

    // Connection Information
    for(i = 0; i < iK; i++){
        scanf("%d %d", &iX, &iY);
        iX--; iY--;
        newNode = (NODE*)malloc(sizeof(NODE));        
        newNode->num = iY;
        newNode->next = nodeList[iX]->next;
        nodeList[iX]->next = newNode;
        nodeList[iY]->num++;
    }

    scanf("%d", &iW);
    iW--;

    // Calc (w. minHeap)
    nodeQ = (heap*)malloc(sizeof(heap)*iN);
    qLast = 0;
    totalTime = 0;
    for(curIdx = 0; curIdx < iN; curIdx++){
        if(nodeList[curIdx]->num == 0) {
            insertQueue(nodeQ, curIdx, delayList[curIdx], qLast++);
        }
    }

    while(deleteQueue(nodeQ, qLast--)){
        curIdx = nodeQ[0].idx;
        totalTime = nodeQ[0].time;
        if(curIdx == iW) break;

        curNode = nodeList[curIdx];
        while(curNode->next){
            if(--(nodeList[curNode->next->num]->num) == 0){
                insertQueue(nodeQ, curNode->next->num, totalTime + delayList[curNode->next->num], qLast++);
            }
            curNode = curNode->next;
        }
    }

    printf("%d\n", totalTime);

    // Free Here
    free(delayList);
    for(i = 0; i < iN; i++) {
        curNode = nodeList[i];
        if(curNode->next){
            delNode = curNode;
            curNode = curNode->next;
            free(delNode);
        }
        free(curNode);
    }
    free(nodeList);
    free(nodeQ);

    return 0;
}

int main(void){
    int iT;

    scanf("%d", &iT);
    while(iT--) solve();

    return 0;
}