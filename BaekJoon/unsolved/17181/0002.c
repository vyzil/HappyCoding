#include <stdio.h>
#include <stdlib.h>

#define CON_MAX 13
#define VOW_MAX 34
#define CON 1
#define VOW 2

// State
// 1 : 초성      [I]nitial Consonant
// 2 : 중성      [N]euter Consonant
// 3 : (초)종성  [F]inal Consonant
#define I_STATE 1
#define N_STATE 2
#define F_STATE 3

int iN, iM;
int **gVisited;
int **gTable;
int gCount;

int checkNext(int state, int r, int c){
    int res, visited;
    res = 0;
    visited = gVisited[r][c];

    switch(state){
        case I_STATE:
            if(visited == 0 && gTable[r][c] == VOW) res = N_STATE;
            break;
        case N_STATE:
            // if(visited != F_STATE && gTable[r][c] == CON) res = F_STATE;
            if(visited != F_STATE && gTable[r][c] == CON) res = F_STATE;
            break;
        case F_STATE:
            if(visited == 0 && gTable[r][c] == CON) res = I_STATE;
            if(visited == 0 && gTable[r][c] == VOW) res = N_STATE;
            break;
        default:
    }
    return res;
}

// row, column, vowel count, state
void dfs(int r, int c, int count, int state){
    int nextState;
    int originalState;
    
    // printf("(%d, %d), c = %d, s = %d\n", r, c, count, state);
    if(gTable[r][c] == VOW) count++;
    if(r == iN-1 && c == iM-1){
        if(state != I_STATE){
            if(gCount > count) gCount = count;            
        }
        return;
    }
    originalState = gVisited[r][c];
    gVisited[r][c] = state;
    if(c + 1 < iM && (nextState = checkNext(state, r, c+1)) > 0) dfs(r, c+1, count, nextState);
    if(r + 1 < iN && (nextState = checkNext(state, r+1, c)) > 0) dfs(r+1, c, count, nextState);
    if(c - 1 >= 0 && (nextState = checkNext(state, r, c-1)) > 0) dfs(r, c-1, count, nextState);
    if(r - 1 >= 0 && (nextState = checkNext(state, r-1, c)) > 0) dfs(r-1, c, count, nextState);

    gVisited[r][c] = originalState;
    return;
}

int main(void){
    int i, j;
    int iTmp;

    scanf("%d %d", &iN, &iM);
    gTable = (int**)malloc(sizeof(int*)*iN);
    gVisited = (int**)malloc(sizeof(int*)*iN);
    for(i = 0; i < iN; i++){
        gTable[i] = (int*)malloc(sizeof(int)*iM);
        gVisited[i] = (int*)malloc(sizeof(int)*iM);
        for(j = 0; j < iM; j++){
            scanf("%d", &iTmp);
            if(iTmp > CON_MAX) gTable[i][j] = VOW;
            else gTable[i][j] = CON;
        }
    }

    gCount = iN * iM;
    dfs(0, 0, 0, I_STATE);

    if(gCount == iN*iM) printf("BAD\n");
    else printf("%d\n", gCount);

    return 0;
}