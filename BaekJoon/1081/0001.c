#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*  
 *  [fix][range][free]
 *  ex) processing '5' in 34567 
 *  [34][0~4|5][XX]
 *  [34]    : (3 + 4) * 5 * (10^2)
 *  [0~4|5] : (0 + 1 + 2 + 3 + 4) * (10^2)  // if last, (0 + 1 + 2 + 3 + 4 + 5)
 *  [XX]    : (0 + 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9) * 5 * (10^2 / 10) * 2
 */

const int NUMSUM[10] = {0, 1, 3, 6, 10, 15, 21, 28, 36, 45};

long long calc(int num){
    int i;
    int tmp, size;
    int *numArr; 
    int highSum, freeNum;
    long long res;

    if(num <= 0) return 0;

    for(tmp = num, size = 0; tmp > 0; tmp /= 10) size++;
    numArr = (int*)malloc(sizeof(int)*size);
    for(i = size - 1, tmp = num; i >= 0; i--, tmp /= 10) numArr[i] = tmp % 10;

    res = 0;
    highSum = 0;
    for(i = 0; i < size - 1; i++){
        freeNum = pow(10, size - i - 1);
        res += (long long)highSum * numArr[i] * freeNum;
        res += (long long)(NUMSUM[numArr[i]] - numArr[i]) * freeNum;
        res += (long long)NUMSUM[9] * numArr[i] * (freeNum / 10) * (size - i - 1);
        highSum += numArr[i];
    }

    res += highSum * (numArr[i] + 1);
    res += NUMSUM[numArr[i]];

    free(numArr);
    return res;
}

int main(void){
    int iL, iU;
    
    scanf("%d %d", &iL, &iU);
    printf("%lld\n", calc(iU) - calc(iL - 1));

    return 0;
}