#include <stdio.h>

int main(void){
    int i, j;
    int R, C;
    char MAP[1000][1000];
    int vMAP[1000][1000] = {0};
    int cnt, num, r, c;

    scanf("%d %d", &R, &C);
    for(i = 0; i < R; i++) scanf("%s", MAP[i]);

    num = 0;
    cnt = 0;
    for(i = 0; i < R; i++){
        for(j = 0; j < C; j++){
            if(vMAP[i][j] != 0) continue;

            // follow map
            num++;
            r = i; c = j;
            while(1){
                if(0 < vMAP[r][c] && vMAP[r][c] < num) break;
                if(vMAP[r][c] == num) {
                    cnt++;
                    break;
                }
                vMAP[r][c] = num;
                if(MAP[r][c] == 'U') r--;
                else if(MAP[r][c] == 'D') r++;
                else if(MAP[r][c] == 'L') c--;
                else c++;
            }
        }
    }

    printf("%d\n", cnt);

    return 0;
}