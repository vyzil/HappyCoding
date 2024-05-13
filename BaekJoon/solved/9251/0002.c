#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    int i, j, k; 
    char inputString[1001];
    char inputPattern[1001];
    int strSize, patSize;
    int *indexDP, dpSize;
    char curChar;
    int low, high, mid;


    scanf("%s", inputString);
    scanf("%s", inputPattern);

    strSize = strlen(inputString);
    patSize = strlen(inputPattern);

    indexDP = (int*)malloc(sizeof(int)*(strSize > patSize? strSize : patSize));
    dpSize = 0;
    for(i = 0; i < strSize; i++){
        curChar = inputString[i];
        for(j = patSize-1; j >= 0; j--){
            if(inputPattern[j] == curChar){
                // Linear Search
                for(k = dpSize-1; k >= 0; k--){
                    if(indexDP[k] < j) break;
                }
                if(k+1 == dpSize) dpSize++;
                indexDP[k+1] = j;
            }
        }
    }

    printf("%d\n", dpSize);
    free(indexDP);

    return 0;
}