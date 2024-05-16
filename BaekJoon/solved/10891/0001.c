#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE{
    int num;
    struct _NODE *next;
} NODE;

NODE *g_adjList;
int g_count, *g_update;

int dfs(int curNum, int prevNum){
    int nextNum, curCount, childRoot;
    NODE *curNode;

    curCount = ++g_count;
    g_adjList[curNum].num = curCount;

    g_update[curNum] = 0;
    curNode = &g_adjList[curNum];
    while(curNode->next){
        nextNum = curNode->next->num;
        if(nextNum != prevNum){
            if(g_adjList[nextNum].num == 0) {
                if((childRoot = dfs(nextNum, curNum)) == -1) return -1;
            }
            else {
                childRoot = g_adjList[nextNum].num;
                g_update[nextNum]--;    // g_update[nextNum] will be updated later
            }
            if(childRoot < g_adjList[curNum].num) g_adjList[curNum].num = childRoot;    
            if(childRoot <= curCount) g_update[curNum]++;;
            if(g_update[curNum] > 1) return -1;
        }
        curNode = curNode->next;
    }

    return g_adjList[curNum].num;
}

int main(void){
    int i;
    int N, M;
    int a, b;
    NODE *newNode;

    scanf("%d %d", &N, &M);
    g_adjList = (NODE*)malloc(sizeof(NODE)*N);
    g_update = (int*)malloc(sizeof(int)*N);
    for(i = 0; i < N; i++) {
        g_adjList[i].num = 0;
        g_adjList[i].next = NULL;
    }

    for(i = 0; i < M; i++){
        scanf("%d %d", &a, &b);
        a--; b--;

        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->num = a;
        newNode->next = g_adjList[b].next;
        g_adjList[b].next = newNode;

        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->num = b;
        newNode->next = g_adjList[a].next;
        g_adjList[a].next = newNode;
    }

    g_count = 0;
    if(dfs(0, -1) == -1) printf("Not cactus\n");
    else printf("Cactus\n");

    // free should be here..

    return 0;
}