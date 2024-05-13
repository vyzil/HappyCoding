#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i, j;
    int iN;
    int *iArr, *forwardDP, *reverseDP;
    int max;

    scanf("%d", &iN);
    iArr = (int*)malloc(sizeof(int)*iN);
    forwardDP = (int*)malloc(sizeof(int)*iN);
    reverseDP = (int*)malloc(sizeof(int)*iN);
    for(i = 0; i < iN; i++) scanf("%d", &iArr[i]);

    for(i = 0; i < iN; i++){
        max = 0;
        for(j = 0; j < i; j++){
            if(iArr[j] < iArr[i] && forwardDP[j] > max) max = forwardDP[j];            
        }
        forwardDP[i] = max + 1;
    }
    
    for(i = iN - 1; i >= 0; i--){
        max = 0;
        for(j = iN - 1; j > i; j--){
            if(iArr[j] < iArr[i] && reverseDP[j] > max) max = reverseDP[j];            
        }
        reverseDP[i] = max + 1;
    }

    max = 0;
    for(i = 0; i < iN; i++){
        if(max < forwardDP[i] + reverseDP[i]) max = forwardDP[i] + reverseDP[i];
    }
    max--;

    printf("%d\n", max);

    return 0;
}