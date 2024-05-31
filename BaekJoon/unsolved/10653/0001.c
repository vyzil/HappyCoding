#include <stdio.h>
#include <stdlib.h>

#define DIST(A, B) (((A).x > (B).x ? (A).x - (B).x : (B).x - (A).x) + ((A).y > (B).y ? (A).y - (B).y : (B).y - (A).y))

typedef struct _NODE{
    int lIdx, rIdx;  
    int ldist, rdist;
    int x, y;
} NODE;

int main(void){
    int i;
    int N, K;
    int d, maxIdx, max;
    NODE *arr;

    scanf("%d %d", &N, &K);
    
    arr = (NODE*)malloc(sizeof(NODE)*N);
    for(i = 0; i < N; i++){
        scanf("%d %d", &arr[i].x, &arr[i].y);
        arr[i].lIdx = i-1;
        arr[i].rIdx = i+1;
        if(i > 0){
            d = DIST(arr[i-1], arr[i]);
            arr[i].ldist = d;
            arr[i-1].rdist = d;
        }
    }
    arr[0].ldist = -1;
    arr[N-1].rdist = -1;

    while(K--){
        maxIdx = -1;
        max = -1;
        for(i = arr[0].rIdx; i < N-1; i = arr[i].rIdx){
            d = arr[i].ldist + arr[i].rdist - DIST(arr[arr[i].lIdx], arr[arr[i].rIdx]);
            if(max < d){
                maxIdx = i;
                max = d;
            }
        }
        if(maxIdx < 0) continue;
        d = DIST(arr[arr[maxIdx].lIdx], arr[arr[maxIdx].rIdx]);
        arr[arr[maxIdx].lIdx].rIdx = arr[maxIdx].rIdx;
        arr[arr[maxIdx].lIdx].rdist = d;
        arr[arr[maxIdx].rIdx].lIdx = arr[maxIdx].lIdx;
        arr[arr[maxIdx].rIdx].ldist = d;
    }

    d = 0;
    for(i = arr[0].rIdx; i < N; i = arr[i].rIdx) d += arr[i].ldist;

    printf("%d\n", d);

    free(arr);

    return 0;
}