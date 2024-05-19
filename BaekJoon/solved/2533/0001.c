#include <stdio.h>
#include <stdlib.h>

#define YES 1
#define NO  0
#define ROOT_NUM 0

#define MIN(x, y) ((x) < (y) ? (x) : (y))

typedef struct _NODE{
    int num;
    struct _NODE *next;
} NODE;

NODE *adjList;
int *g_queue, g_qStart, g_qEnd;
int *DP[2];

int main(void){
    int i;
    int N, u, v;
    int curIdx;
    NODE *newNode, *curNode, *delNode;

    scanf("%d", &N);
    adjList = (NODE*)malloc(sizeof(NODE)*N);
    DP[YES] = (int*)malloc(sizeof(int)*N);
    DP[NO]  = (int*)malloc(sizeof(int)*N);
    for(i = 0; i < N; i++) {
        adjList[i].num = 0;
        adjList[i].next = NULL;
        DP[YES][i] = 1;
        DP[NO ][i] = 0;
    }

    // Make adjList
    for(i = 0; i < N-1; i++){
        scanf("%d %d", &u, &v);
        u--; v--;
        
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->num = u;
        newNode->next = adjList[v].next;
        adjList[v].next = newNode;
        adjList[v].num++;

        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->num = v;
        newNode->next = adjList[u].next;
        adjList[u].next = newNode;
        adjList[u].num++;
    }

    adjList[ROOT_NUM].num++;

    // num == 1 to Queue
    g_queue = (int*)malloc(sizeof(int)*N);
    g_qStart = 0;
    g_qEnd = -1;
    for(i = 0; i < N; i++){
        if(adjList[i].num == 1) g_queue[++g_qEnd] = i;
    }

    // while(sth in Q) ~
    while(g_qStart <= g_qEnd){
        curIdx = g_queue[g_qStart++];

        // connected Node search
        curNode = &adjList[curIdx];
        while(curNode->next){
            // I think I can optimize searching.. (delete child or memorize parent or sth..)
            if(adjList[curNode->next->num].num != 0) {
                DP[YES][curNode->next->num] += MIN(DP[YES][curIdx], DP[NO][curIdx]);
                DP[NO ][curNode->next->num] += DP[YES][curIdx];
                if(--(adjList[curNode->next->num].num) == 1) g_queue[++g_qEnd] = curNode->next->num;
                break;
            }
            curNode = curNode->next;
        }

        adjList[curIdx].num--;
    }

    // print min value fo root DP
    printf("%d\n", MIN(DP[YES][ROOT_NUM], DP[NO][ROOT_NUM]));

    // free
    for(i = 0; i < N; i++) {
        delNode = adjList[i].next;
        while(delNode){ 
            curNode = delNode->next;
            free(delNode);
            delNode = curNode;
        }
    }
    free(adjList);
    free(DP[YES]);
    free(DP[NO]);

    return 0;
}