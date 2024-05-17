#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b)   ((a) < (b)? (a) : (b))
#define MAX(a, b)   ((a) > (b)? (a) : (b))

#define N_MIN 0
#define N_MAX 1000000001

typedef struct _NODE{
    int min;
    int max;
} NODE;

NODE *g_segTree;
int g_treeSize;

NODE makeTree(int idx, int start, int end){
    int in;
    NODE left, right;

    if(start == end) {
        scanf("%d", &in);
        g_segTree[idx].min = in;
        g_segTree[idx].max = in;
    }
    else {
        left = makeTree(2*idx, start, (start + end)/2);
        right = makeTree(2*idx+1, (start + end)/2 + 1, end);
        g_segTree[idx].min = MIN(left.min, right.min);
        g_segTree[idx].max = MAX(left.max, right.max);
    }

    return g_segTree[idx];
}

NODE searchRange(int idx, int start, int end,  int s, int e){
    NODE res, tmp;
    if(s <= start && end <= e) return g_segTree[idx];

    res.min = N_MAX;
    res.max = N_MIN;
    if((s <= (start + end)/2) && start <= e) {
        tmp = searchRange(2*idx, start, (start + end)/2, s, e);   
        res.min = MIN(tmp.min, res.min);
        res.max = MAX(tmp.max, res.max);     
    }
    if((s <= end) && ((start + end)/2 + 1) <= e){
        tmp = searchRange(2*idx+1, (start + end)/2 + 1, end, s, e);
        res.min = MIN(tmp.min, res.min);
        res.max = MAX(tmp.max, res.max);
    }

    return res;
}

int main(void) {
    int N, M;
    int a, b;
    NODE tmp;

    scanf("%d %d", &N, &M);

    for(g_treeSize = 1; g_treeSize < N; g_treeSize <<= 1);
    g_treeSize <<= 1;
    g_segTree = (NODE*)malloc(sizeof(NODE)*g_treeSize);

    makeTree(1, 0, N-1);
    // for(int i = 0; i < g_treeSize; i++) printf("(%d, %d)\n", g_segTree[i].min, g_segTree[i].max);  

    while(M--){
        scanf("%d %d", &a, &b);
        tmp = searchRange(1, 0, N-1, a-1, b-1);
        printf("%d %d\n", tmp.min, tmp.max);
    }

    free(g_segTree);

    return 0;
}