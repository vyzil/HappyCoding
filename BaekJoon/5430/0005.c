#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i, t, iN, iT;
    int start, end, isRev;
    int *iArr;
    int forDelete, revDelete;
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
        if(start > end + 1) {
            printf("error\n");
            continue;
        }

        iArr = (int*)malloc(sizeof(int)*iN);
        do scanf("%c", &iC); 
        while(iC != '[');
        for(i = 0; iC != ']'; i++) {
            scanf("%d", iArr + i);
            scanf("%c", &iC);
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