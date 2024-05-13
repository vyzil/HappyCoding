#include <stdio.h>
#include <stdlib.h>

// O(n^2) Code >> I have to utilize FFT to make this O(nlogn)
int main(void){    
    int n, i, j, idx, max;
    int* arr1;
    int* arr2;
    int* res;

    scanf("%d", &n);

    arr1 = (int*)malloc(sizeof(int)*n);
    arr2 = (int*)malloc(sizeof(int)*n);
    res  = (int*)calloc(n, sizeof(int));
    
    for(i = 0; i < n; i++) scanf("%d", &arr1[i]);
    for(i = 0; i < n; i++) scanf("%d", &arr2[i]);

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            idx = i-j > 0 ? (i-j)%n - 1 : (i-j)%n + n - 1;
            res[idx] += arr1[i]*arr2[j];
        }
    }

    max = 0;
    for(i = 0; i < n; i++) {
        if(max < res[i]) max = res[i];
    }
    printf("%d\n", max);

    return 0;
}