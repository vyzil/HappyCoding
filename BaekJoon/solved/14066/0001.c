#include <stdio.h>
#include <stdlib.h>

char BLOCK[6][7] = 
{
    "..+---+",
    "./   /|",
    "+---+ |",
    "|   | +",
    "|   |/.",
    "+---+..",
};

void makeBlock(char** board, int r, int c){
    int i, j;

    r -= 5;
    for(i = 0; i < 6; i++){
        for(j = 0; j < 7; j++){
            if(BLOCK[i][j] == '.') continue;
            board[r+i][c+j] = BLOCK[i][j];
        }
    }
    return;
}

int main(void){
    int i, j, k;
    int iM, iN;
    int bRow, bCol;
    int curR, curC;
    int **blocks;
    char **board;

    scanf("%d %d", &iM, &iN);
    blocks = (int**)malloc(sizeof(int*)*iM);
    bCol = iN * 4 + 3 + (iM - 1)* 2;
    bRow = 0;
    for(i = 0; i < iM; i++){
        blocks[i] = (int*)malloc(sizeof(int)*iN);
        for(j = 0; j < iN; j++){
            scanf("%d", &blocks[i][j]);
            if( (iM-1-i) * 2 + (blocks[i][j]+1)*3> bRow) bRow = (iM-1-i) * 2 + (blocks[i][j]+1)*3;
        }
    }
    

    printf("%d %d\n", bRow, bCol);
    board = (char**)malloc(sizeof(char*)*bRow);
    for(i = 0; i < bRow; i++){
        board[i] = (char*)malloc(sizeof(char)*(bCol+2));
        for(j = 0; j < bCol; j++) board[i][j] = '.';
        board[i][bCol]   = '\n';
        board[i][bCol+1] = '\0';
    }

    for(i = 0; i < iM; i++){
        for(j = 0; j < iN; j++){
            curR = bRow-1 - 2 * (iM - 1 - i);
            curC = 0 + 2 * (iM - 1 - i) + 4 * j;
            for(k = 0; k < blocks[i][j]; k++){
                printf("%d %d %d, (%d, %d)\n", i, j, k, curR - 3 * k, curC);
                makeBlock(board, curR - 3* k, curC);
            }
        }
    }

    for(i = 0; i < bRow; i++) printf("%s", board[i]);

    for(i = 0; i < bRow; i++) free(board[i]);
    free(board);

    return 0;
}