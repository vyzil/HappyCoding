#include <stdio.h>
#include <stdlib.h>


#define N_MAX 100000

typedef struct _NODE{
    int root;
    int height;
    int weight; 
} NODE;

int g_stack[N_MAX];
int g_stackTop;

int findRoot(NODE* ROOT, int num){
    int root;
    int curIdx, weightSum;

    g_stackTop = -1;
    curIdx = num;

    // find root while counting height
    while(ROOT[curIdx].root != curIdx) {
        g_stack[++g_stackTop] = curIdx;
        curIdx = ROOT[curIdx].root;
    }
    root = ROOT[curIdx].root;
    ROOT[root].height = g_stackTop + 1;

    // update passed nodes' root value to root
    weightSum = 0;
    while(g_stackTop >= 0){
        weightSum += ROOT[g_stack[g_stackTop]].weight;
        ROOT[g_stack[g_stackTop]].root = root;
        ROOT[g_stack[g_stackTop]].weight = weightSum;
        g_stackTop--;
    }

    return root;
}

int solve(int N, int M){
    int i;
    char query; int iA, iB, iW;
    NODE ROOT[N_MAX];
    int ARoot, BRoot, w_AR, w_BR;

    if((N || M) == 0) return 0;

    for(i = 0; i < N; i++) {
        ROOT[i].root = i;
        ROOT[i].height = 0;
        ROOT[i].weight = 0;
    }

    for(i = 0; i < M; i++){
        scanf("%s", &query);
        if(query == '!'){ // add
            scanf("%d %d %d", &iA, &iB, &iW);
            iA--; iB--;
            ARoot = findRoot(ROOT, iA);
            BRoot = findRoot(ROOT, iB);
            w_AR = ROOT[iA].weight;
            w_BR = ROOT[iB].weight;
            
            if(ARoot == BRoot) continue;
            else if(ROOT[ARoot].height >= ROOT[BRoot].height){
                ROOT[BRoot].root = ARoot;
                ROOT[BRoot].weight = - (iW - w_AR + w_BR);
            }
            else{
                ROOT[ARoot].root = BRoot;
                ROOT[ARoot].weight = iW - w_AR + w_BR;
            }
        }
        else if(query == '?'){ // search
            scanf("%d %d", &iA, &iB);
            iA--; iB--;
            ARoot = findRoot(ROOT, iA);
            BRoot = findRoot(ROOT, iB);
            if(ARoot != BRoot) printf("UNKNOWN\n");
            else printf("%d\n", ROOT[iA].weight - ROOT[iB].weight);
        }
    }

    return 1;
}

int main(void){
    int iN, iM;

    do scanf("%d %d", &iN, &iM);
    while(solve(iN, iM));

    return 0;
}