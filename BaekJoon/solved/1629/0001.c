#include <stdio.h>

int main(void){
    long long iA, iB, iC, res;

    scanf("%lld %lld %lld", &iA, &iB, &iC);

    res = 1;
    if(iB % 2) res = iA % iC;
    iB >>= 1;

    while(iB > 0){
        iA = (iA * iA) % iC;
        if(iB%2) res = (res * iA) % iC;
        iB >>= 1;
    }

    printf("%lld\n", res);

    return 0;
}