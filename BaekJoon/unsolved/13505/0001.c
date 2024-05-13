#include <stdio.h>

int main(void){
    int i;
    int n;
    int* arr;

    scanf("%d", &n);
    arr = (int*)malloc(sizeof(int)*n);
    for(i = 0; i < n; i++) scanf("%d", &arr[i]);

    // 1. max1과 같은 bit의 최댓값 구하기
    // 2. 그 값을 max1에서 빼기

    

    return 0;
}