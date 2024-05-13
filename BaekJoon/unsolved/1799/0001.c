#include <stdio.h>
#include <stdlib.h>

/*
 *   0  1  2  3  4  5  6  7  8
 *   -  -  -  -  x  -  -  -  - 0
 *   -  -  -  x  -  x  -  -  - 1
 *   -  -  x  -  x  -  x  -  - 2
 *   -  x  -  x  -  x  -  x  - 3
 *   x  -  x  -  x  -  x  -  x 4
 *   -  x  -  x  -  x  -  x  - 5
 *   -  -  x  -  x  -  x  -  - 6
 *   -  -  -  x  -  x  -  -  - 7
 *   -  -  -  -  x  -  -  -  - 8
 *    (i, j) => (i-j+N, i+j)
 *  
 */

int main(void){
    int i, j, row, col;
    int iSize, iNum;
    int **iBoard, boardSize;

    scanf("%d", &iSize);

    boardSize = 2*iSize - 1;

    iBoard = (int**)malloc(sizeof(int*)*boardSize);
    for(i = 0; i < boardSize; i++){
        iBoard[i] = (int*)malloc(sizeof(int)*boardSize);
        for(j = 0; j < boardSize; j++) iBoard[i][j] = 1;
    }

    for(i = 0; i < iSize; i++){
        for(j = 0; j < iSize; j++){            
            scanf("%d", &iNum);
            if(iNum == 0) iBoard[i - j + iSize][i + j] = 0;
        }
    }

    return 0;
}