#include <stdio.h>
#include <stdlib.h>

#define moveNum 8
const int dx[moveNum] = {+1, +2, +2, +1, -1, -2, -2, -1};
const int dy[moveNum] = {+2, +1, -1, -2, -2, -1, +1, +2};
#define IN_RANGE(x, y, N) ((0 <= (x) && (x) < (N) && 0 <= (y) && (y) < (N)))

int main(void){
    int i, j, k;
    int N, x, y, K;
    int _x, _y;
    double **map, **tmp, **swap;
    double res;

    scanf("%d %d %d %d", &N, &x, &y, &K);

    map = (double**)malloc(sizeof(double*)*N);
    tmp = (double**)malloc(sizeof(double*)*N);
    for(i = 0; i < N; i++){
        map[i] = (double*)malloc(sizeof(double)*N);
        tmp[i] = (double*)malloc(sizeof(double)*N);
        for(j = 0; j < N; j++) tmp[i][j] = 0.0;
    }

    map[x-1][y-1] = 1;
    while(K--){
        for(i = 0; i < N; i ++){
            for(j = 0; j < N; j++) tmp[i][j] = 0;
        }
        for(i = 0; i < N; i ++){
            for(j = 0; j < N; j++) {
                if(map[i][j] == 0) continue;
                for(k = 0; k < moveNum; k++){
                    x = i + dx[k];
                    y = j + dy[k];
                    if(IN_RANGE(x, y, N)) tmp[x][y] += (map[i][j]/8);
                }                
            }
        }
        swap = tmp;
        tmp = map;
        map = swap;
    }

    res = 0.0;
    for(i = 0; i < N; i ++){
        for(j = 0; j < N; j++) res += map[i][j];
    }
    printf("%.9f\n", res);

    for(i = 0; i < N; i++){
        free(map[i]);
        free(tmp[i]);
    }
    free(map);
    free(tmp);

    return 0;
}