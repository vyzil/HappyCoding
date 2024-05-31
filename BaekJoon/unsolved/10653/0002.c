#include <stdio.h>
#include <stdlib.h>

#define DIST(A, B) (((A).x > (B).x ? (A).x - (B).x : (B).x - (A).x) + ((A).y > (B).y ? (A).y - (B).y : (B).y - (A).y))

typedef struct _POINT{
    int x, y;
} POINT;


POINT *arr;
int dynamic[501][501] = {-1, };

int DP(int n, int k){
    if(dynamic[n][k] != -1) return dynamic[n][k];
    if(n - 2 <= k) return dynamic[n][k] = DIST(arr[1], arr[n]);

    for(int i = 2; i < n)

}

int main(void){
    int i;
    int N, K;
    int d, maxIdx, max;

    scanf("%d %d", &N, &K);    
    arr = (POINT*)malloc(sizeof(POINT)*N);
    for(i = 0; i < N; i++) scanf("%d %d", &arr[i].x, &arr[i].y);


    printf("%d\n", DP(N, K));


    free(arr);

    return 0;
}