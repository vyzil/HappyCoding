#include <stdio.h>
#include <stdlib.h>

#define LOG_MAX 17  // log(100,000) = 16.xxx

typedef struct _NODE{
    int v;
    struct _NODE *next;
} NODE;

typedef struct _TREE{
    int depth;
    int ancestor[LOG_MAX+1];
} TREE;

int findAnc(TREE *tree, int num, int targetDepth){
    int dist, log2;
    int res;

    dist = tree[num].depth - targetDepth;
    for(log2 = 1; (1 << log2) < dist+1; log2++);
    log2--;

    res = num;
    while(dist > 0){
        if(dist & (1<<log2)) res = tree[res].ancestor[log2];
        dist ^= (1<<log2);
        log2--;
    }

    return res;
}

int findLCA(TREE *tree, int u, int v){
    int uDepth, vDepth, cnt;

    uDepth = tree[u].depth;
    vDepth = tree[v].depth;

    // match height
    if(vDepth > uDepth) v = findAnc(tree, v, uDepth);
    if(uDepth > vDepth) u = findAnc(tree, u, vDepth);
    // findLCA
    while(u != v){
        for(cnt = 0; (1 << cnt) < uDepth ; cnt++){
            if(tree[u].ancestor[cnt] == tree[v].ancestor[cnt]) break;
        }
        if(cnt > 1) cnt--;
        u = tree[u].ancestor[cnt];
        v = tree[v].ancestor[cnt];
        uDepth -= (1 << cnt);
    }

    return u;
};

void makeTree(NODE *adjList, TREE *tree, int num, int depth){
    int i, v, log2;
    NODE *curNode;

    tree[num].depth = depth;

    for(log2 = 1; (1 << log2) < depth; log2++){
        tree[num].ancestor[log2] = tree[(tree[num].ancestor[log2-1])].ancestor[log2-1];
    }
    tree[num].ancestor[log2] = -1;
    
    curNode = &adjList[num];
    while(curNode->next){
        v = curNode->next->v;
        if(tree[v].depth == 0) {
            tree[v].ancestor[0] = num;
            makeTree(adjList, tree, v, depth+1);
        }
        curNode = curNode->next;
    }

    return;
}

int main(void){
    int i;
    int N, M;
    int u, v;
    NODE *adjList, *newNode;
    TREE *tree;

    scanf("%d", &N);
    adjList = (NODE*)calloc(N, sizeof(NODE));
    for(i = 0; i < N-1; i++){
        scanf("%d %d", &u, &v);
        u--;v--;
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->v = v;
        newNode->next = adjList[u].next;
        adjList[u].next = newNode;
        
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->v = u;
        newNode->next = adjList[v].next;
        adjList[v].next = newNode;
    }

    tree = (TREE*)calloc(N, sizeof(TREE));
    tree[0].ancestor[0] = -1;
    makeTree(adjList, tree, 0, 1);
    free(adjList);

    scanf("%d", &M);
    for(i = 0; i < M; i++){
        scanf("%d %d", &u, &v);
        u--;v--;
        printf("%d\n", findLCA(tree, u, v) + 1);
    }
    free(tree);
    return 0;
}