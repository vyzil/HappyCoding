#include <stdio.h>
#include <stdlib.h>

#define ll long long

ll *segTree; int treeSize;

ll makeTree(int idx, int start, int end){
    if(start == end) scanf("%lld", &segTree[idx]);
    else segTree[idx] = makeTree(2*idx , start, (start + end)/2) + makeTree(2*idx+1, (start + end)/2 + 1, end);
    return segTree[idx];
}

ll updateTree(int idx, int start, int end, int num, ll modifyNum){
    ll change;
    change = 0;
    if(start == end) change = modifyNum - segTree[idx];
    else if(start <= num && num <= (start + end)/2) change = updateTree(2*idx, start, (start + end)/2, num, modifyNum);
    else change = updateTree(2*idx+1, (start + end)/2 + 1, end, num, modifyNum);
    segTree[idx] += change;

    return change;
}

ll printRange(int idx, int start, int end, int s, int e){
    if(end < s || e < start) return 0;
    if(s <= start && end <= e) return segTree[idx];
    return printRange(2*idx, start, (start+end)/2, s, e) + printRange(2*idx+1, (start+end)/2 + 1, end, s, e);
}

int main(void) {
    int i;
    int N, M, K;
    int a, b; ll c;

    scanf("%d %d %d", &N, &M, &K);

    for(treeSize = 1; treeSize < N; treeSize <<= 1);
    treeSize <<= 1;
    segTree = (ll*)malloc(sizeof(ll)*treeSize);

    makeTree(1, 0, N-1);

    for(i = 0; i < M + K; i++){
        scanf("%d %d %lld", &a, &b, &c);
        if(a == 1){ // update
            updateTree(1, 0, N-1, b-1, c);
        } 
        else { // a == 2, print
            printf("%lld\n", printRange(1, 0, N-1, b-1, c-1));
        }
    }

    free(segTree);

    return 0;
}