#include <stdio.h>
#include <stdlib.h>

int main(void){
    int iN, iH;
    char iArr;

    scanf("%d %d", &iN, &iH);
    iArr = (char*)malloc(sizeof(char)*(iN+1));
    scanf("%s", iArr);


    free(iArr);

    return 0;
}