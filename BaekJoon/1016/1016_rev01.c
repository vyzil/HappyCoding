#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){

    long long i, j, arrIndex, bitIndex;
    long long min, max, sqr, arrSize, result;
    char *arr, tmp; 

    scanf("%lld %lld", &min, &max);

    result = max - min + 1;
    arrSize = max - min + 1;
    arr = (char*)malloc(sizeof(char)*(arrSize));
    memset(arr, 0, arrSize);

    for (i = 2; i*i <= max; i++){
        sqr = i*i;
        for(j = ((min-1)/sqr)+1; sqr * j <= max; j++){
            arr[sqr * j - min] = 1;
        }
    }

    for (i = 0; i < arrSize; i++){
        if(arr[i]) result--;
    }

    printf("%lld\n", result);
    free(arr);

    return 0;
}