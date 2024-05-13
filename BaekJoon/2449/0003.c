#include <stdio.h>
#include <stdlib.h>

#define N_MAX 201

int main(void){
    int i, j, k;
    int iN, iK;
    int min, cost;
    int *arr;
    int **DP;

    scanf("%d %d", &iN, &iK);
    arr = (int*)malloc(sizeof(int)*iN);
    for(i = 0; i < iN; i++) scanf("%d", &arr[i]);

    DP = (int**)malloc(sizeof(int*)*(iN+1));    
    for(i = 0; i < iN+1; i++) DP[i] = (int*)malloc(sizeof(int)*iN);
    for(i = 0; i < iN; i++) DP[1][i] = 0;

    for(i = 2; i <= iN; i++){
        for(j = 0; j <= iN - i; j++){
            min = N_MAX;  
            for(k = 1; k < i; k++){
                cost = DP[k][j] + DP[i - k][j + k];
                if(arr[j] != arr[j + k] && arr[j] != arr[j + i - 1] && arr[j + k - 1] != arr[j + k] && arr[j + k - 1] != arr[j + i - 1]) cost++;
                if(cost < min) min = cost;
            }
            DP[i][j] = min;
        } 
    }

    printf("%d\n", DP[iN][0]);

    free(DP);
    free(arr);
    return 0;
}