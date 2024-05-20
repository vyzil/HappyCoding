#include <stdio.h>
#include <stdlib.h>

int *negHeap, negSize;
int *posHeap, posSize;
int zero, one;

void insertPos(int num){
    int curIdx, parentIdx;

    posSize++;
    curIdx = posSize;
    while(curIdx > 1){
        parentIdx = curIdx / 2;
        if(posHeap[parentIdx] > num) break;
        posHeap[curIdx] = posHeap[parentIdx];
        curIdx = parentIdx;
    }
    posHeap[curIdx] = num;
    return;
}

void popPos(){
    int num, curIdx, childIdx;

    num = posHeap[posSize];
    curIdx = 1;
    while(2*curIdx < posSize){
        childIdx = 2*curIdx;
        if(childIdx+1 < posSize && posHeap[childIdx] < posHeap[childIdx+1]) childIdx++;
        if(posHeap[childIdx] < num) break;  
        posHeap[curIdx] = posHeap[childIdx];
        curIdx = childIdx;
    }
    posHeap[curIdx] = num;
    posSize--;
    return;
}

void insertNeg(int num){
    int curIdx, parentIdx;

    negSize++;
    curIdx = negSize;
    while(curIdx > 1){
        parentIdx = curIdx / 2;
        if(negHeap[parentIdx] < num) break;
        negHeap[curIdx] = negHeap[parentIdx];
        curIdx = parentIdx;
    }
    negHeap[curIdx] = num;
    return;

}

void popNeg(){
    int num, curIdx, childIdx;

    num = negHeap[negSize];
    curIdx = 1;
    while(2*curIdx < negSize){
        childIdx = 2*curIdx;
        if(childIdx+1 < negSize && negHeap[childIdx] > negHeap[childIdx+1]) childIdx++;
        if(negHeap[childIdx] > num) break;  
        negHeap[curIdx] = negHeap[childIdx];
        curIdx = childIdx;
    }
    negHeap[curIdx] = num;
    negSize--;
    return;
}

int main(void){
    int i;
    int N, num, sum;

    scanf("%d", &N);

    negHeap = (int*)malloc(sizeof(int)*(N+1));
    posHeap = (int*)malloc(sizeof(int)*(N+1));
    negSize = 0; posSize = 0;
    zero = 0;
    one = 0;
    for(i = 0 ; i < N; i++) {
        scanf("%d", &num);
        if(num == 1) one++;
        else if (num == 0) zero++;
        else if(num > 0) insertPos(num);
        else if(num < 0) insertNeg(num);
    }

    sum = one;
    // popPos
    while(posSize > 1){
         num = posHeap[1];
         popPos();
         num *= posHeap[1];
         popPos();
         sum += num;
    }
    if(posSize == 1) sum += posHeap[1];

    // popNeg
    while(negSize > 1){
         num = negHeap[1];
         popNeg();
         num *= negHeap[1];
         popNeg();
         sum += num;
    }
    if(negSize == 1 && zero == 0) sum += negHeap[1];

    printf("%d\n", sum);

    free(negHeap);
    free(posHeap);    

    return 0;
}