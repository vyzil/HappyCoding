#include <stdio.h>

int main(void){
    long long  N;
    scanf("%lld", &N);

    if((N%5)&5) printf("SK\n");
    else printf("CY\n");

    return 0;
}