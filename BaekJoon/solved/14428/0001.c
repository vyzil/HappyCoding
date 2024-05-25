#include <stdio.h>
#include <stdlib.h>

#define A_MAX 1000000001

int *g_segTree, g_treeSize;
int *input, g_inputSize;

int makeTree(int tIdx, int start, int end){
    int leftIdx, rightIdx, minIdx;
    if(start == end) minIdx = start;
    else {
        leftIdx = makeTree(2*tIdx, start, (start+end)/2);
        rightIdx = makeTree(2*tIdx+1, (start+end)/2 + 1, end);
        minIdx = (input[leftIdx] <= input[rightIdx] ? leftIdx : rightIdx);
    }

    return g_segTree[tIdx] = minIdx;
}

int updateTree(int tIdx, int start, int end, int idx, int num){
    int minIdx, leftIdx, rightIdx;

    if(start == end) {
        input[idx] = num;
        minIdx = start;
    }
    else {
        leftIdx = g_segTree[2*tIdx];
        rightIdx = g_segTree[2*tIdx+1];
        if(start <= idx && idx <= (start+end)/2) leftIdx = updateTree(2*tIdx, start, (start+end)/2, idx, num);
        else rightIdx = updateTree(2*tIdx+1, (start+end)/2 + 1 ,end, idx, num);

        minIdx = (input[leftIdx] <= input[rightIdx] ? leftIdx : rightIdx);
    }

    return g_segTree[tIdx] = minIdx;
}

int queryTree(int tIdx, int start, int end, int s, int e){
    int leftIdx, rightIdx, minIdx;    

    if(end < s || e < start) return g_inputSize;
    if(s <= start && end <= e) return g_segTree[tIdx];

    leftIdx = g_inputSize; rightIdx = g_inputSize;
    if(start <= e && s <= (start + end)/2) leftIdx = queryTree(2*tIdx, start, (start + end)/2, s, e);
    if((start + end)/2+1 <= e && s <= end) rightIdx = queryTree(2*tIdx+1, (start + end)/2 + 1, end, s, e);

    minIdx = (input[leftIdx] <= input[rightIdx] ? leftIdx : rightIdx);

    return minIdx;
}


int main(void){
    int i;
    int N, M;
    int a, b, c;
   
    scanf("%d", &N);
    input = (int*)malloc(sizeof(int)*(N+1));
    for(i = 0; i < N; i++) scanf("%d", &input[i]);
    input[N] = A_MAX;
    g_inputSize = N;

    for(g_treeSize = 1; g_treeSize < N; g_treeSize <<= 1);
    g_treeSize <<= 1;
    g_segTree = (int*)malloc(sizeof(int)*g_treeSize);

    makeTree(1, 0, N-1);

    scanf("%d", &M);
    while(M--){
        scanf("%d %d %d", &a, &b, &c);
        if(a == 1) updateTree(1, 0, N-1, b-1, c);
        else printf("%d\n", queryTree(1, 0, N-1, b-1, c-1) + 1);
    }

    return 0;
}