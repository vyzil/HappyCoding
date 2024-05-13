#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char arr[1000001];

int main(void){

    long long i, j, arrIndex, bitIndex;
    long long min, max, sqr, arrSize, result;
    char tmp; 

    scanf("%lld %lld", &min, &max);

    result = max - min + 1;
    arrSize = max - min + 1;

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

    return 0;
}