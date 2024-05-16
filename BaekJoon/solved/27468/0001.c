#include <stdio.h>
#include <stdlib.h> 

#define N_MAX 100000
#define false 0
#define true 1

typedef struct _NODE{
    int num;
    struct _NODE *next;
} NODE;

int checkList[N_MAX];
NODE* g_adjList;

int dfs(int x){
    int i;
    int y, find, dfs_res, childNum;
    NODE* curNode;

    if(checkList[x] == true) return false;
    checkList[x] = true;

    curNode = &g_adjList[x];
    childNum = 0;
    while(curNode->next){
        if(checkList[curNode->next->num] == false) childNum++;
        curNode = curNode->next;
    }
    if(childNum == 0) return true;

    while(g_adjList[x].num){
        scanf("%d", &y);
        y--;
        childNum = 0;
        find = false;
        curNode = &g_adjList[x];
        while(curNode->next){
            // printf("asd => %d: %d %d\n", x+1, curNode->next->num + 1, y + 1);
            if(curNode->next->num == y && checkList[y] == false){
                find = true;
                break;
            }
            curNode = curNode->next;
        }
        if(find == true) {
            g_adjList[x].num--;
            g_adjList[y].num--;
            if(dfs(y) == false) return false;
        }
        else return false;
    }

    return true;
}

int main(void){
    int i;
    int N, src, dst;
    NODE *newNode;

    scanf("%d", &N);
    g_adjList = (NODE*)malloc(sizeof(NODE)*N);
    for(i = 0; i < N; i++) {
        g_adjList[i].num = 0;
        g_adjList[i].next = NULL;
        checkList[i] = false;
    }
    
    for(i = 0; i < N-1; i++){
        scanf("%d %d", &src, &dst);
        src--; dst--;
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->num = dst;
        newNode->next = g_adjList[src].next;
        g_adjList[src].next = newNode;
        g_adjList[src].num++;
        
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->num = src;
        newNode->next = g_adjList[dst].next;
        g_adjList[dst].next = newNode;
        g_adjList[dst].num++;

    }
    scanf("%d", &i);
    i--;
    if(i == 0) printf("%d\n", dfs(i));
    else printf("0\n");

    return 0;
}