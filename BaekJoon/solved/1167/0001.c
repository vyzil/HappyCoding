#include <stdio.h>
#include <stdlib.h>

// using 플루이드-워셜 (maybe..?)
int main(void){
    int N, src, dst, len, mid;
    int i, j;
    int max;
    int **arr;

    scanf("%d", &N);
    arr = (int**)malloc(sizeof(int*)*N);
    for(i = 0; i < N; i++){
        scanf("%d", &src);
        arr[src-1] = (int*)calloc(N, sizeof(int));            // len input is Natural Number, 0 can mean infinite or src = dst
        for(scanf("%d", &dst); dst != -1; scanf("%d", &dst)){
            scanf("%d", &len);
            arr[src-1][dst-1] = len;
        }
    }

    for(mid = 0; mid < N; mid++){
        for(dst = 0; dst < N; dst++){
            if(arr[mid][dst] == 0) continue;
            for(src = 0; src < N; src++){
                if(src == dst) continue;
                if(arr[src][mid] == 0) continue;
                if(arr[src][dst] == 0 || arr[src][dst] > arr[src][mid] + arr[mid][dst]) arr[src][dst] = arr[src][mid] + arr[mid][dst];
            }
        }
    }

    max = 0;
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            if(max < arr[i][j]) max = arr[i][j];
        }
    }
    printf("%d\n", max);
    
    // free 
    for(i = 0; i < N; i++) free(arr[i]);
    free(arr);

    return 0;
}