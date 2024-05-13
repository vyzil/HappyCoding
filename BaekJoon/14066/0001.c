#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i, j;
    int iM, iN;
    int row, col;
    char **board;

    scanf("%d %d", &iM, &iN);
    
    board = (char**)malloc(sizeof(char*)*row);
    for(i = 0; i < row; i++){
        board[i] = (char*)malloc(sizeof(char)*(col+2));
        for(j = 0; j < col; j++) board[i][j] = '.';
        board[i][col]   = '\n';
        board[i][col+1] = '\0';
    }


    for(i = 0; i < row; i++) printf("%s", board[i]);

    for(i = 0; i < row; i++) free(board[i]);
    free(board);

    return 0;
}