#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i, idx;
    int K, *arr, sum;

    scanf("%d", &K);

    arr = (int*)malloc(sizeof(int)*K);    
    for(i = 0, idx = 0, sum = 0; i < K; i++){
        scanf("%d", &arr[idx]);
        if(arr[idx] == 0){
            sum -= arr[idx-1];
            idx --;
            continue;
        }
        sum += arr[idx++];
    }
    
    printf("%d\n", sum);

    return 0;
}