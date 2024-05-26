#include <stdio.h>

#define INF ((int)10e9)

int main(void){
    int i, j, k;
    int TC;
    int N, M, W;
    int S, E, T;
    int edges[3][5200];
    int dist[501], visit[501];
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
        for(i = 1; i < N+1; i++) visit[i] = 0;
        for(i = 1; i < N+1; i++){
            if(visit[i] != 0) continue;
            for(j = 1; j < N+1; j++) dist[j] = INF;
            dist[i] = 0;
            for(j = 0; j < N; j++){
                for(k = 0; k < 2*M+W; k++){
                    S = edges[0][k];
                    E = edges[1][k];
                    T = edges[2][k];
                    if(dist[S] != INF && dist[E] > dist[S] + T){
                        dist[E] = dist[S] + T;
                        if(j == N - 1){
                            isNegCycle = 1;
                            break;
                        }
                    }
                }
                if(isNegCycle) break;
            }
            if(isNegCycle) break;
            for(j = 1; j < N+1; j++) {
                if(dist[j] != INF) visit[j] = 1;
            }
        }
        if(isNegCycle) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}