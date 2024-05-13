#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i, j;
    int iN, iP;
    int iInt;
    int iF0;
    int eval, tmp;
    int *iArr;

    scanf("%d %d", &iN, &iP);
    iArr = (int*)calloc(iP, sizeof(int));
    for(i = iN; i > 0; i--) {
        scanf("%d", &iInt);
        iArr[i % (iP-1)] = (iArr[i % (iP-1)] + iInt) % iP;
    }
    scanf("%d", &iF0);
    iF0 = iF0 % iP;
    iArr[0] = (iArr[0] + iF0) % iP;
    
    printf("%d\n", iF0);
    for(i = 1; i < iP; i++){
        eval = 0;
        tmp = 1;
        for(j = 0; j < iP; j++){
            eval = (eval + tmp * iArr[j]) % iP;
            tmp = (tmp * i) % iP;
        }
        printf("%d\n", eval);
    }
    free(iArr);

    return 0;
}