#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i, t, tmp;
    int iT, iN;
    int start, end, isRev, shortCut;
    int *iArr, forDelete, revDelete, arrSize;
    char iFunc[100001], iC;

    scanf("%d", &iT);
    for(t = 0; t < iT; t++) {
        scanf("%s", iFunc);
        scanf("%d", &iN);
        getchar();

        isRev = 0;
        shortCut = 0;
        forDelete = 0;
        revDelete = 0;
        for(i = 0; iFunc[i]; i++){
            if(iFunc[i] == 'D') {
                if(isRev) revDelete++;
                else      forDelete++;
            }
            else isRev = 1 - isRev;

            if(forDelete + revDelete > iN) {
                printf("error\n");
                scanf("%s", iFunc);
                shortCut = 1;
                break;
            }
        }
        if(shortCut) continue;

        if(forDelete + revDelete == iN){
            printf("[]\n");
            scanf("%s", iFunc);
            continue;
        }

        end = iN - 1 - revDelete;
        start = forDelete;
        arrSize = end - start + 1;

        iArr = (int*)malloc(sizeof(int)*arrSize);
        do scanf("%c", &iC); 
        while(iC != '[');
        
        for(i = 0; i < start; i++) {
            scanf("%d", &tmp);
            scanf("%c", &iC);
        }

        for(i = 0; i < arrSize; i++) {
            scanf("%d", iArr + i);
            scanf("%c", &iC);
        }
        
        if(iC != ']') scanf("%s", iFunc);
        getchar();

        printf("[");
        if(isRev){
            for(i = arrSize - 1; i >= 0; i--){
                printf("%d", iArr[i]);
                if(i != 0) printf(",");
            }
        }
        else{
            for(i = 0; i < arrSize; i++){
                printf("%d", iArr[i]);
                if(i != arrSize - 1) printf(",");
            }
        }
        printf("]\n");

        free(iArr);
    }

    return 0;
}