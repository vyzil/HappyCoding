#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE{
    int dst;
    struct _NODE *next;
} NODE;


int main(void) {
    int i;
    int N;
    NODE *adjList;
    NODE *newNode, *curNode, *delNode;
    int *order, *parent, prevPOrder;
    int u, v, curNum;
    scanf("%d", &N);

    adjList = (NODE*)malloc(sizeof(NODE)*(N+1));
    order = (int*)malloc(sizeof(int)*(N+1));
    parent = (int*)malloc(sizeof(int)*(N+1));
    for(i = 1; i <= N; i++) {
        adjList[i].next = NULL;
        parent[i] = -1;
        order[i] = -1;
    }
    for(i = 1; i <= N-1; i++){
        scanf("%d %d", &u, &v);
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->dst = v;
        newNode->next = adjList[u].next;
        adjList[u].next = newNode;
        
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->dst = u;
        newNode->next = adjList[v].next;
        adjList[v].next = newNode;
    }

    curNum = 0;
    scanf("%d", &u);
    if(u != 1) {
        printf("0\n");
        goto finale;
    }
    order[u] = curNum++;
    curNode = &adjList[u];
    while(curNode->next){
        v = curNode->next->dst;
        parent[v] = u;
        curNode = curNode->next;
    }
    prevPOrder = -1;

    for(i = 1; i < N; i++){
        scanf("%d", &u);
        if(parent[u] == -1 || order[parent[u]] < prevPOrder){
            printf("0\n");
            goto finale;
        }
        order[u] = curNum++;
        curNode = &adjList[u];
        while(curNode->next){
            v = curNode->next->dst;
            if(parent[v] == -1) parent[v] = u;
            curNode = curNode->next;
        }
        prevPOrder = order[parent[u]];
    }

    printf("1\n");

finale:
    for(i = 1; i <= N; i++){
        curNode = adjList[i].next;
        while(curNode){
            delNode = curNode;
            curNode = curNode->next;
            free(delNode);
        }
    }
    free(adjList);
    free(order);
    free(parent);

    return 0;
}