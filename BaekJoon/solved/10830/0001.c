#include <stdio.h>
#include <stdlib.h>

#define MOD 1000

int iN;

void matMult(int ***matA, int ***matB, int ***tmp){
    int i, j, k, product, **swap;

    for(i = 0; i < iN; i++){
        for(j = 0; j < iN; j++){
            product = 0;
            for(k = 0; k < iN; k++) product = (product + (*matA)[i][k] * (*matB)[k][j]) % MOD;
            (*tmp)[i][j] = product;
        }
    }

    swap = *matA;
    *matA = *tmp;
    *tmp = swap;
    return;
}


int main(void){
    int i, j;
    long long iB;
    int **matrix, **tmpMatrix;
    int **res;

    scanf("%d %lld", &iN, &iB);

    matrix = (int**)malloc(sizeof(int*)*iN);
    tmpMatrix = (int**)malloc(sizeof(int*)*iN);
    res = (int**)malloc(sizeof(int*)*iN);
    for(i = 0; i < iN; i++){    
        matrix[i] = (int*)malloc(sizeof(int)*iN);
        tmpMatrix[i] = (int*)malloc(sizeof(int)*iN);
        res[i] = (int*)calloc(iN, sizeof(int));
        for(j = 0; j < iN; j++){
            scanf("%d", &matrix[i][j]);
            if(i == j) res[i][j] = 1;
        }
    }

    if(iB % 2) matMult(&res, &matrix, &tmpMatrix);
    iB >>= 1;

    while(iB > 0){
        matMult(&matrix, &matrix, &tmpMatrix);
        if(iB % 2) matMult(&res, &matrix, &tmpMatrix);
        iB >>= 1;
    }

    for(i = 0; i < iN; i++){
        for(j = 0; j < iN; j++) printf("%d ", res[i][j]);
        printf("\n");
    }

}