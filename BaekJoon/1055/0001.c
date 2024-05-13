#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ll long long

int main(void){
    int i, idx; char iStr[51]; char dStr[51];
    int execNum, min, max;
    int iStrSize, dStrSize, dSize, rSize;
    int *treeIdxArr, curNum, curChunk, height, carry;
    ll *expandCache; int cacheSize;
 
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
        expandCache = (ll*)malloc(sizeof(ll)*1);
        if(((max - iStrSize) / rSize) + 1 < execNum) expandCache[0] = max;
        else expandCache[0] = iStrSize + rSize * execNum;
        for(i = min - 1; i < max && i < iStrSize; i++) printf("%c", iStr[i]);
        for(; i < max && (ll)i < expandCache[0]; i++) printf("%c", dStr[((i - iStrSize) % (dStrSize-1))  + 1]);
        for(;i < max ; i++) printf("-");
        printf("\n");
        goto finale;
    }

    // Calculate Tree Size with Depth
    for(cacheSize = 2; ((ll)1 << (cacheSize - 1)) < (ll)max; cacheSize++);
    
    expandCache = (ll*)malloc(sizeof(ll)*cacheSize);
    expandCache[0] = iStrSize;    
    for(i = 1; i < cacheSize; i++){
        expandCache[i] = expandCache[i-1] * dSize + rSize;
        if(expandCache[i] > (ll)max) {   
            if (execNum > i) execNum = i;         
            cacheSize = i + 1;
            break;
        }
    }
    expandCache = realloc(expandCache, sizeof(ll)*cacheSize);

    // Calculate treeIdx of min
    treeIdxArr = (int*)malloc(sizeof(int)*cacheSize);
    for(i = 0; i < cacheSize; i++) treeIdxArr[i] = 0;
    
    curNum = min - 1;
    idx = cacheSize - 1;
    while(curNum > 0){
        while((ll)curNum < expandCache[idx-1] && idx > 0) idx--;
        if(idx <= 0) break;
        while(curNum > 0 && idx > 0){
            if(dStr[treeIdxArr[idx]] == '$') {
                curChunk = expandCache[idx-1];
                if(curNum < curChunk) break;
                treeIdxArr[idx]++;
            }
            else if(('a' <= dStr[treeIdxArr[idx]]) && (dStr[treeIdxArr[idx]] <= 'z')) {
                curChunk = 1;
                treeIdxArr[idx]++;
            }
            else curChunk = 0;
            curNum -= curChunk;
        }
    }
    treeIdxArr[idx] += curNum;

    // Print from min to max
    carry = 0;
    for(i = min - 1; i < max && (ll)i < expandCache[execNum]; i++){
        height = execNum;
        while(height > 0 && dStr[treeIdxArr[height]] == '$') height--;
        if(height == 0) {
            printf("%c", iStr[treeIdxArr[height]]);
            if(++(treeIdxArr[height]) >= iStrSize) carry = 1;
        }
        else {
            printf("%c", dStr[treeIdxArr[height]]);
            if(++(treeIdxArr[height]) >= dStrSize) carry = 1;
        }

        while(carry){
            treeIdxArr[height] = 0;
            height++;
            treeIdxArr[height]++;
            if(treeIdxArr[height] < dStrSize) carry = 0;
        }
    }
    for(; i < max; i++) printf("-");
    printf("\n");

    free(treeIdxArr);
finale:
    free(expandCache);
    return 0;
}

