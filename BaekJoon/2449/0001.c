#include <stdio.h>
#include <stdlib.h>

#define N_MAX 201

int main(void){
    int i, j;
    int iN, iK;
    int start, end;
    int group1, group2;
    int min, cost;
    int *arr;
    int **DP;

    scanf("%d %d", &iN, &iK);
    if(iN < 2){
        printf("0\n");
        return 0;
    }

    arr = (int*)malloc(sizeof(int)*iN);
    for(i = 0; i < iN; i++) scanf("%d", &arr[i]);

    DP = (int**)malloc(sizeof(int*)*(iN+1));    
    for(i = 0; i < iN+1; i++) DP[i] = (int*)malloc(sizeof(int)*iN);
    for(i = 0; i < iN; i++) DP[1][i] = 0;

    for(i = 2; i <= iN; i++){
        printf("i : %d\n", i);
        for(j = 0; j <= iN - i; j++){
            printf("\tj : %d\n", j);
            min = N_MAX;  
            for(group1 = 1, group2 = i - 1; group1 <= group2; group1++, group2--){         
                cost = DP[group1][j] + DP[group2][j + group1];
                if(arr[j] != arr[j + group1] && arr[j] != arr[j + i - 1] && arr[j+group1-1] != arr[j + group1] && arr[j+group1-1] != arr[j + i -1]) cost++;
                if(cost < min) min = cost;
                printf("\tDP[%d][%d] + DP[%d][%d] + @ = %d\n", group1, j, group2, j + group1, cost);
                
                cost = DP[group1][j + group2] + DP[group2][j];
                if(arr[j] != arr[j + group2] && arr[j] != arr[j + i - 1] && arr[j+group2-1] != arr[j + group2] && arr[j+group2-1] != arr[j + i - 1]) cost++;
                if(cost < min) min = cost;
                printf("\tDP[%d][%d] + DP[%d][%d] + @ = %d\n", group1, j + group2, group2, j, cost);
            }
            DP[i][j] = min;
            printf("\tDP[%d][%d] = %d\n", i, j, min);
        }
        for(j = 0; j < iN - i + 1; j++) printf("%d ", DP[i][j]); printf("\n");
        
    }

    printf("%d\n", DP[iN][0]);

    free(DP);
    free(arr);
    return 0;
}