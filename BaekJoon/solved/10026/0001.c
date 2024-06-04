#include <stdio.h>


char pic[100][101];


/* 
 * R = 0b010[1]_001[0] 
 * G = 0b010[0]_011[1]
 * B = 0b010[0]_001[0]
 */
void bfs(int visit[100][100], int r, int c, char color, int N, int cb){
    if(0 > r || r >= N || 0 > c || c >= N) return;
    if(cb && (((pic[r][c] & 0b10001) == 0) != ((color & 0b10001) == 0))) return;
    if(!cb && (pic[r][c] != color)) return;
    
    visit[r][c] = 1;

    if(visit[r+1][c] == 0) bfs(visit, r+1, c, color, N, cb);
    if(visit[r-1][c] == 0) bfs(visit, r-1, c, color, N, cb);
    if(visit[r][c+1] == 0) bfs(visit, r, c+1, color, N, cb);
    if(visit[r][c-1] == 0) bfs(visit, r, c-1, color, N, cb);

    return;
}

int visitSection(int visit[100][100], int N, int cb){
    int i, j;
    int res;

    res = 0;
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            if(visit[i][j] != 0) continue;
            bfs(visit, i, j, pic[i][j], N, cb);
            res++;
        }
    }

    return res;
}

int main(void){
    int i, j;
    int N;
    int visit1[100][100] = {0, };
    int visit2[100][100] = {0, };

    scanf("%d", &N);
    for(i = 0; i < N; i++){
        scanf("%s", pic[i]);
    }

    printf("%d %d\n", visitSection(visit1, N, 0), visitSection(visit2, N, 1));

    return 0;
}