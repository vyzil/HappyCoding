#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i, t, tmp;
    int iT, iN;
    int start, end, isRev;
    int *iArr, forDelete, revDelete, arrSize;
    char iC;

    scanf("%d", &iT);
    for(t = 0; t < iT; t++) {
        forDelete = 0;
        revDelete = 0;
        isRev = 0;
        do scanf("%c", &iC); 
        while( !(iC == 'R' || iC == 'D') );
        while( iC == 'R' || iC == 'D' ){
            if(iC == 'D') {
                if(isRev) revDelete++;
                else forDelete++;
            }
            else isRev = (1 - isRev);
            scanf("%c", &iC);
        }
        
        scanf("%d", &iN);
        end = iN - 1 - revDelete;
        start = forDelete;
        arrSize = end - start + 1;
        if(arrSize < 0) {
            printf("error\n");
            continue;
        }
        if(arrSize == 0){
            printf("[]\n");
            continue;
        }

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
        
        while (iC != ']') scanf("%c", &iC);

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