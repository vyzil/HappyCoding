#include <stdio.h>

int main(void){
    int N, res;

    scanf("%d", &N);
    res = (N/5) + (N%5 - 1)%2 + 1;
    if(N == 4 || N == 7) res = -1;
    printf("%d\n", res);

    return 0;
}