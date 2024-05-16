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
    int height;
} TREE;

NODE *g_adjList;
TREE *g_tree;

void makeTree(int n, int h){
    NODE *curNode;

    g_tree[n].height = h;
    curNode = &g_adjList[n];
    while(curNode->next){
        if(g_tree[curNode->next->num].height == 0) {
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
        if(g_tree[aRoot].height < g_tree[bRoot].height){
            res += g_tree[bRoot].dist;
            bRoot = g_tree[bRoot].parent;
        }
        else if(g_tree[aRoot].height > g_tree[bRoot].height){
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
    g_adjList = (NODE*)malloc(sizeof(NODE)*N);
    g_tree = (TREE*)malloc(sizeof(TREE)*N);

    for(i = 0; i < N; i++) {
        g_adjList[i].next = NULL;
        g_tree[i].height = 0;
    }
    for(i = 0; i < N-1; i++){
        scanf("%d %d %d", &a, &b, &c);
        a--; b--;

        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->num = b;
        newNode->dist = c;
        newNode->next = g_adjList[a].next;
        g_adjList[a].next = newNode;
        
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->num = a;
        newNode->dist = c;
        newNode->next = g_adjList[b].next;
        g_adjList[b].next = newNode;
    }

    makeTree(0, 1);
    free(g_adjList);

    scanf("%d", &M);
    for(i = 0; i < M; i++) {
        scanf("%d %d", &a, &b);
        printf("%d\n", distance(a-1, b-1));
    }

    free(g_tree);
    return 0;
}