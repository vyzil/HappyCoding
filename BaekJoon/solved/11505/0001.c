#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define MOD 1000000007

int *g_segTree, g_treeSize, g_inv;

int inv(int num){
    int i;
    ll res, sqr;

    i = MOD - 2;
    res = 1;
    sqr = num;
    while(i){
        if(i & 1) res = (res * sqr) % MOD;
        sqr = (sqr * sqr) % MOD;
        i >>= 1;
    }
    return (int)res;
}

int makeTree(int idx, int start, int end){
    if(start == end) scanf("%d", &g_segTree[idx]);
    else g_segTree[idx] = (int)(((ll)makeTree(2*idx, start, (start + end)/2) * (ll)makeTree(2*idx+1, (start + end)/2 + 1, end)) % MOD);
    return g_segTree[idx];
}

int update(int idx, int start, int end, int changeIdx, int changeNum){
    int changeInv = 1;
    if(start == end) {
        changeInv = inv(g_segTree[idx]);
        g_segTree[idx] = changeNum;
        return changeInv;
    }
    if(start <= changeIdx && changeIdx <= (start + end)/2) changeInv = update(2*idx, start, (start + end)/2, changeIdx, changeNum);
    else if((start + end)/2 + 1 <= changeIdx && changeIdx <= end) changeInv = update(2*idx+1, (start + end)/2 + 1, end, changeIdx, changeNum);    
    else exit(-1);  // never
    g_segTree[idx] = (int)(((((ll)g_segTree[idx] * (ll)changeInv) % MOD) * (ll)changeNum) % MOD);
    return changeInv;
}

int calcRange(int idx, int start, int end, int s, int e){
    if(e < start || end < s) return 1;
    if(s <= start && end <= e) return g_segTree[idx];
    return (int)(((ll)calcRange(2*idx, start, (start + end)/2, s, e) * (ll)calcRange(2*idx+1, (start + end)/2 + 1, end, s, e)) % MOD);
}

int main(void){
    int i;
    int N, M, K;
    int a, b, c;

    scanf("%d %d %d", &N, &M, &K);
    for(g_treeSize = 1; g_treeSize < N; g_treeSize <<= 1);
    g_treeSize <<= 1;
    g_segTree = (int*)malloc(sizeof(int)*g_treeSize);

    makeTree(1, 0, N-1);

    for(i = 0; i < M+K; i++){
        scanf("%d %d %d", &a, &b, &c);
        if(a == 1) update(1, 0, N-1, b-1, c);
        else printf("%d\n", calcRange(1, 0, N-1, b-1, c-1));
    }

    free(g_segTree);

    return 0;
}