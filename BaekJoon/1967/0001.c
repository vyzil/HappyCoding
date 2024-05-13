#include <stdio.h>
#include <stdlib.h>

typedef struct NODE{
    int index;
    int lValue;
    int rValue;
    int parentIdx;
    int lChildIdx;
    int rChildIdx;
} NODE;

int main(void){
    int i;
    int iN, iS, iE, iV;
    int prevS;
    NODE *iTree, *curNode;
    int *pMax; // pMax[idx] = longest path passing idx (idx as root)
    int *nMax; // nMax[idx] = longest path until idx (idx as root)
    int *done;
    int lMax, rMax, max;

    scanf("%d", &iN);

    iTree = (NODE*)malloc(sizeof(NODE)*iN);
    for(i = 0; i < iN; i++){
        iTree[i].index = i;
        iTree[i].lValue = 0;
        iTree[i].rValue = 0;
        iTree[i].parentIdx = -1;
        iTree[i].lChildIdx = -1;
        iTree[i].rChildIdx = -1;
    }

    prevS = -1;
    for(i = 0; i < iN-1; i++){
        scanf("%d %d %d", &iS, &iE, &iV);
        iS--; iE--;
        iTree[iE].parentIdx = iS;
        if(prevS == iS) {
            iTree[iS].rValue = iV;
            iTree[iS].rChildIdx = iE;
        }
        else {
            iTree[iS].lValue = iV;
            iTree[iS].lChildIdx = iE;
            prevS = iS;
        }
    }

    pMax = (int*)malloc(sizeof(int)*iN);
    nMax = (int*)calloc(iN, sizeof(int));
    done = (int*)calloc(iN, sizeof(int));
    curNode = iTree;
    while(1){
        if(curNode->lChildIdx != -1 && done[curNode->lChildIdx] == 0){
            curNode = iTree + curNode->lChildIdx;
            continue;
        }
        if(curNode->rChildIdx != -1 && done[curNode->rChildIdx] == 0){
            curNode = iTree + curNode->rChildIdx;
            continue;
        }
        lMax = 0;
        rMax = 0;
        if(curNode->lChildIdx != -1) lMax = nMax[curNode->lChildIdx] + curNode->lValue;
        if(curNode->rChildIdx != -1) rMax = nMax[curNode->rChildIdx] + curNode->rValue;
        pMax[curNode->index] = lMax + rMax;
        nMax[curNode->index] = lMax > rMax ? lMax : rMax;

        done[curNode->index] = 1;
        if(curNode->parentIdx == -1) break;
        curNode = iTree + curNode->parentIdx;        
    }

    max = 0;
    for(i = 0; i < iN; i++){
        if(pMax[i] > max) max = pMax[i];
    }
    printf("%d\n", max);

    return 0;
}