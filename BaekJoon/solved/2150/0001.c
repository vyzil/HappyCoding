#include <stdio.h>
#include <stdlib.h>


typedef struct NODE{
    int num;
    struct NODE *next;
} NODE;

NODE* adjList;
int global_adjListSize;
int *global_stack;
int global_stackTop;
int *global_sccInfo; 
int global_sccNum;

int dfs(int num){        
    NODE* curNode;
    int childRoot;
    int id;
    int topId;
    int res;

    global_stack[++global_stackTop] = num;
    id = global_stackTop + 1; // id should be larger than 0, since 0 means non-visited
    adjList[num].num = id;
    curNode = &(adjList[num]);

    while(curNode->next){
        childRoot = adjList[curNode->next->num].num;
        if(childRoot == 0) childRoot = dfs(curNode->next->num);         // never visited
        if(childRoot < adjList[num].num) adjList[num].num = childRoot;  // visited but in current stack
        curNode = curNode->next;
    }

    // if num is root, pop until top becomes num
    if(adjList[num].num == id){
        while(id - 1 <=global_stackTop){
            adjList[global_stack[global_stackTop]].num = global_adjListSize;         // update to max, which means finished
            global_sccInfo[global_stack[global_stackTop]] = global_sccNum;
            global_stackTop--;
        }
        global_sccNum++;
        return id;
    }
    
    return adjList[num].num;
}

int findNonVisited(){
    int i;

    for(i = 0; i < global_adjListSize; i++) {
        if(adjList[i].num == 0) break;
    }

    return i;
}

int main(void){
    int i;
    int iV, iE, iA, iB;
    NODE *newNode, *curNode;
    int curNum;
    int *sccMeta, *sccIndex;
    int *res, idx, sum;
    
    // Scan Input
    scanf("%d %d", &iV, &iE);
    global_adjListSize = iV;
    adjList = (NODE*)malloc(sizeof(NODE)*iV);
    for(i = 0; i < iV; i++){
        adjList[i].num = 0;
        adjList[i].next = NULL;
    }
    for(i = 0; i < iE; i++){
        scanf("%d %d", &iA, &iB);
        iA--; iB--;
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->num = iB;
        newNode->next = adjList[iA].next;
        adjList[iA].next = newNode;
    }

    // Calc SCC
    global_stack = (int*)malloc(sizeof(int)*iV);
    global_stackTop = -1;
    global_sccInfo = (int*)malloc(sizeof(int)*iV);
    global_sccNum = 0;
    while( (curNum = findNonVisited(adjList, iV)) < iV ) dfs(curNum);

    // Print in Order
    sccMeta = (int*)malloc(sizeof(int)*global_sccNum);
    sccIndex = (int*)malloc(sizeof(int)*global_sccNum);
    for(i = 0; i < global_sccNum; i++){
        sccMeta [i] = 0;
        sccIndex[i] = -1;
    }

    for(i = 0; i < iV; i++) sccMeta[global_sccInfo[i]]++;

    sum = 0;
    res = (int*)malloc(sizeof(int)*iV);
    for(i = 0; i < iV; i++){
        if(sccIndex[global_sccInfo[i]] == -1) {
            sccIndex[global_sccInfo[i]] = sum;
            sum += sccMeta[global_sccInfo[i]];
        }
        idx = (sccIndex[global_sccInfo[i]])++;
        res[idx] = i;
    }

    printf("%d\n", global_sccNum);
    i = 0;
    while(i < iV){
        sum = sccIndex[global_sccInfo[res[i]]];
        for(;i < sum; i++) printf("%d ", res[i] + 1);
        printf("-1\n");
    }

    return 0;
}