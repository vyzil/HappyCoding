#include <stdio.h>

#define MAX_LEN 1000
#define MAX_NUM 1000000000

int main(void) {
    int i;
    int P, K, N;
    int arr[MAX_LEN]; 
    int ascIdx, min, minIdx, count;

    scanf("%d", &P);
    while(P--){
        scanf("%d %d", &K, &N);
        for(i = 0; i < N; i++) scanf("%d", &arr[i]);

        ascIdx = -1;
        count = 0;
        while(1){
            min = MAX_NUM;
            for(i = 0; i < N; i++){
                if(min > arr[i]) {
                    min = arr[i];
                    minIdx = i;
                }
            }
            if(ascIdx > minIdx || min == MAX_NUM) break;
            ascIdx = minIdx;
            count++;
            arr[minIdx] = MAX_NUM;
        }
        for(i = ascIdx+1; i < N; i++){
            if(arr[i] == min) count++;
        }

        printf("%d %d\n", K, N - count);        
    }


    return 0;
}