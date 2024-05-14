#include <stdio.h>
#include <stdlib.h>

#define ll long long

ll *inputArr, *accumArr;
ll *segTree; int treeSize;

void makeTree(int idx, int start, int end){
    // printf("%d, %d, %d (%d)\n", idx, start, end, treeSize);
    segTree[idx] = accumArr[end] - (start -1 < 0 ? 0 : accumArr[start-1]);
    if(start == end) return;
    makeTree(2*idx , start, (start + end)/2);
    makeTree(2*idx+1, (start + end)/2 + 1, end);
    return;
}

void updateTree(int idx, int start, int end, int num, ll addNum){
    // printf("%d, %d, %d (%d)\n", idx, start, end, addNum);
    if(start > end) return;
    segTree[idx] += addNum;
    if(start == end) return;
    if(start <= num && num <= (start + end)/2) updateTree(2*idx, start, (start + end)/2, num, addNum);
    else updateTree(2*idx+1, (start + end)/2 + 1, end, num, addNum);

    return;
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
    inputArr = (ll*)malloc(sizeof(ll)*N);
    accumArr = (ll*)malloc(sizeof(ll)*N);
    for(i = 0; i < N ;i++){
        scanf("%lld", &inputArr[i]);
        if(i == 0) accumArr[i] = inputArr[i];
        else accumArr[i] = accumArr[i-1] + inputArr[i];
    }

    for(treeSize = 1; treeSize < N; treeSize <<= 1);
    treeSize <<= 1;
    segTree = (ll*)malloc(sizeof(ll)*treeSize);

    makeTree(1, 0, N-1);

    for(i = 0; i < M + K; i++){
        scanf("%d %d %lld", &a, &b, &c);
        if(a == 1){ // update
            updateTree(1, 0, N-1, b-1, c - inputArr[b-1]);
            inputArr[b-1] = c;
        } 
        else { // a == 2, print
            printf("%lld\n", printRange(1, 0, N-1, b-1, c-1));
        }
    }

    free(inputArr);
    free(accumArr);
    free(segTree);

    return 0;
}