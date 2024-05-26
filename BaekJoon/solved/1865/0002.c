#include <stdio.h>

int main(void){
    int i, j;
    int TC;
    int N, M, W;
    int S, E, T;
    int edges[3][5200];
    int dist[501];
    int isNegCycle;

    scanf("%d", &TC);
    while(TC--){
        scanf("%d %d %d", &N, &M, &W);
        for(i = 0; i < M; i++){
            scanf("%d %d %d", &S, &E, &T);
            edges[0][i] = S;
            edges[1][i] = E;
            edges[2][i] = T;
            edges[0][i+M] = E;
            edges[1][i+M] = S;
            edges[2][i+M] = T;
        }
        for(i = 2*M; i < 2*M+W; i++){
            scanf("%d %d %d", &S, &E, &T);
            edges[0][i] = S;
            edges[1][i] = E;
            edges[2][i] = -T;
        }

        isNegCycle = 0;
        for(i = 1; i < N+1; i++) dist[i] = 0;
        for(i = 0; i < N; i++){
            for(j = 0; j < 2*M+W; j++){
                S = edges[0][j];
                E = edges[1][j];
                T = edges[2][j];
                if(dist[E] > dist[S] + T){
                    dist[E] = dist[S] + T;
                    if(i == N - 1){
                        isNegCycle = 1;
                        break;
                    }
                }
            }
            if(isNegCycle) break;
        }

        if(isNegCycle) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}