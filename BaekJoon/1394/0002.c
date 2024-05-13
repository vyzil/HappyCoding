#include <stdio.h>
#include <string.h>

int main(void){
    int  i, j, tmp, res;
    int  i1Size, i2Size; 
    char cur;
    char input1[101];       // 알파벳 종류
    char input2[1000001];   // 암호

    scanf("%s", input1);
    scanf("%s", input2);

    i1Size = strlen(input1);
    i2Size = strlen(input2);


    res = 0;
    for(i = 0; i < i2Size; i++){
        cur = input2[i];
        j = 0;
        while(input1[j] != cur) j++;
        res = res * i1Size + j + 1;
        res %= 900528;
    }
    printf("%d\n", res);

    return 0;
}