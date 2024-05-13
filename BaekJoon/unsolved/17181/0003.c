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

    if(visited == -1) return -1;
    
    switch(state){
        case I_STATE:
            if(visited == 0 && gTable[r][c] == CON) res = F_STATE;
            if(visited == 0 && gTable[r][c] == VOW) res = N_STATE;
            break;
        case N_STATE:
            if(visited != I_STATE && gTable[r][c] == CON) res = I_STATE;
            break;
        case F_STATE:
            if(visited == 0 && gTable[r][c] == VOW) res = N_STATE;
            break;
        default:
    }
    return res;
}

// row, column, vowel count, state
int dfs(int r, int c, int count, int state){
    int nextState;
    int originalState;
    int res[4] = {-1, -1, -1, -1};

    // printf("(%d, %d), c = %d, s = %d\n", r, c, count, state);
    if(gTable[r][c] == VOW) count++;
    if(r == 0 && c == 0){
        if(state == I_STATE){
            if(gCount > count) gCount = count;
            else return -1;
        }
        return 0;
    }
    originalState = gVisited[r][c];
    gVisited[r][c] = state;

    if(c - 1 >= 0 && (nextState = checkNext(state, r, c-1)) > 0) res[0] = dfs(r, c-1, count, nextState);
    if(r - 1 >= 0 && (nextState = checkNext(state, r-1, c)) > 0) res[1] = dfs(r-1, c, count, nextState);
    if(c + 1 < iM && (nextState = checkNext(state, r, c+1)) > 0) res[2] = dfs(r, c+1, count, nextState);
    if(r + 1 < iN && (nextState = checkNext(state, r+1, c)) > 0) res[3] = dfs(r+1, c, count, nextState);

    if(res[0] + res[1] + res[2] + res[3] == -4) {
        originalState = -1;
        return -1;
    }

    gVisited[r][c] = originalState;
    return 0;
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
    if(gTable[iN-1][iM-1] == CON) dfs(iN-1, iM-1, 0, F_STATE);
    else dfs(iN-1, iM-1, 0, N_STATE);

    if(gCount == iN*iM) printf("BAD\n");
    else printf("%d\n", gCount);

    return 0;
}