#include <stdio.h>
#include <stdlib.h>

#define MODE_NUM 4
#define MODE_R 0
#define MODE_U 1
#define MODE_L 2
#define MODE_D 3

#define IN_RANGE(r, c) ((r1 <= (r) && (r) <= r2 && c1 <= (c) && (c) <= c2) ? 1 : 0)

int R_MOD[4] = {0,-1,0,1};
int C_MOD[4] = {1,0,-1,0};

int main(void){
    int i, j;
    int r1, c1, r2, c2;
    int row, col;
    int curR, curC, curNum;
    int left, max, mode, maxDigits;
    int **BOARD;
    
    scanf("%d %d %d %d", &r1, &c1, &r2, &c2);    
    row = r2 - r1 + 1;
    col = c2 - c1 + 1;
    BOARD = (int**)malloc(sizeof(int*)*row);
    for(i = 0; i < row; i++) BOARD[i] = (int*)malloc(sizeof(int)*col);
    left = row * col;

    curNum = 1;
    curR = 0; curC = 0;
    mode = MODE_R;
    while(left){
        if(IN_RANGE(curR, curC)){
            BOARD[curR-r1][curC-c1] = curNum;
            max = curNum;
            left--;
        }
        if(curC > 0){
            if(curC == -curR) mode = MODE_L;
            if(curC == curR + 1) mode = MODE_U;
        }
        else if (curC < 0){
            if(curC == curR) mode = MODE_D;
            if(curC == -curR) mode = MODE_R;
        }
        curR += R_MOD[mode];
        curC += C_MOD[mode];
        curNum++;
    }

    for(maxDigits = 0; max; maxDigits++, max /= 10);
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            printf("%*d ", maxDigits, BOARD[i][j]);
        }
        printf("\n");
    }
    
    
    // free    
    for(i = 0; i < row; i++) free(BOARD[i]);
    free(BOARD);

    return 0;
}