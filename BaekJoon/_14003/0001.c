#include <stdio.h>
#include <stdlib.h>

typedef struct DPNODE{
    int size;
    int prevIdx;
} dpNode, *dpPTR;

int main(void){
    int i, j;
    int N, size, idx, maxSize, maxIndex, top;
    int *arr, *buffer;
    dpPTR DP;

    scanf("%d", &N);
    arr = (int*)malloc(sizeof(int)*N);
    buffer = (int*)malloc(sizeof(int)*N);
    for(i = 0; i < N; i++) scanf("%d", &arr[i]);
    
    DP = (dpPTR)malloc(sizeof(dpNode)*N);
    maxSize = 1;
    maxIndex = 0;
    for(i = 0; i < N; i++){
        size = 1;
        idx = -1;
        for(j = 0; j < i; j++){     // This for loop should be optimize
            if(arr[i] > arr[j] && DP[j].size >= size) {
                size = DP[j].size + 1;
                idx = j;
            }
        }
        DP[i].size = size;
        DP[i].prevIdx  = idx;

        if(size > maxSize) {
            maxSize = size;
            maxIndex = i;
        }
    }

    top = 0;
    idx = maxIndex;
    while(idx != -1){
        buffer[top++] = idx;
        idx = DP[idx].prevIdx;
    }

    printf("%d\n", DP[maxIndex].size);
    for(i = top-1; i >= 0; i--) printf("%d ", arr[buffer[i]]);
    printf("\n");
    

    return 0;
}