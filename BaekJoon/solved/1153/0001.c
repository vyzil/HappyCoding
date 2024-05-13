#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i, j;
    int n, primeTop, tmp;
    int* prime;
    int output[4] = {0,};

    scanf("%d", &n);

    prime = (int*)calloc(n+1, sizeof(int));
    primeTop = 0;

    // 1. Make Prime Array
    // re-use "prime" : first as Eratos, second as prime array 
    for(i = 2; i < n+1; i++){
        if(prime[i] == 0) prime[primeTop++] = i;
        for(j = 2*i; j < n+1; j += i){
            prime[j] = -1;
        }
    }

    // 2. Calculate Output
    while(1){
        tmp = prime[output[0]] + prime[output[1]] + prime[output[2]] + prime[output[3]];
        if(tmp == n) break;
        output[0]++;
        for(i = 0; i < 4; i++){
            if(output[i] >= primeTop){
                output[i] = 0;
                output[i+1]++;
            }
        }
        if(output[4] == 1) break;
    }

    if(output[4] == 1) {
        printf("-1");        
    }
    else {
        for(i = 3; i >= 0; i--) printf("%d ", prime[output[i]]);
    }
    printf("\n");

    return 0;
}