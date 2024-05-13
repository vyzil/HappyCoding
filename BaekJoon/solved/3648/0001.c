#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MAX 2*(1000+1)
#define NOT(x, n) (2*(n) - (x))

typedef struct _NODE{
    int idx;
    struct _NODE *next;
} NODE;

int global_stack[N_MAX];
int global_stackTop;
int global_check[N_MAX];

int dfs(NODE* graph, int size, int num){
    int _id;
    int childRoot;
    NODE *curNode;
    
    global_stackTop++;
    global_stack[global_stackTop] = num;
    _id = global_stackTop + 1;
    graph[num].idx = _id;
    curNode = &graph[num];

    while(curNode->next){
        childRoot = graph[curNode->next->idx].idx;
        if(childRoot == 0) childRoot = dfs(graph, size, curNode->next->idx);
        if(childRoot < graph[num].idx) graph[num].idx = childRoot;
        if(graph[num].idx == -1) return -1;
        curNode = curNode->next;
    }

    if(graph[num].idx == _id){
        memset(global_check, 0, sizeof(int)*N_MAX);
        while(_id <= global_stackTop + 1){
            if(global_check[NOT(global_stack[global_stackTop], size)] == 1) return -1;
            global_check[global_stack[global_stackTop]] = 1;
            graph[global_stack[global_stackTop]].idx = N_MAX;
            global_stackTop--;
        }
        return _id;
    }

    return graph[num].idx;
}

int findNonVisit(NODE *graph, int iN){
    int i;
    for(i = 0; i < 2*(iN+1); i++){
        if (graph[i].idx == 0) break;
    }
    return i;
}

// [ (0, 1, ..., iN-1) , iN, (iN+1, iN+2, ... 2*iN) , 2*iN + 1]
// [(-iN ~ -1) , x , (1 ~ iN), x] + iN = index
// not operation = (2*iN - x)
void solve(int iN, int iM){
    int i;
    int iA, iB;
    int res;
    NODE *graph, *newNode, *freeNode;

    graph = (NODE*)malloc(sizeof(NODE)*2*(iN + 1));   // +, -
    for(i = 0; i < 2*(iN+1); i++) {
        graph[i].idx = 0;
        graph[i].next = NULL;
    }
    for(i = 0; i < iM; i++){
        scanf("%d %d", &iA, &iB);
        iA += iN; iB += iN;
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->idx = iB;
        newNode->next = graph[NOT(iA, iN)].next;
        graph[NOT(iA, iN)].next = newNode;
        
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->idx = iA;
        newNode->next = graph[NOT(iB, iN)].next;
        graph[NOT(iB, iN)].next = newNode;
    }
    
    iA = 1 + iN;
    iB = 1 + iN;
    newNode = (NODE*)malloc(sizeof(NODE));
    newNode->idx = iB;
    newNode->next = graph[NOT(iA, iN)].next;
    graph[NOT(iA, iN)].next = newNode;
    graph[iN].idx = iN;
    graph[2*iN+1].idx = iN;
    
    global_stackTop = -1;
    while((i = findNonVisit(graph, iN)) < 2*(iN+1)) {
        if((res = dfs(graph, iN, i)) == -1) break;
    }

    if (res == -1) printf("no\n");
    else printf("yes\n");
    
    // free
    for(i = 0; i < 2*(iN+1); i++){
        newNode = graph[i].next;
        while(newNode){
            freeNode = newNode;
            newNode = newNode->next;
            free(freeNode);
        }
    }
    free(graph);

    return;
}

int main(void){
    int iN, iM;

    while(scanf("%d %d", &iN, &iM) != EOF) solve(iN, iM);

    return 0;
}