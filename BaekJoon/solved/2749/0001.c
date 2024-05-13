#include <stdio.h>

int main(void){
    long long i;
    long long N;
    int fib[3];

    scanf("%lld", &N);
    fib[0] = 0;
    fib[1] = 1;
    for(i = 0; i < N-1; i++){
        fib[2] = (fib[0] + fib[1]) % 1000000;
        fib[0] = fib[1];
        fib[1] = fib[2];
    }

    if(N == 0) printf("0\n");
    if(N == 1) printf("1\n");
    printf("%d\n", fib[2]);

    return 0;
}