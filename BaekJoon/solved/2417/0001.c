#include <stdio.h>

#define MAX 4294967296

int main(void){
    unsigned long long iN;
    unsigned long long low, high, mid, pow;

    scanf("%llu", &iN);
    low = 0; 
    high = iN > MAX ? MAX : iN;
    mid = 0;

    while(low <= high){
        mid = (low + high) / 2;
        pow = mid * mid;
        if (pow < iN) low = mid + 1;
        else if (pow > iN) high = mid - 1;
        else {
            printf("%llu\n", mid);
            return 0;
        }
    }

    printf("%llu\n", low);

    return 0;
}