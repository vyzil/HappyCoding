#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i = 0;
    int N, tmp;
    int cur;
    int *arr;
    int *stack, top, low, mid, high;
    int *pos;

    top = 0;
    
    scanf("%d", &N);
    arr = (int*)malloc(sizeof(int)*N);
    stack = (int*)malloc(sizeof(int)*N);
    pos = (int*)malloc(sizeof(int)*N);

    for(i = 0; i < N; i++) {        
        scanf("%d", &cur);
        arr[i] = cur;
        low = 0; 
        high = top - 1;
        while(low <= high){
            mid = (low + high) / 2;
            if (cur > stack[mid]) low = mid + 1;
            else if (cur < stack[mid]) high = mid - 1;
            else {  // cur == mid
                low = mid;
                break;
            }
        }
        
        if(low >= top) top++;
        stack[low] = cur;
        pos[i] = low;
    }

    tmp = top - 1;
    for(i = N-1; i >= 0; i--){
        if(pos[i] == tmp) stack[tmp--] = arr[i];
    }

    printf("%d\n", top);
    for(i = 0; i < top; i++) printf("%d ", stack[i]);
    printf("\n");

    return 0;
}