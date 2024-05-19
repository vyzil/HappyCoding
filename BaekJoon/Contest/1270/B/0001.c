#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i, j;
    int N, M, turn, sum;
    int *arrA, swap;

    scanf("%d %d", &N, &M);
    arrA = (int*)malloc(sizeof(int)*N);
    for(i = 0; i < N; i++) scanf("%d", &arrA[i]);

    for(i = 0; i < N; i++){
        for(j = 0; j < N-i-1; j++){
            if(arrA[j] < arrA[j+1]){
                swap = arrA[j];
                arrA[j] = arrA[j+1];
                arrA[j+1] = swap;
            }
        }
    }

    turn = M-1;
    if(turn > (N-1)/2) turn = (N-1)/2;

    sum = 0;
    for(i = 0; i <= turn; i++) {
        if(arrA[i] < 0) break;
        sum += arrA[i];
    }

    printf("%d\n", sum);
    free(arrA);
    return 0;
}