#include <stdio.h>
#include <stdlib.h>

#define INF 70000000
#define ll long long

int *(edges[3]);

int main(void){
    int i, j;
    int N, M;
    int u, v, d;
    ll *dist; int isNegCycle;
    scanf("%d %d", &N, &M);

    edges[0] = (int*)malloc(sizeof(int)*M);
    edges[1] = (int*)malloc(sizeof(int)*M);
    edges[2] = (int*)malloc(sizeof(int)*M);
    
    for(i = 0; i < M; i++) scanf("%d %d %d", &edges[0][i], &edges[1][i], &edges[2][i]);
    dist = (ll*)malloc(sizeof(ll)*(N+1));
    for(i = 0; i < N+1; i++) dist[i] = INF;
    dist[1] = 0;

    isNegCycle = 0;
    // Bellman-Ford
    for(i = 0; i < N; i++){
        for(j = 0; j < M; j++){
            u = edges[0][j];
            v = edges[1][j];
            d = edges[2][j];
            if(dist[u] != INF && dist[v] > dist[u] + (ll)d) {
                dist[v] = dist[u] +(ll) d;
                if(i == N-1) {
                    isNegCycle = 1;
                    break;
                }
            }
        }
        if(isNegCycle) break;
    }

    if(isNegCycle) printf("-1\n");
    else {
        for(i = 2; i <= N; i++) {
            if(dist[i] == INF) printf("-1\n");
            else printf("%lld\n", dist[i]);
        }
    }

    return 0;
}