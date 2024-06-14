#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20001

int isPrime[MAX];

int main(void){
    int i, j;
    int N;
    int *arr;
    int prime;

    for(i = 0; i < MAX; i++) isPrime[i] = 1;
    for(i = 2; i < MAX; i++){
        if(isPrime[i] == 0) continue;
        for(j = i+i; j < MAX; j += i) isPrime[j] = 0;
    }

    scanf("%d", &N);
    arr = (int*)malloc(sizeof(int)*N);
    for(i = 0; i < N; i++) scanf("%d", &arr[i]);
    prime = 0;
    for(i = MAX-1; i > 0; i--){
        if(isPrime[i] == 0) continue;
        for(j = 0; j < N; j++){
            if(arr[j] % i == 0) {
                prime = 1;
                printf("%d\n", arr[j]);
                break;
            }
        }
        if(prime) break;
    }


    free(arr);

    return 0;
}