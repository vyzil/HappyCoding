#include <stdio.h>

int main(void){
    int i;
    int iN, iM;
    int *iArr;

    scanf("%d %d", &iN, &iM);
    iArr = (int*)malloc(sizeof(int)*iN);
    for(i = 0; i < iN; i++) scanf("%d", &iArr[i]);





    return 0;
}