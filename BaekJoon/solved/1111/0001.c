#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i;
    int N;
    int a, b;
    int *arr;

    scanf("%d", &N);
    arr = (int*)malloc(sizeof(int)*N);
    for(i = 0; i < N ; i++) scanf("%d", &arr[i]);

    if(N < 3) {
        if(N == 2 && arr[0] == arr[1]) printf("%d\n", arr[0]);
        else printf("A\n");
        goto finale;
    }
    else{
        if(arr[0] == arr[1]) a = 0;
        else a = (arr[2] - arr[1]) / (arr[1] - arr[0]);
        b = arr[2] - arr[1] * a;
        for(i = 1; i < N; i++){
            if(arr[i-1]*a + b != arr[i]) {
                printf("B\n");
                goto finale;
            }
        }
        printf("%d\n", a*arr[N-1] + b);
    }

finale:
    free(arr);
    return 0;
}