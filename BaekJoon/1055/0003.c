#include <stdio.h>
#include <string.h>

#define ll long long

int main(void){
    int i, j, idx; char iStr[51]; char dStr[51];
    int execNum, min, max;
    int iStrSize, dStrSize, dSize, rSize;
    int treeIdxArr[32], curNum, curChunk, height, carry;
    ll strLenArr[32]; int lenArrSize;
 
    // input
    scanf("%s", iStr);
    scanf("%s", dStr);
    scanf("%d", &execNum);
    scanf("%d %d", &min, &max);
    iStrSize = strlen(iStr); dStrSize = strlen(dStr);

    // Calc Meta Data : pattern, count $, count rest
    dSize = 0;    
    idx = 0;
    for(i = 0; i < dStrSize; i++) {
        if(dStr[i] == '$') dSize++; 
    }

    rSize = dStrSize - dSize;

    if(dSize == 1){
        strLenArr[0] = iStrSize + (dStrSize - 1) * execNum;
        for(i = min - 1; i < max && i < iStrSize; i++) printf("%c", iStr[i]);
        for(j = 0; i < max && i < (int)strLenArr[0]; i++, j++) printf("%c", dStr[(j % (dStrSize-1))  + 1]);
        for(;i < max ; i++) printf("-");
        printf("\n");
        goto finale;
    }

    // Calculate Tree Size with Depth
    for(lenArrSize = 0; (1 << lenArrSize) < max; lenArrSize++); lenArrSize++;
    strLenArr[0] = iStrSize;    
    for(i = 1; i <= lenArrSize; i++){
        strLenArr[i] = strLenArr[i-1] * dSize + rSize;
        if(strLenArr[i] > (ll)max) {   
            if (execNum > i) execNum = i;         
            lenArrSize = i + 1;
            break;
        }
    }

    // Calculate treeIdx of min
    for(i = 0; i <= lenArrSize; i++) treeIdxArr[i] = 0;
    
    curNum = min - 1;
    idx = lenArrSize - 1;
    while(curNum > 0){
        while((ll)curNum < strLenArr[idx] && idx >= 0) idx--;
        if(idx < 0) break;
        while(curNum > 0){
            if (dStr[treeIdxArr[idx]] == '$') {
                curChunk = strLenArr[idx];
                if(curNum - curChunk < 0) break;
                treeIdxArr[idx]++;
            }
            else if('a' <= dStr[treeIdxArr[idx]] && dStr[treeIdxArr[idx]] <= 'z') {
                curChunk = 1;
                treeIdxArr[idx]++;
                if(curNum - curChunk < 0) break;
            }
            curNum -= curChunk;
        }
    }

    // Print from min to max
    for(i = min - 1; i < max && (ll)i < strLenArr[execNum]; i++){
        height = execNum;
        while(height >= 0 && dStr[treeIdxArr[height]] == '$') height--;
        if(height < 0) {
            printf("%c", iStr[curNum]);
            curNum++;
            if(curNum == iStrSize) {
                curNum = 0;
                carry = 1;
                height++;
            }
        }
        else {
            printf("%c", dStr[treeIdxArr[height]]);
            treeIdxArr[height]++;
            if(treeIdxArr[height] == dStrSize){
                treeIdxArr[height] = 0;
                carry = 1;
                height++;
            }
        }
        while(carry){
            treeIdxArr[height]++;
            if(treeIdxArr[height] == dStrSize) {
                treeIdxArr[height] = 0;
                height++;
            }
            else carry = 0;
        }
    }
    for(; i < max; i++) printf("-");
    printf("\n");

finale:
    return 0;
}

