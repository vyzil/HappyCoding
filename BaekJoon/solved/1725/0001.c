#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define min(a, b) ((a) > (b) ? (b) : (a));
#define max(a, b) ((a) > (b) ? (a) : (b));

int *segTree, g_treeSize;

int makeTree(int idx, int start, int end){
    int lChild, rChild;
    if(start == end) scanf("%d", &segTree[idx]);
    else {
        lChild = makeTree(2*idx, start, (start + end)/2);
        rChild = makeTree(2*idx+1, (start + end)/2 + 1, end);
        segTree[idx] = min(lChild, rChild);
    }
    return segTree[idx];
}

ll maxRec(int idx, int start, int end){
    ll childMax, lChild, rChild;
    if(start == end) childMax = 0;
    else {
        lChild = maxRec(2*idx, start, (start + end)/2);
        rChild = maxRec(2*idx+1, (start + end)/2 + 1, end);
        childMax = max(lChild, rChild);
    }
    return max((ll)segTree[idx]*(ll)(end-start+1), childMax);
}

int main(void){
    int N;    
    scanf("%d", &N);

    for(g_treeSize=1; g_treeSize < N; g_treeSize <<= 1);
    g_treeSize <<= 1;
    segTree = (int*)malloc(sizeof(int)*g_treeSize);

    makeTree(1, 0, N-1);
    printf("%lld\n", maxRec(1, 0, N-1));

    free(segTree);

    return 0;
}