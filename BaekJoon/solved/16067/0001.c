#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b){
    int _a = *(int*)a;
    int _b = *(int*)b;
    if(_a > _b) return 1;
    if(_a < _b) return -1;
    return 0;
}

int main(void){
    int i;
    int N;
    int* arr, *saved;
    int fibA, fibB, tmp, idx, prev;
    int res1, res2;

    scanf("%d", &N);
    arr = (int*)malloc(sizeof(int)*N);
    saved = (int*)malloc(sizeof(int)*N);

    for(i = 0; i < N; i++) scanf("%d", &arr[i]);
    memcpy(saved, arr, sizeof(int)*N);
    qsort(arr, N, sizeof(int), cmp);

    res2 = -1;
    prev = 0;
    idx = 0;
    fibA = 1; fibB = 1;
    while(idx < N){
        while(idx < N && arr[idx] < fibA) idx++;
        if(arr[idx] == fibA) {
            idx++;
            while(idx < N && arr[idx] < fibB) idx++;
            if(arr[idx] == fibB) break;
        }
        
        while(fibA < arr[idx]) {
            tmp = fibB;
            fibB += fibA;
            fibA = tmp;
        }
    }

    if(idx >= N) {
        printf("impossible\n");
        goto finale;
    }

    res1 = -1; res2 = -1;
    for(i = 0; i < N; i++){
        if(0 < res1 && 0 < res2) break;
        if(res1 < 0 && saved[i] == fibA) res1 = i+1;
        else if(res2 < 0 && saved[i] == fibB) res2 = i+1;
    }

    printf("%d %d\n", res1, res2);

finale:
    free(arr);
    free(saved);

}