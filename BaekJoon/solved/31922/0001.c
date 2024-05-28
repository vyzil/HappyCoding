#include <stdio.h>

int main(void){
    int A, P, C;
    int res;
    scanf("%d %d %d", &A, &P, &C);
    res = A + C;
    if(res < P) res = P;
    printf("%d\n", res);

    return 0;
}