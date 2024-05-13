#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    int i, j; 
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
                // binarySearch
                low = 0;
                high = dpSize-1;
                while(low <= high){
                    mid = (low + high) / 2;
                    
                    if(indexDP[mid] < j) low = mid+1;
                    else if((indexDP[mid] > j)) high = mid-1;
                    else {
                        low = mid;
                        break;
                    }
                }
                indexDP[low] = j;
                if(low == dpSize) dpSize++;
            }
        }
    }

    printf("%d\n", dpSize);

    return 0;
}