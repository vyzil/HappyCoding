#include <stdio.h>
#include <stdlib.h>

int main(void){
    int N, Q;
    int q, x;
    int *arr, cnt;

    scanf("%d %d", &N, &Q);    
    arr = (int*)calloc(N+1, sizeof(int));

    cnt = N;
    while(Q--){
        scanf("%d", &q);
        if(q == 1){
            scanf("%d", &x);
            if(arr[x] == 0){
                arr[x] = 1;
                cnt--;
            }
        }
        else if (q == 2){
            scanf("%d", &x);
            if(arr[x] == 1){
                arr[x] = 0;
                cnt++;
            }

        }
        else {  // q == 3
            printf("%d\n", cnt);
        }
    }

    free(arr);
    return 0;
}