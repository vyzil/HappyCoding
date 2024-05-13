#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i, t;
    int iT, iN;
    int start, end, isRev, isError;
    int *iArr, dCount;
    char iFunc[100001], iC;

    scanf("%d", &iT);
    for(t = 0; t < iT; t++) {
        scanf("%s", iFunc);
        scanf("%d", &iN);

        isError = 0;
        dCount = 0;
        for(i = 0; iFunc[i]; i++){
            if(iFunc[i] == 'D') dCount++;
            if(dCount > iN) {
                printf("error\n");
                do scanf("%c", &iC); 
                while(iC != ']');
                isError = 1;
                break;
            }
        }
        if(isError) continue;

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
    }

    return 0;
}