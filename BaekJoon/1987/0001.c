#include <stdio.h>
#include <stdlib.h>

char **iBoard;
int iR, iC;

int DFS(int visited, int curR, int curC){
    int max, tmp;

    max = 0;
    if(curR - 1 >= 0 && (visited & (1 << (iBoard[curR-1][curC] - 'A'))) == 0) {
        tmp = DFS(visited | (1 << (iBoard[curR-1][curC] - 'A')), curR-1, curC);
        if(tmp > max) max = tmp;
    }
    if(curR + 1 < iR && (visited & (1 << (iBoard[curR+1][curC] - 'A'))) == 0) {
        tmp = DFS(visited | (1 << (iBoard[curR+1][curC] - 'A')), curR+1, curC);
        if(tmp > max) max = tmp;
    }
    if(curC - 1 >= 0 && (visited & (1 << (iBoard[curR][curC-1] - 'A'))) == 0) {
        tmp = DFS(visited | (1 << (iBoard[curR][curC-1] - 'A')), curR, curC-1);
        if(tmp > max) max = tmp;
    }
    if(curC + 1 < iC && (visited & (1 << (iBoard[curR][curC+1] - 'A'))) == 0) {
        tmp = DFS(visited | (1 << (iBoard[curR][curC+1] - 'A')), curR, curC+1);
        if(tmp > max) max = tmp;
    }

    if(max == 0){
        for(;visited > 0; visited >>= 1) {
            if(visited %2 == 1) max++;
        }
    }

    return max;
}


int main(void){
    int i, j;
    int curR, curC;
    
    scanf("%d %d", &iR, &iC);
    iBoard = (char**)malloc(sizeof(char*)*iR);

    for(i = 0; i < iR; i++){
        iBoard[i] = (char*)malloc(sizeof(char)*(iC+1));
        scanf("%s", iBoard[i]);
    }

    curR = 0;
    curC = 0;
    
    printf("%d\n", DFS(1 << (iBoard[curR][curC] - 'A'), curR, curC));


    return 0;
}