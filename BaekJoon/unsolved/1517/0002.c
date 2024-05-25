#include <stdio.h>
#include <stdlib.h>

#define ll long long

#define MIN(a, b) ((a) > (b) ? (a) : (b));
#define MAX(a, b) ((a) < (b) ? (a) : (b));

typedef struct _NODE{
    int max;
    int min;
} NODE;



NODE makeTree(NODE *tree, int *input, int idx, int start, int end){    
    NODE lchild, rchild;
    if(start == end) {
        tree[idx].min = input[start];
        tree[idx].max = input[start];
        return tree[idx];
    }

    lchild = makeTree(tree, input, 2*idx, start, (start+end)/2);
    rchild = makeTree(tree, input, 2*idx+1, (start+end)/2+1, end);

    tree[idx].max = MAX(lchild.max, rchild.max);
    tree[idx].min = MIN(lchild.min, rchild.min);

    return tree[idx];
}

int searchTree(NODE* tree, int idx, int start, int end, int s, int num){
    if(end < s) return 0;
    if(start < s) return searchTree(tree, 2*idx, start, (start+end)/2, s, num) + searchTree(tree, 2*idx+1, (start+end)/2+1, end, s, num);

    if(tree[idx].max < num) return end - start + 1;
    if(tree[idx].min >= num) return 0;
    return searchTree(tree, 2*idx, start, (start+end)/2, s, num) + searchTree(tree, 2*idx+1, (start+end)/2+1, end, s, num);
}

int main(void){
    int i;
    int N;
    int *input;
    ll res;
    NODE* segTree; int treeSize;

    scanf("%d", &N);
    input = (int*)malloc(sizeof(int)*N);
    for(i = 0; i < N; i++) scanf("%d", &input[i]);
    for(treeSize = 1; treeSize < N; treeSize <<= 1);
    treeSize <<= 1;
    segTree = (NODE*)malloc(sizeof(NODE)*treeSize);

    makeTree(segTree, input, 1, 0, N-1);
    
    res = 0;
    for(i = 0; i < N-1; i++) res += (ll)searchTree(segTree, 1, 0, N-1, i+1, input[i]);
    printf("%lld\n", res);

    free(input);
    free(segTree);
    return 0;
}