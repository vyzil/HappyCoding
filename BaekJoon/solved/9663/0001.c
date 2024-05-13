#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int i;
    int N, top, col, valid, count;
    int* arr;

    scanf("%d", &N);
    arr = (int*)malloc(sizeof(int)*N);
    for(i = 0; i < N; i++) arr[i] = -1;

    top = 0;
    count = 0;
    while(top >= 0){
        col = ++arr[top]; // Place Queen
        printf("Place (%d, %d) ", top, col);
        if(col >= N){     // If place overflow > top remove
            printf("Undo\n");
            arr[top--] = -1;
            continue;
        }
        valid = 1;
        for(i = 0; i < top; i++){   // Check if place was valid (Column)
            if(arr[i] == col) valid = 0;
            if(arr[i] - i == col - top) valid = 0;
            if(arr[i] + i == col + top) valid = 0;
        }
        if(valid == 1) top++;               // place valid > place next
        if((top == N) && (valid == 1)){     // if last place > count++
            count++;            
            // for(i = 0; i < N; i++) printf("%d ", arr[i]);
            // printf("\n");
        } 
        if(valid == 1) printf("Valid\n");
        else printf("Not Valid\n");
    }

    printf("%d\n", count);
    free(arr);

    return 0;
}