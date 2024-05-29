#include <stdio.h>

#define N_MAX 1000
#define M_MAX 300000
#define ll long long

#define MAX(a, b)   ((a) > (b) ? (a) : (b))
#define MIN(a, b)   ((a) < (b) ? (a) : (b))

int g_matrix[N_MAX][N_MAX];
int g_query[M_MAX][5];

int main(void){
    int i, j;
    int N, M;
    int q, i_1, j_1, i_2, j_2;
    int w, h;
    ll res, sum;

    scanf("%d %d", &N, &M);

    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++) scanf("%d", &g_matrix[i][j]);
    }

    for(i = 0; i < M - 1; i++) scanf("%d %d %d %d %d %d", &q, &g_query[i][0], &g_query[i][1], &g_query[i][2], &g_query[i][3], &g_query[i][4]);        
    scanf("%d %d %d %d %d", &q, &i_1, &j_1, &i_2, &j_2);    
    res = 0;
    for(i = i_1; i <= i_2; i++){
        for(j = j_1; j <= j_2; j++) res += (ll)g_matrix[i][j];
    }
    for(i = 0; i < M-1; i++){
        w = MIN(g_query[i][2], i_2) - MAX(g_query[i][0], i_1) + 1;
        w = MAX(w, 0);
        h = MIN(g_query[i][3], j_2) - MAX(g_query[i][1], j_1) + 1;
        h = MAX(h, 0);
        sum = (ll)w * (ll)h * (ll)g_query[i][4];
        res += sum;
    }
    
    printf("%lld\n", res);

    return 0;
}