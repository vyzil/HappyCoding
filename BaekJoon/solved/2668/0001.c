#include <stdio.h>
#include <stdlib.h>

#define NEVER_VISIT 0
#define NOW_VISIT   1
#define IS_CYCLE    2
#define NOT_CYCLE   3
#define LOOP_FOUND  4

int main(void){
    int i;
    int N;
    int *arr, *visit;
    int *stack, top;
    int cnt;

    scanf("%d", &N);
    arr = (int*)malloc(sizeof(int)*N);
    visit = (int*)malloc(sizeof(int)*N);
    stack = (int*)malloc(sizeof(int)*N);
    for(i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
        arr[i]--;
        visit[i] = NEVER_VISIT;
    }

    cnt = 0;
    for(i = 0; i < N; i++){
        if(visit[i] != NEVER_VISIT) continue;

        visit[i] = NOW_VISIT;
        top = 0;
        stack[top] = i;
        while(visit[arr[stack[top]]] == NEVER_VISIT){
            visit[arr[stack[top]]] = NOW_VISIT;
            stack[top+1] = arr[stack[top]];
            top++;
        }

        if(visit[arr[stack[top]]] == NOW_VISIT){
            visit[arr[stack[top]]] = LOOP_FOUND;
            while(visit[stack[top]] == NOW_VISIT){
                visit[stack[top]] = IS_CYCLE;
                cnt++;
                top--;
            }
            visit[stack[top]] = IS_CYCLE;
            cnt++;
            top--;
        }

        while(top >= 0){
            visit[stack[top]] = NOT_CYCLE;
            top--;
        }
    }

    printf("%d\n", cnt);
    for(i = 0; i < N; i++){
        if(visit[i] == IS_CYCLE) printf("%d\n", i+1);
    }

    free(arr);
    free(visit);
    free(stack);

    return 0;
}