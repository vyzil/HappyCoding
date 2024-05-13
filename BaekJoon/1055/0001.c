#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ll long long

int main(void){
    int i, j; char iStr[51]; char dStr[51];
    int execNum, min, max;
    int iStrSize, dStrSize, dSize, rSize; ll strSize;
    int pattern[50] = {0}, patSize, idx; // pattern : accumulate
    int *treeIdxArr, curNum, curChunk, height;
    ll *strLenArr, lenArrSize;
 
    // input
    scanf("%s", iStr);
    scanf("%s", dStr);
    scanf("%d", &execNum);
    scanf("%d %d", &min, &max);
    iStrSize = strlen(iStr); dStrSize = strlen(dStr); strSize = iStrSize;

    // Calc Meta Data : pattern, count $, count rest
    dSize = 0;    
    idx = 0;
    for(i = 0; i < dStrSize; i++) {
        if(dStr[i] == '$') {
            if(pattern[idx] > 0) idx++;
            dSize++; 
            idx++;
        }
        else pattern[idx]++;
    }
    if(pattern[idx] > 0) idx++;
    pattern[idx] = -1;
    patSize = idx;
    for(i = 0; i < patSize+1; i++) printf("%d ", pattern[i]); printf("\n");

    rSize = dStrSize - dSize;

    if(dSize == 1){
        strLenArr = (ll*)malloc(sizeof(ll)*1);
        strLenArr[0] = iStrSize + (dStrSize - 1) * execNum;
        for(i = min - 1; i < max && i < iStrSize; i++) printf("%c", iStr[i]);
        for(j = 0; i < max && i < (int)strLenArr[0]; i++, j++) printf("%c", dStr[(j % (dStrSize-1))  + 1]);
        for(;i < max ; i++) printf("-");
        printf("\n");
        goto finale;
    }

    // Calculate Tree Size with Depth
    for(lenArrSize = 0; (1 << lenArrSize) < max; lenArrSize++); lenArrSize++;
    strLenArr = (ll*)malloc(sizeof(ll)*(lenArrSize + 1));
    strLenArr[0] = iStrSize;    
    for(i = 1; i < execNum; i++){
        strLenArr[i] = strLenArr[i-1] * dSize + rSize;
        if(strLenArr[i] > (ll)max) {            
            lenArrSize = i + 1;
            break;
        }
    }

    // Calculate treeIdx of min
    treeIdxArr = (int*)malloc(sizeof(int)*lenArrSize);
    for(i = 0; i < lenArrSize; i++) treeIdxArr[i] = 0;
    
    curNum = min - 1;
    idx = lenArrSize - 1;
    while(curNum > 0 && idx >= 0){
        while(curNum < strLenArr[idx] && idx >= 0) idx--;
        while(idx >= 0){
            if (pattern[treeIdxArr[idx]] == 0) curChunk = strLenArr[idx];
            else curChunk = pattern[treeIdxArr[idx]];            
            if(curNum - curChunk < 0 || curChunk < 0) break;
            printf("\t%d %d\n", curNum, curChunk);
            curNum -= curChunk;
            treeIdxArr[idx]++;
        }
    }
    printf("curNum = %d\n", curNum);
    for(i = 0; i < lenArrSize; i++) printf("%d ", treeIdxArr[i]); printf("\n");

    // Print from min to max
    for(height = lenArrSize - 1;;){
        while(pattern[treeIdxArr[height]] == 0 && height >= 0) height--;
        if(height < 0) printf("%c", iStr[curNum]);
        else printf("%c", )

    }

    for(i = min; i < max; i++){

    }

finale:
    free(strLenArr);
    return 0;
}

