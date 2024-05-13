#include <stdio.h>
#include <stdlib.h>

typedef struct DPNODE{
    int size;
    int prevIdx;
} dpNode, *dpPTR;

int main(void){
    int i, j;
    int N, size, cur;
    int *arr;
    int *LIS, lisSize, top, mid, bot;
    int *rec;
    dpPTR DP;

    scanf("%d", &N);
    arr = (int*)malloc(sizeof(int)*N);
    LIS = (int*)malloc(sizeof(int)*N);
    rec = (int*)malloc(sizeof(int)*N);

    lisSize = 0;
    for(i = 0; i < N; i++) {
        scanf("%d", &cur);
        arr[i] = cur;

        top = lisSize;
        bot = 0;

        while(1){
            mid = (top + bot) / 2;            
            if(top - bot < 1) {
                mid = top;
                break;
            }
            if(arr[mid] < cur) bot = mid;       // when change, bot is always less than mid
            else if (arr[mid] > cur) top = mid; // when change, top is always bigger than mid
            else break;                         // arr[mid] == cur 
        }
        rec[i] = mid;
        LIS[mid] = cur;
        if(mid == lisSize) lisSize++;
        printf("LIS\t:");
        for(j = 0; j <= i; j++) printf(" %d", LIS[i]);
        printf("\nrec\t:");
        for(j = 0; j <= i; j++) printf(" %d", rec[i]);
        printf("\n");

    }

    


    return 0;
}