#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _WINDOW{
    char title[11];
    int tStart;
    int sR, sC;
    int eR, eC;
    struct _WINDOW *next;
} WINDOW;



int main(void){
    int i, j, k;
    int R, C;
    char g_board[101][101];
    WINDOW *winList, * curWin, *newWin; int tmpR, tmpC, curIdx;

    scanf("%d %d", &R, &C);
    for(i = 0 ; i < R; i++) scanf("%s", g_board[i]);
    winList = (WINDOW*)malloc(sizeof(WINDOW));
    winList->next = NULL;

    for(i = 0; i < R; i++){
        for(j = 0; j < C; j++){
            if(g_board[i][j] != '+') continue;
            // make window and add to winList
            // - collect sR sC
            tmpR = i; tmpC = j;
            newWin = (WINDOW*)malloc(sizeof(WINDOW));
            newWin->sR = tmpR; newWin->sC = tmpC;

            // - collect title
            while(g_board[tmpR][tmpC] != '|') tmpC++;
            newWin->tStart = tmpC;
            tmpC++;
            for(k = 0; g_board[tmpR][tmpC] != '|'; k++, tmpC++) newWin->title[k] = g_board[tmpR][tmpC];
            newWin->title[k] = '\0';

            // - collect eR eC
            while(g_board[tmpR][tmpC] != '+') tmpC++;
            tmpR++;
            while(g_board[tmpR][tmpC] != '+') tmpR++;
            newWin->eR = tmpR; newWin->eC = tmpC;

            // - remove + 
            g_board[newWin->sR][newWin->sC] = '.';
            g_board[newWin->sR][newWin->eC] = '.';
            g_board[newWin->eR][newWin->sC] = '.';
            g_board[newWin->eR][newWin->eC] = '.';

            // add to List with sort
            curWin = winList;
            while(curWin->next){
                if(strcmp(curWin->next->title, newWin->title) > 0) break;
                if(curWin->next) curWin = curWin->next;   
                else break;
            }
            newWin->next = curWin->next;
            curWin->next = newWin;
        }
    }

    // curWin = winList;
    // while(curWin->next){
    //     printf("%s\n", curWin->next->title);
    //     curWin = curWin->next;
    // }
    
    for(i = 0; i < R; i++){
        for(j = 0; j < C; j++) g_board[i][j] = '.';
    }


    curWin = winList;
    curIdx = 0;
    while(curWin->next){
        curWin = curWin->next;
        tmpR = curWin->sR; tmpC = curWin->sC;
        tmpR -= curIdx; tmpC -= curIdx;
        curWin->tStart -= tmpC;
        curWin->sR -= tmpR; curWin->sC -= tmpC;
        curWin->eR -= tmpR; curWin->eC -= tmpC;     

        for(i = curWin->sC; i < curWin->tStart; i++) g_board[curWin->sR][i] = '-';
        g_board[curWin->sR][i++] = '|';
        for(j = 0; curWin->title[j]; j++, i++) g_board[curWin->sR][i] = curWin->title[j];
        g_board[curWin->sR][i++] = '|';
        for(; i < curWin->eC; i++) g_board[curWin->sR][i] = '-';
        for(i = curWin->sR + 1; i < curWin->eR; i++){
            j = curWin->sC;
            g_board[i][j] = '|';
            for(j++; j < curWin->eC; j++) g_board[i][j] = '.';
            g_board[i][j] = '|';
        }
        for(j = curWin->sC; j <= curWin->eC; j++) g_board[i][j] = '-';
        
        g_board[curWin->sR][curWin->sC] = '+';
        g_board[curWin->sR][curWin->eC] = '+';
        g_board[curWin->eR][curWin->sC] = '+';
        g_board[curWin->eR][curWin->eC] = '+';

        curIdx++;
    }

    for(i = 0; i < R; i++){
        for(j = 0; j < C; j++) printf("%c", g_board[i][j]);
        printf("\n");
    }

    return 0;
}