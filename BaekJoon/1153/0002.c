#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i, j;
    int n, tmp;
    int* arr;
    int output[4];

    scanf("%d", &n);

    arr = (int*)calloc(n+1, sizeof(int));

    // 1. Make Prime Array
    // re-use "arr" : first as Eratos
    for(i = 2; i < n+1; i++){
        if(arr[i] == 0) arr[i] = 1;
        for(j = 2*i; j < n+1; j += i){
            arr[j] = -1;
        }
    }

    // 2. Calculate Output
    // 골드바흐의 추측
    // 홀수 : 2 + 3 + (2보다 큰 짝수)  // 9 이상 홀수 
    // 짝수 : 2 + 2 + (2보다 큰 짝수)  // 8 이상 짝수
    if(n < 7) printf("-1");
    else{
        output[0] = 2;
        output[1] = n%2? 3 : 2;
        n -= (output[0] + output[1]);
        for(i = 2; i <n+1; i++){
            if(arr[i] == 1 && arr[n-i] == 1) break;
        }
        output[2] = i;
        output[3] = n - i;

        for(i = 0; i < 4; i++) printf("%d ", output[i]);
    }
    printf("\n");

    return 0;
}