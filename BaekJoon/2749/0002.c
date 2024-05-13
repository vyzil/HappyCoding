#include <stdio.h>

// Pisano Period
#define MOD 1000000
#define PP  (15*(MOD/10))

int main(void){
    long long i;
    long long N;
    int loopCount;
    int fib[PP];

    scanf("%lld", &N);
    fib[0] = 0;
    fib[1] = 1;
    loopCount = (N + 1 > PP ? PP : N + 1);
    for(i = 2; i < loopCount; i++) fib[i] = (fib[i - 1] + fib[i - 2]) % MOD;
        
    printf("%d\n", fib[N % PP]);

    return 0;
}