#include <stdio.h>
#include <string.h>

int main(void){
    int  i, j, tmp, res;
    int  i1Size, i2Size; 
    char cur;
    int  pos[128];
    char input1[101];       // 알파벳 종류
    char input2[1000001];   // 암호

    scanf("%s", input1);
    scanf("%s", input2);

    i1Size = strlen(input1);
    i2Size = strlen(input2);

    for(i = 0; i < i1Size; i++) pos[input1[i]] = i + 1;
    
    res = 0;
    for(i = 0; i < i2Size; i++){
        res = res * i1Size + pos[input2[i]];
        res %= 900528;
    }
    printf("%d\n", res);

    return 0;
}