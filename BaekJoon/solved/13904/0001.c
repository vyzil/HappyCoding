#include <stdio.h>
#include <stdlib.h>

typedef struct _ASSIGNMENT{
    int d;
    int w;
} ASSIGN;

int main(void){
    int i;
    int N;
    ASSIGN *arr, curMax;
    int dayMax, maxIdx;
    int pointSum;

    scanf("%d", &N);
    arr = (ASSIGN*)malloc(sizeof(ASSIGN)*N);
    dayMax = 0;
    for(i = 0; i < N; i++) {
        scanf("%d %d", &arr[i].d, &arr[i].w);
        if(dayMax < arr[i].d) dayMax = arr[i].d;
    }

    pointSum = 0;
    while(dayMax){
        curMax.d = 0;
        curMax.w = 0;
        maxIdx = -1;
        for(i = 0; i < N; i++){
            if(arr[i].d >= dayMax && curMax.w < arr[i].w){
                curMax.d = arr[i].d;
                curMax.w = arr[i].w;
                maxIdx = i;
            }            
        }
        // printf("Day-%d : do %d(%d)\n", dayMax, maxIdx, arr[maxIdx].w);
        if(maxIdx >= 0){
            pointSum += arr[maxIdx].w;
            arr[maxIdx].d = 0;
            arr[maxIdx].w = 0;
        }
        dayMax--;
    }

    printf("%d\n", pointSum);

    return 0;
}