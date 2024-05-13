#include <stdio.h>
#include <stdlib.h>

#define HEAP_MAX 50+100000
#define N_MAX 50


double gHeap[HEAP_MAX];
int gHeapSize;

void insertHeap(double num){
    int curIdx, parentIdx;
    gHeapSize++;
    curIdx = gHeapSize;
    while(curIdx > 1){
        parentIdx = curIdx / 2;
        if(gHeap[parentIdx] >= num) break;
        gHeap[curIdx] = gHeap[parentIdx];
        curIdx = parentIdx;
    }
    gHeap[curIdx] = num;

    return;
}

// no return logic for no element
double deleteHeap(){
    double res;
    double num;
    int curIdx, childIdx;

    res = gHeap[1];
    num = gHeap[gHeapSize];
    gHeapSize--;
    curIdx = 1;
    while(2*curIdx <= gHeapSize){
        childIdx = 2*curIdx;
        if(childIdx + 1 <= gHeapSize && gHeap[childIdx] < gHeap[childIdx+1]) childIdx++;
        if(num >= gHeap[childIdx]) break;
        gHeap[curIdx] = gHeap[childIdx];
        curIdx = childIdx;        
    }
    gHeap[curIdx] = num;

    return res;
}

int main(void){
    int i;
    int iN, iM;
    double iW;
    double min, max;
    double *res;

    min = N_MAX;
    max = 0;
    scanf("%d", &iN);

    gHeapSize = 0;
    for(i = 0 ; i < iN; i++){
        scanf("%lf", &iW);
        insertHeap(iW);
        if(min > iW) min = iW;
        if(max < iW) max = iW;
    }

    scanf("%d", &iM);

    res = (double*)malloc(sizeof(double)*(iM+1));
    for(i = 0; i <= iM; i++) {
        max = deleteHeap();
        res[i] = max - min;
        max /= 2;
        insertHeap(max);
        insertHeap(max);
        if(min > max) min = max;
    }

    min = N_MAX;
    for(i = 0; i <= iM; i++) {
        if(res[i] < min) min = res[i];
        printf("%lf ", res[i]);
    }
    printf("\n%.9lf\n", min);

    free(res);

    return 0;
}