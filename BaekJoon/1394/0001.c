#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    int  i, j, tmp, res;
    int  i1Size, i2Size; 
    char cur;
    int* arr;               // arr[i] = 길이 i인 경우의 수
    char input1[101];       // 알파벳 종류
    char input2[1000001];   // 암호

    scanf("%s", input1);
    scanf("%s", input2);

    i1Size = strlen(input1);
    i2Size = strlen(input2);

    arr = (int*)malloc(sizeof(int)*i2Size);
    arr[0] = 1;

    tmp = 1;
    res = 1;
    for(i = 1; i < i2Size; i++){
        tmp *= i1Size;
        tmp %= 900528;
        arr[i] = tmp;
        res += tmp;
        res %= 900528;
    }

    // password 앞부분부터 확정하면서 count
    for(i = 0; i < i2Size; i++){
        cur = input2[i];
        j = 0;
        while(input1[j] != cur) j++;
        res += j * arr[i2Size-1-i];
        res %= 900528;
    }
    printf("%d\n", res);

    return 0;
}