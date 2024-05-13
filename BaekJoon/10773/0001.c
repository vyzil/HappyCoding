#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i, idx;
    int K, *arr, sum;

    scanf("%d", &K);

    arr = (int*)malloc(sizeof(int)*K);    
    for(i = 0, idx = 0; i < K; i++){
        scanf("%d", &arr[idx]);
        if(arr[idx++] == 0) idx -= 2;
    }
    for(i = 0, sum = 0; i < idx; i++) sum += arr[i];
    
    printf("%d\n", sum);

    return 0;
}