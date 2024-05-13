#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int i;
    int N, top, col, valid, count;
    int* arr;

    scanf("%d", &N);
    arr = (int*)malloc(sizeof(int)*N);
    for(i = 0; i < N; i++) arr[i] = -1;

    top = 0;
    count = 0;
    while(top >= 0){
        col = ++arr[top];
        if(col >= N){
            arr[top--] = -1;
            continue;
        }
        valid = 1;
        for(i = 0; i < top; i++){ 
            if(arr[i] == col || arr[i] - i == col - top || arr[i] + i == col + top) {
                valid = 0;
                break;
            }
        }
        if(valid == 0) continue;
        top++;
        if(top == N){
            top--;
            count++;
        } 
    }

    printf("%d\n", count);

    return 0;
}