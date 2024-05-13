#include <stdio.h>

int main(void){
    long long i;
    long long n, tmp, count;
    
    scanf("%lld", &n);

    tmp = n;
    count = n;
    for(i = 2; i*i <= n; i++){
        if(tmp % i == 0) count = (count / i) * (i-1);
        while(tmp % i == 0) tmp /= i;
        if(tmp == 1) break;
    }

    if(tmp != 1) count = (count/tmp) * (tmp-1);

    printf("%lld\n", count);

    return 0;
}