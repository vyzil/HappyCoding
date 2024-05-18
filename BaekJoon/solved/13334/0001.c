#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE{
    int start;
    int end;
} NODE;

NODE *g_inputHeap; int g_inputSize;
int *g_procHeap; int g_procSize;

void InsertInput(int start, int end){
    int curIdx, parentIdx;    

    g_inputSize++;
    curIdx = g_inputSize;
    while(curIdx > 1){
        parentIdx = curIdx / 2;
        if(g_inputHeap[parentIdx].end < end) break;
        g_inputHeap[curIdx] = g_inputHeap[parentIdx];
        curIdx = parentIdx;
    }
    g_inputHeap[curIdx].start = start;
    g_inputHeap[curIdx].end = end;

    return;
}

void DeleteInput(){
    int curIdx, childIdx;
    int start, end;

    curIdx = 1;
    start = g_inputHeap[g_inputSize].start;
    end = g_inputHeap[g_inputSize].end;
    while(2*curIdx < g_inputSize){
        childIdx = 2*curIdx;
        if(childIdx + 1 < g_inputSize && g_inputHeap[childIdx].end > g_inputHeap[childIdx+1].end) childIdx++;
        if(g_inputHeap[childIdx].end > end) break;
        g_inputHeap[curIdx] = g_inputHeap[childIdx];
        curIdx = childIdx;
    }
    g_inputHeap[curIdx].start = start;
    g_inputHeap[curIdx].end = end;    
    g_inputSize--;

    return;
}

void InsertProc(int num){
    int curIdx, parentIdx;

    g_procSize++;
    curIdx = g_procSize;
    while(curIdx > 1){
        parentIdx = curIdx / 2;
        if(g_procHeap[parentIdx] < num) break;
        g_procHeap[curIdx] = g_procHeap[parentIdx];
        curIdx = parentIdx;
    }
    g_procHeap[curIdx] = num;

    return;
}

void DeleteProc(){
    int curIdx, childIdx;
    int num;

    curIdx = 1;
    num = g_procHeap[g_procSize];
    while(2*curIdx < g_procSize){
        childIdx = 2*curIdx;
        if(childIdx + 1 < g_procSize && g_procHeap[childIdx]> g_procHeap[childIdx+1]) childIdx++;
        if(g_procHeap[childIdx] > num) break;
        g_procHeap[curIdx] = g_procHeap[childIdx];
        curIdx = childIdx;
    }
    g_procHeap[curIdx] = num;
    g_procSize--;

    return;
}

int main(void){
    int i;
    int N, h, o, d;
    int small, large;
    int start, end, max;
    NODE curNode;

    scanf("%d", &N);

    g_inputHeap = (NODE*)malloc(sizeof(NODE)*(N+1));
    g_inputSize = 0;
    for(i = 0; i < N; i++){
        scanf("%d %d", &h, &o);
        small = (h < o ? h : o);
        large = (h > o ? h : o);
        InsertInput(small, large);        
    }

    scanf("%d", &d);

    g_procHeap = (int*)malloc(sizeof(int)*(N+1));
    g_procSize = 0;

    max = 0;
    while(g_inputSize){
        curNode = g_inputHeap[1];
        DeleteInput();
        if(curNode.end - curNode.start > d) continue;

        end = curNode.end;
        start = end - d;
        InsertProc(curNode.start);        
        while(g_procSize > 0 && g_procHeap[1] < start) DeleteProc();
        if(max < g_procSize) max = g_procSize;
    }

    printf("%d\n", max);
    

    free(g_inputHeap);
    free(g_procHeap);
    
    return 0;
}