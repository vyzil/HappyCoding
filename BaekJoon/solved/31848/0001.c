#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100000

int main(void){
    int i;
    int N, Q;
    int *nArr, outArr[MAX_SIZE+1], curIdx;
    int qSize;

    scanf("%d", &N);
    nArr = (int*)malloc(sizeof(int)*N);
    for(i = 0; i < N; i++) scanf("%d", &nArr[i]);

    curIdx = 0;
    for(i = 1; i <= MAX_SIZE; i++){
        while(curIdx < N && i - curIdx > nArr[curIdx]) curIdx++;
        outArr[i] = curIdx;
    }
    
    scanf("%d", &Q);
    for(i = 0; i < Q; i++) {
        scanf("%d", &qSize);
        printf("%d ", outArr[qSize] + 1);
    }
    printf("\n");
    return 0;
}