#include <stdio.h>

#define ll long long

int main(void){
    ll N;
    scanf("%lld", &N);
    
    if((N%7) & (~0b10)) printf("SK\n");
    else printf("CY\n");

    return 0;
}