#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i;
    int n, p, k, d;
    int *arr, sum;

    scanf("%d %d %d %d", &n, &p, &k, &d);
    arr = (int*)calloc(n, sizeof(int));

    if (d > 1) {
        sum = 0;
        for(i = 0; i < d-1; i++) {
            arr[i] += (d - 1 - i);
            sum += (d - 1 - i);
        }
        if(sum > p) {
            printf("Wrong information\n");
            goto finale;
        }     
        arr[0] += p - sum; 
    }
    else { // d == 1
        for(i = 0; i < k; i++) arr[i] = p/k;
        sum = arr[0] * k;
        for(i = k; i < n; i++) {
            if((p - sum) >= p/k) {
                arr[i] = p/k;
                sum += p/k;
            }
            else {
                arr[i] = (p - sum);
                sum = p;
                break;
            }
        }
        if(p - sum > 0) {
            printf("Wrong information\n");
            goto finale;
        }
    }

print:
    // for(i = 0; i < n; i++) printf("%d\n", arr[i]);
    for(i = 0; i < n; i++) printf("%d\n", arr[i]);

finale:

    return 0;
}