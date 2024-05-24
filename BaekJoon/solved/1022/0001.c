#include <stdio.h>

#define N_MAX 5050 * 2
#define R_MAX 5050 * 2
#define ZERO 5050
#define MODE_NUM 4
#define MODE_R 0
#define MODE_U 1
#define MODE_L 2
#define MODE_D 3

#define NEXT_MODE(mode) (((mode)+1)%MODE_NUM)
#define NEXT_BOARD(r, c, mode) (BOARD[(r)+R_MOD[(mode)]][(c)+C_MOD[(mode)]])
#define IN_RANGE(r, c) ((ZERO + r1 <= (r) && (r) <= ZERO +r2 && ZERO + c1 <= (c) && (c) <= ZERO + c2) ? 1 : 0)

int BOARD[N_MAX][R_MAX] = {0, };
int R_MOD[4] = {0,-1,0,1};
int C_MOD[4] = {1,0,-1,0};

int main(void){
    int i, j;
    int r1, c1, r2, c2;
    int curR, curC, curNum;
    int left, max, mode, maxDigits;
    
    scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
    left = (r2 - r1 + 1) * (c2 - c1  + 1);
       
    max = 0;
    curNum = 1;
    curR = ZERO; curC = ZERO;
    BOARD[curR][curC] = curNum;
    if(IN_RANGE(curR, curC)) left--;
    mode = MODE_D;
    while(left){
        if(NEXT_BOARD(curR, curC, NEXT_MODE(mode)) == 0) mode = NEXT_MODE(mode);
        NEXT_BOARD(curR, curC, mode) = ++curNum;    
        curR += R_MOD[mode];
        curC += C_MOD[mode];    
        if(IN_RANGE(curR, curC)) {
            max = curNum;
            left--;
        }
    }

    for(maxDigits = 0; max; maxDigits++, max /= 10);

    for(i = ZERO + r1; i <= ZERO + r2; i++){
        for(j = ZERO + c1; j <= ZERO + c2; j++){
            printf("%*d ", maxDigits, BOARD[i][j]);
        }
        printf("\n");
    }


    return 0;
}