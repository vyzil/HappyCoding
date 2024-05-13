#include <stdio.h>
#include <stdlib.h>

#define DIST_MAX 200000
#define W_MAX 11

typedef struct NODE{    
    int dst;
    int len;
    struct NODE *next;
} NODE;

typedef struct QUEUE{
    int idx;
    int len;
} queue;

int deleteQueue(queue *Q, int *qLast){
    int curIdx;
    int lastIdx, lastLen;
    int lChildIdx, rChildIdx, nextIdx, curMin;

    if(*qLast == 0) return -1;

    Q[0].idx = Q[1].idx;
    Q[0].len = Q[1].len;
    
    if(*qLast == 1) {
        *qLast = 0;
        return 0;
    }

    lastIdx = Q[*qLast].idx;
    lastLen = Q[*qLast].len;
    *qLast = *qLast - 1;
    curIdx = 1;

    while(curIdx <= *qLast/2){
        lChildIdx = curIdx * 2;
        rChildIdx = curIdx * 2 + 1;
        
        curMin = Q[lChildIdx].len;
        nextIdx = lChildIdx;
        if(rChildIdx <= *qLast && Q[lChildIdx].len > Q[rChildIdx].len) {
            curMin = Q[rChildIdx].len;
            nextIdx = rChildIdx;
        }

        if(curMin >= lastLen) break;
        
        Q[curIdx].len = Q[nextIdx].len;
        Q[curIdx].idx = Q[nextIdx].idx;       

        curIdx = nextIdx;
    }

    Q[curIdx].idx = lastIdx;
    Q[curIdx].len = lastLen;

    return 0;
}
void insertQueue(queue *Q, int *qLast, int idx, int len){
    int curIdx, nextIdx; // nextIdx = parentIdx

    *qLast = *qLast + 1;
    curIdx = *qLast;
    while(curIdx > 1){
        nextIdx = curIdx / 2;
        if(Q[nextIdx].len > len){
            Q[curIdx].idx = Q[nextIdx].idx;
            Q[curIdx].len = Q[nextIdx].len;
        }
        else break;
        curIdx = nextIdx;
    }

    Q[curIdx].idx = idx;
    Q[curIdx].len = len;

}

int main(void){
    int i, j;
    int iV, iE, iS;
    int iu, iv, iw;
    NODE **root, *newNode, *curNode, *tmpNode;
    int *minArr;
    queue *priorityQ;
    int qLastIdx;
    int curIdx, curLen;
    
    scanf("%d %d", &iV, &iE);
    scanf("%d", &iS);
    iS--;

    // Make graph
    root = (NODE**)malloc(sizeof(NODE)*iV);
    for(i = 0; i < iV; i++) {
        root[i] = (NODE*)malloc(sizeof(NODE));
        root[i]->next = NULL;
    }
    for(i = 0; i < iE; i++){
        scanf("%d %d %d", &iu, &iv, &iw);
        newNode = (NODE*)malloc(sizeof(NODE));
        iu--; iv--;
        newNode->dst = iv;
        newNode->len = iw;
        newNode->next = root[iu]->next;
        root[iu]->next = newNode;
    }


    // Calc min
    minArr = (int*)malloc(sizeof(int)*iV);
    for(i = 0; i < iV; i++) minArr[i] = DIST_MAX;
    minArr[iS] = 0;
    priorityQ = (queue*)malloc(sizeof(queue)*iE);
    qLastIdx = 1;
    priorityQ[qLastIdx].idx = iS;
    priorityQ[qLastIdx].len = minArr[iS];


    while(deleteQueue(priorityQ, &qLastIdx)== 0){
        curIdx = priorityQ[0].idx;
        curLen = priorityQ[0].len;
        curNode = root[curIdx];

        if(curLen > minArr[curIdx]) continue;

        while(curNode->next){
            if(minArr[curNode->next->dst] > curLen + curNode->next->len) {
                minArr[curNode->next->dst] = curLen + curNode->next->len;
                insertQueue(priorityQ, &qLastIdx, curNode->next->dst, minArr[curNode->next->dst]);
            }
            curNode = curNode->next;
        }
    }

    for(i = 0; i < iV; i++) {
        if (minArr[i] == DIST_MAX) printf("INF\n");
        else printf("%d\n", minArr[i]);
    }

    return 0;
}