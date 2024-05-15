#include <stdio.h>
#include <stdlib.h>

#define MAX_H 1000000001

int *g_input;
int *g_segTree, g_treeSize;
int g_min, g_minIdx;
int N;

int makeTree(int idx, int start, int end){
    int lChild, rChild;
    if(start == end) g_segTree[idx] = start;
    else {
        lChild = makeTree(2*idx, start, (start + end)/2);
        rChild = makeTree(2*idx+1, (start + end)/2 + 1, end);
        if(g_input[lChild] > g_input[rChild]) g_segTree[idx] = rChild;
        else g_segTree[idx] = lChild;
    }
    return g_segTree[idx];
}

int minRange(int idx, int start, int end, int s, int e){
    int curMin, lChild, rChild;
    if(end < s || e < start) curMin = N;
    else if (s <= start && end <= e) curMin = g_segTree[idx];
    else {
        lChild = minRange(2*idx, start, (start + end)/2, s, e);
        rChild = minRange(2*idx+1, (start + end)/2 + 1, end, s, e);
        if(g_input[lChild] > g_input[rChild]) curMin = rChild;
        else curMin = lChild;
    }
    return curMin;
}

int divNcon(int start, int end){
    int mid, curMax, lMax, rMax;
    mid = minRange(1, 0, N-1, start, end);
    curMax = g_input[mid] * (end-start+1);
    
    if(start <= mid-1) {
        lMax = divNcon(start, mid - 1);
        if(curMax < lMax) curMax = lMax;
    }
    
    if(mid+1 <= end){
        rMax = divNcon(mid+1, end);
        if(curMax < rMax) curMax = rMax;
    }
    return curMax;
}

int main(void){
    int i;  
    scanf("%d", &N);
    g_input = (int*)malloc(sizeof(int)*(N+1));
    for(i = 0; i < N; i++) scanf("%d", &g_input[i]);
    g_input[N] = MAX_H;

    for(g_treeSize=1; g_treeSize < N; g_treeSize <<= 1);
    g_treeSize <<= 1;
    g_segTree = (int*)malloc(sizeof(int)*g_treeSize);

    makeTree(1, 0, N-1);
    g_min = MAX_H;
    g_minIdx = 0;
    printf("%d\n", divNcon(0, N-1));

    free(g_segTree);
    free(g_input);

    return 0;
}