#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE{
    int num;
    int dist;
    struct _NODE *next;
} NODE;

typedef struct _TREE{
    int parent;
    int dist;
    int depth;
} TREE;

NODE *adjList;
TREE *g_tree;

void makeTree(int n, int h){
    NODE *curNode;

    g_tree[n].depth = h;
    curNode = &adjList[n];
    while(curNode->next){
        if(g_tree[curNode->next->num].depth == 0) {
            g_tree[curNode->next->num].parent = n;
            g_tree[curNode->next->num].dist = curNode->next->dist;
            makeTree(curNode->next->num, h+1);
        }
        curNode = curNode->next;
    }

    return;
}

int distance(int a, int b){
    int aRoot, bRoot;
    int res;

    res = 0;
    aRoot = a; bRoot = b;
   
    while(aRoot != bRoot){
        if(g_tree[aRoot].depth < g_tree[bRoot].depth){
            res += g_tree[bRoot].dist;
            bRoot = g_tree[bRoot].parent;
        }
        else if(g_tree[aRoot].depth > g_tree[bRoot].depth){
            res += g_tree[aRoot].dist;
            aRoot = g_tree[aRoot].parent;
        }
        else { // g_tree[aRoot].height == g_tree[bRoot].height
            res += g_tree[aRoot].dist;
            res += g_tree[bRoot].dist;
            aRoot = g_tree[aRoot].parent;
            bRoot = g_tree[bRoot].parent;
        }
    }

    return res; 
}

int main(void){
    int i;
    int N, M;
    int a, b, c;
    NODE *newNode;

    scanf("%d", &N);
    adjList = (NODE*)malloc(sizeof(NODE)*N);
    g_tree = (TREE*)malloc(sizeof(TREE)*N);

    for(i = 0; i < N; i++) {
        adjList[i].next = NULL;
        g_tree[i].depth = 0;
    }
    for(i = 0; i < N-1; i++){
        scanf("%d %d %d", &a, &b, &c);
        a--; b--;

        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->num = b;
        newNode->dist = c;
        newNode->next = adjList[a].next;
        adjList[a].next = newNode;
        
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->num = a;
        newNode->dist = c;
        newNode->next = adjList[b].next;
        adjList[b].next = newNode;
    }

    makeTree(0, 1);
    free(adjList);

    scanf("%d", &M);
    for(i = 0; i < M; i++) {
        scanf("%d %d", &a, &b);
        printf("%d\n", distance(a-1, b-1));
    }

    free(g_tree);
    return 0;
}