#include <stdio.h>
#include <stdlib.h>

#define N_MAX 201

int main(void){
    int i, j, k;
    int iN, iK, iNum;
    int min, cost;
    int *arr, arrSize;
    int **DP;

    scanf("%d %d", &iN, &iK);
    arr = (int*)malloc(sizeof(int)*iN);
    arrSize = 0;
    for(i = 0; i < iN; i++) {
        scanf("%d", &iNum);
        if(arrSize == 0) arr[arrSize++] = iNum;
        if(iNum != arr[arrSize-1]) arr[arrSize++] = iNum;
    }

    DP = (int**)malloc(sizeof(int*)*(arrSize+1));    
    for(i = 0; i < arrSize+1; i++) DP[i] = (int*)malloc(sizeof(int)*arrSize);
    for(i = 0; i < arrSize; i++) DP[1][i] = 0;

    for(i = 2; i <= arrSize; i++){
        for(j = 0; j <= arrSize - i; j++){
            min = N_MAX;  
            for(k = 1; k < i; k++){
                cost = DP[k][j] + DP[i - k][j + k];
                if(arr[j] != arr[j + k] && arr[j] != arr[j + i - 1] && arr[j + k - 1] != arr[j + k] && arr[j + k - 1] != arr[j + i - 1]) cost++;
                if(cost < min) min = cost;
            }
            DP[i][j] = min;
        } 
    }

    printf("%d\n", DP[arrSize][0]);

    for(i = 0; i < arrSize+1; i++) free(DP[i]);
    free(DP);
    free(arr);
    return 0;
}