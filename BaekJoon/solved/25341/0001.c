#include <stdio.h>
#include <stdlib.h>

#define ll long long

int main(void){    
    int i, j;
    int N, M, Q;
    int c;
    int **info;
    int *tmp;
    ll res;

    scanf("%d %d %d", &N, &M, &Q);
    info = (int**)malloc(sizeof(int*)*M);
    tmp = (int*)malloc(sizeof(int)*(N+1));

    for(i = 0; i < M; i++){        
        info[i] = (int*)calloc(N+1, sizeof(int));
        scanf("%d", &c);
        for(j = 0; j < c; j++) scanf("%d", &tmp[j]);
        for(j = 0; j < c; j++) scanf("%d", &info[i][tmp[j]]);
        scanf("%d", &info[i][0]);
    }

    for(i = 0; i <= N; i++) tmp[i] = 0;
    for(i = 0; i < M; i++){
        scanf("%d", &c);
        for(j = 0; j <= N; j++) tmp[j] += info[i][j] * c;
    }

    scanf("%d", &c);
    tmp[0] += c;
    while(Q--){
        res = (ll)tmp[0];
        for(i = 1; i <= N; i++) {
            scanf("%d", &c);
            res += (ll)tmp[i] * c;
        }
        printf("%lld\n", res);
    }


    free(tmp);
    for(i = 0; i < M; i++) free(info[i]);
    free(info);
    return 0;
}