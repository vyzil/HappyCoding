#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){

    long long i, j, arrIndex, bitIndex;
    long long min, max, sqr, arrSize, result;
    unsigned char *arr, tmp; 

    scanf("%lld %lld", &min, &max);

    result = max - min + 1;
    arrSize = (max - min + 1)/8 + 1;
    arr = (unsigned char*)calloc(arrSize, sizeof(unsigned char));

    sqr = 4;
    for(j = ((min-1)/sqr)+1; sqr * j <= max; j++){
        arrIndex = (sqr * j - min) / 8;
        bitIndex = (sqr * j - min) % 8;
        arr[arrIndex] = arr[arrIndex] | ((unsigned)1 << bitIndex);
    }

    for (i = 3; i*i <= max; i += 2){
        sqr = i*i;
        for(j = ((min-1)/sqr)+1; sqr * j <= max; j++){
            arrIndex = (sqr * j - min) / 8;
            bitIndex = (sqr * j - min) % 8;
            arr[arrIndex] = arr[arrIndex] | ((unsigned)1 << bitIndex);
        }
    }

    for (i = 0; i < arrSize; i++){
        tmp = arr[i];
        while(tmp){
            if(tmp%2) result--;
            tmp >>= 1;
        }
    }

    printf("%lld\n", result);
    free(arr);

    return 0;
}