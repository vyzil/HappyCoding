#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VALUE 1000000

typedef struct POINT{
    int x;
    int y;
    struct POINT *next;
} point;

point* insertQueue(point *qTail, int X, int Y){
    qTail->next = (point*)malloc(sizeof(point));
    qTail->next->x = X;
    qTail->next->y = Y;
    qTail->next->next = NULL;
    qTail = qTail->next;      
    return qTail;
}

void indexMap(int** indexMap, int startX, int startY, int maxX, int maxY){
    int curX, curY, curIdx;
    point *qHead, *qTail, *tmpPoint;
    
    indexMap[startX][startY] = 1;
    qHead = (point*)malloc(sizeof(point));
    qTail = qHead;
    qTail->x = startX; 
    qTail->y = startY;
    qTail->next = NULL;
    while(qHead){
        curX = qHead->x;
        curY = qHead->y;
        curIdx = indexMap[curX][curY];
        if (curY-1 >= 0 && indexMap[curX][curY-1] > curIdx + 1) {
            indexMap[curX][curY-1] = curIdx + 1;
            qTail = insertQueue(qTail, curX, curY-1);
        }
        if (curY+1 <= maxY && indexMap[curX][curY+1] > curIdx + 1) {
            indexMap[curX][curY+1] = curIdx + 1;
            qTail = insertQueue(qTail, curX, curY+1);
        }
        if (curX-1 >= 0 && indexMap[curX-1][curY] > curIdx + 1) {
            indexMap[curX-1][curY] = curIdx + 1;
            qTail = insertQueue(qTail, curX-1, curY);
        }
        if (curX+1 <= maxX && indexMap[curX+1][curY] > curIdx + 1) {
            indexMap[curX+1][curY] = curIdx + 1;
            qTail = insertQueue(qTail, curX+1, curY);
        }

        tmpPoint = qHead;
        qHead = qHead->next;
        free(tmpPoint);
    }
}

int main(void){
    int i, j;
    int iN, iM, iV;
    int **forwardMap, **reverseMap;
    char *inputStr;
    int min, fLocalMin, rLocalMin;
    // point *qHead, *qTail, *tmpPoint;
    // int curX, curY, curIdx;

    scanf("%d %d", &iN, &iM);

    forwardMap = (int**)malloc(sizeof(int*)*iN);
    reverseMap = (int**)malloc(sizeof(int*)*iN);
    for(i = 0; i <iN; i++) {
        forwardMap[i] = (int*)malloc(sizeof(int)*iM);
        reverseMap[i] = (int*)malloc(sizeof(int)*iM);
    }

    inputStr = (char*)malloc(iM+1);
    for(i = 0; i <iN; i++){
        scanf("%s", inputStr);
        for(j = 0; j < iM; j++){
            iV = inputStr[j] - '0';
            forwardMap[i][j] = (1 - iV) * MAX_VALUE;    // empty : MAX_VALUE , wall : 0
            reverseMap[i][j] = (1 - iV) * MAX_VALUE;    // empty : MAX_VALUE , wall : 0
        }
    }

    // BFS map indexing
    indexMap(forwardMap, 0, 0, iN-1, iM-1);
    indexMap(reverseMap, iN-1, iM-1, iN-1, iM-1);

    // Map Compare & find Min
    min = reverseMap[0][0];
    
    for(i = 0; i < iN; i++){
        for(j = 0; j < iM; j++){
            if(forwardMap[i][j] != 0) continue;
            fLocalMin = MAX_VALUE;
            if (i-1 >= 0 && forwardMap[i-1][j] != 0 && forwardMap[i-1][j] < fLocalMin) fLocalMin = forwardMap[i-1][j];
            if (i+1 < iN && forwardMap[i+1][j] != 0 && forwardMap[i+1][j] < fLocalMin) fLocalMin = forwardMap[i+1][j];
            if (j-1 >= 0 && forwardMap[i][j-1] != 0 && forwardMap[i][j-1] < fLocalMin) fLocalMin = forwardMap[i][j-1];
            if (j+1 < iM && forwardMap[i][j+1] != 0 && forwardMap[i][j+1] < fLocalMin) fLocalMin = forwardMap[i][j+1];

            
            rLocalMin = MAX_VALUE;
            if (i-1 >= 0 && reverseMap[i-1][j] != 0 && reverseMap[i-1][j] < rLocalMin) rLocalMin = reverseMap[i-1][j];
            if (i+1 < iN && reverseMap[i+1][j] != 0 && reverseMap[i+1][j] < rLocalMin) rLocalMin = reverseMap[i+1][j];
            if (j-1 >= 0 && reverseMap[i][j-1] != 0 && reverseMap[i][j-1] < rLocalMin) rLocalMin = reverseMap[i][j-1];
            if (j+1 < iM && reverseMap[i][j+1] != 0 && reverseMap[i][j+1] < rLocalMin) rLocalMin = reverseMap[i][j+1];
            
            if(min > fLocalMin + rLocalMin + 1) min = fLocalMin + rLocalMin + 1;
        }
    }

    if(min == MAX_VALUE) min = -1;
    printf("%d\n", min);

    // free
    // for(i = 0; i <iM; i++) free(map[i]);
    // free(map);
    
    return 0;
}