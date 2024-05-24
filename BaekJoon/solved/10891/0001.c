#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE{
    int num;
    struct _NODE *next;
} NODE;

NODE *adjList;
int g_count, *g_update;

int dfs(int curNum, int prevNum){
    int nextNum, curCount, childRoot;
    NODE *curNode;

    curCount = ++g_count;
    adjList[curNum].num = curCount;

    g_update[curNum] = 0;
    curNode = &adjList[curNum];
    while(curNode->next){
        nextNum = curNode->next->num;
        if(nextNum != prevNum){
            if(adjList[nextNum].num == 0) {
                if((childRoot = dfs(nextNum, curNum)) == -1) return -1;
            }
            else {
                childRoot = adjList[nextNum].num;
                g_update[nextNum]--;    // g_update[nextNum] will be updated later
            }
            if(childRoot < adjList[curNum].num) adjList[curNum].num = childRoot;    
            if(childRoot <= curCount) g_update[curNum]++;;
            if(g_update[curNum] > 1) return -1;
        }
        curNode = curNode->next;
    }

    return adjList[curNum].num;
}

int main(void){
    int i;
    int N, M;
    int a, b;
    NODE *newNode;

    scanf("%d %d", &N, &M);
    adjList = (NODE*)malloc(sizeof(NODE)*N);
    g_update = (int*)malloc(sizeof(int)*N);
    for(i = 0; i < N; i++) {
        adjList[i].num = 0;
        adjList[i].next = NULL;
    }

    for(i = 0; i < M; i++){
        scanf("%d %d", &a, &b);
        a--; b--;

        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->num = a;
        newNode->next = adjList[b].next;
        adjList[b].next = newNode;

        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->num = b;
        newNode->next = adjList[a].next;
        adjList[a].next = newNode;
    }

    g_count = 0;
    if(dfs(0, -1) == -1) printf("Not cactus\n");
    else printf("Cactus\n");

    // free should be here..

    return 0;
}