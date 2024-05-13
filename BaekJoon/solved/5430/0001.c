#include <stdio.h>
#include <stdlib.h>

void solve(){
    int i, iN;
    int start, end, isRev;
    int *iArr, dCount;
    char iFunc[100001], iC;

    scanf("%s", iFunc);
    scanf("%d", &iN);

    dCount = 0;
    for(i = 0; iFunc[i]; i++){
        if(iFunc[i] == 'D') dCount++;
        if(dCount > iN) {
            printf("error\n");
            do scanf("%c", &iC); 
            while(iC != ']');
            return;
        }
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