#include <stdio.h>
#include <stdlib.h>

void solve(){
    int i, iN;
    int start, end, isRev;
    int *iArr, dCount, rCount;
    char iFunc[100001], iC, funcIdx;
  
    do scanf("%c", &iC); 
    while( !(iC == 'R' || iC == 'D') );

    dCount = 0;
    rCount = 0;
    funcIdx = 0;
    while( iC == 'R' || iC == 'D' ){
        if(iC == 'D') {
            if(rCount) {
                iFunc[funcIdx++] = 'R';
                rCount = 0;
            }
            iFunc[funcIdx++] = 'D';
            dCount++;
        }
        else rCount = (1 - rCount);
        scanf("%c", &iC);
    }
    if(rCount) iFunc[funcIdx++] = 'R';
    iFunc[funcIdx] = '\0';
    
    scanf("%d", &iN);
    if(dCount > iN) {
        printf("error\n");
        do scanf("%c", &iC); 
        while(iC != ']');
        return;
    }

    iArr = (int*)malloc(sizeof(int)*iN);
    do scanf("%c", &iC); 
    while(iC != '[');
    
    for(i = 0; iC != ']'; i++) {
        scanf("%d", iArr + i);
        scanf("%c", &iC);
    }

    start = 0;
    end = iN - 1;
    isRev = 0;
    for(i = 0; iFunc[i]; i++){
        if(iFunc[i] == 'R') isRev = 1 - isRev;
        else if (isRev) end--;
        else start++;
    }

    printf("[");
    if(isRev){
        for(i = end; i >= start; i--){
            printf("%d", iArr[i]);
            if(i != start) printf(",");
        }
    }
    else{
        for(i = start; i <= end; i++){
            printf("%d", iArr[i]);
            if(i != end) printf(",");
        }
    }
    printf("]\n");

    free(iArr);
    return;
}

int main(void){
    int i;
    int iT;

    scanf("%d", &iT);
    for(i = 0; i < iT; i++) solve();

    return 0;
}