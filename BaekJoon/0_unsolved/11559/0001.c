#include <stdio.h>
#include <string.h>

#define ROW 12
#define COL 6

typedef struct NODE{
    char color;
    int  count;
} node;

int main(void){
    int  i, j, k, col, row;
    int  curCount;
    char inputLine[7];
    node field[ROW][COL];
    int  numArr[ROW][COL];
    char curColor, matchingColor;
    node rowNodes[COL];
    int  cntStart;
 
    for(i = 0; i < ROW; i++) {
        scanf("%s", inputLine);
        for(j = 0; j < COL; j++) {
            field[i][j].color = inputLine[j];
            field[i][j].count = 0;
        }
    }
    
    // Make useful Info.
    for(col = 0; col < COL; col++){
        curCount = 0;
        matchingColor = '.';
        cntStart = 0;
        for(row = 0; row < ROW; row++){
            if((curColor = field[row][col].color) == '.') continue;
            
            if(curCount == 0) {                        
                cntStart = row;
                matchingColor = curColor;
                curCount = 1;
                continue;
            }

            if(curColor == matchingColor) curCount++;
            else { 
                while(cntStart < row) field[cntStart++][col].count = curCount;
                cntStart = row;
                matchingColor = curColor;
                curCount = 1;
            }
        }
        while(cntStart < row) field[cntStart++][col].count = curCount;
        
    }

    // while Start
    // - Check Bomb
    for(row = ROW-1; row >= 0; row--){
        for(col = 0; col < COL; col++) rowNodes[col].color = field[row][col].color;
        
        col = 0;
        while(rowNodes[col].color == '.') col++;
        curColor = rowNodes[col].color;
        curCount = rowNodes[col].count;
        cntStart = col;
        for(col = cntStart+1; col < COL; col++){
            
            if(curColor == rowNodes[col].color){
                curCount += rowNodes[col].count;                
            }
        }
        
    }
    // - Field Arrange
    // Check each Column from bottom if there is "." before Puyo

    // while End

    for(row = 0; row < ROW; row++){
        for(col = 0; col < COL; col++)
            printf("%d", field[row][col].count);
        printf("\n");
    }
        printf("\n");

    return 0;
}