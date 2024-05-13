#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ABLEWALL 3

int findEmpty(int** map, int mapRow, int mapCol, int wallCount, int emptyMax){
    int row, col, vRow, vCol;
    int emptySpace;
    int virusCount; // only counts new virus
    int *virusQ, vQFirst, vQLast;

    virusCount = 0;
    emptySpace = mapRow * mapCol - wallCount;
    virusQ = (int*)malloc(sizeof(int)*emptySpace*4);    // mult 4, when one is deleted maximum 4 can be added
    vQFirst = 0; 
    vQLast = 0;
    for(row = 0; row < mapRow; row++){
        for(col = 0; col < mapCol; col++){
            if(map[row][col] != 2) continue;
            // if Virus Detected, add to VirusQ
            virusQ[vQLast++] = row*mapCol + col;
            
            // If sth in VirusQ, Infection Start!
            while(vQFirst < vQLast){
                vRow = virusQ[vQFirst] / mapCol;
                vCol = virusQ[vQFirst] % mapCol;
                vQFirst++;
                
                if(map[vRow][vCol] == 3) continue;

                // Infect, if virus exceed limit, return with -1
                map[vRow][vCol] = 3;
                virusCount++;
                if(emptyMax > emptySpace - virusCount) {
                    free(virusQ);
                    return -1;
                }                
                
                // Top, Bottom, Left, Right
                if(vRow - 1 >= 0     && (map[vRow-1][vCol] == 0 || map[vRow-1][vCol] == 2)) virusQ[vQLast++] = (vRow - 1)*mapCol + vCol;
                if(vRow + 1 < mapRow && (map[vRow+1][vCol] == 0 || map[vRow+1][vCol] == 2)) virusQ[vQLast++] = (vRow + 1)*mapCol + vCol;
                if(vCol - 1 >= 0     && (map[vRow][vCol-1] == 0 || map[vRow][vCol-1] == 2)) virusQ[vQLast++] = vRow*mapCol + vCol - 1;
                if(vCol + 1 < mapCol && (map[vRow][vCol+1] == 0 || map[vRow][vCol+1] == 2)) virusQ[vQLast++] = vRow*mapCol + vCol + 1;
            }
        }
    }

    free(virusQ);
    return emptySpace - virusCount;
}

int main(void){
    int i, j, row, col, pos;
    int wallComb[ABLEWALL], wallIdx, wallCount;
    int mapRow, mapCol;
    int **baseMap, **curMap;
    int *emptyPos, emptyCount;
    int maxEmpty, curEmpty;
   
    scanf("%d %d", &mapRow, &mapCol);

    emptyCount = 0;
    wallCount = 0;
    baseMap = (int**)malloc(sizeof(int*)*mapRow);
    curMap  = (int**)malloc(sizeof(int*)*mapRow);
    for(i = 0; i < mapRow; i++){
        baseMap[i] = (int*)malloc(sizeof(int)*mapCol);
        curMap[i] = (int*)malloc(sizeof(int)*mapCol);
        for(j = 0; j < mapCol; j++) {
            scanf("%d", &baseMap[i][j]);
            if(baseMap[i][j] == 0) emptyCount++;
            if(baseMap[i][j] == 1) wallCount++;
        }
    }

    emptyPos = (int*)malloc(sizeof(int)*emptyCount);
    for(i = 0, pos = 0; pos < emptyCount; i++){
        row = i / mapCol;
        col = i % mapCol;
        if(baseMap[row][col] == 0) emptyPos[pos++] = i;
    }

    wallComb[0] = 0;
    wallComb[1] = 1;
    wallComb[2] = 1;    // start with 2 in while statement
    wallCount += 3;    

    maxEmpty = 0;
    while(1){
        // Find wall combination. If all combination tried, break
        wallIdx = ABLEWALL - 1;        
        while( (wallIdx >= 0) && !(++wallComb[wallIdx] < emptyCount - ((ABLEWALL - 1) - wallIdx))  ) wallIdx--;
        if(wallIdx < 0) break;
        while(++wallIdx < ABLEWALL) wallComb[wallIdx] = wallComb[wallIdx-1] + 1;
                
        // Place walls
        for(i = 0; i < mapRow; i++) memcpy(curMap[i], baseMap[i], sizeof(int)*mapCol);          // curMap initialize with baseMap
        for(i = 0; i < ABLEWALL; i++) curMap[emptyPos[wallComb[i]] / mapCol][emptyPos[wallComb[i]] % mapCol] = 1;   // palce three wall
        
        curEmpty = findEmpty(curMap, mapRow, mapCol, wallCount, maxEmpty);
        if(curEmpty > maxEmpty) maxEmpty = curEmpty;
    }

    printf("%d\n", maxEmpty);

    return 0;
}