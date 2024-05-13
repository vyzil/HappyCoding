#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE{
    int num;
    struct _NODE *next;
} NODE;

typedef struct _ADJLIST{
    int root;
    NODE *next;
} ADJLIST;

ADJLIST* global_adjList;
int global_adjListSize;
int *global_stack;
int global_stackTop;
int *global_sccInfo; 
int global_sccNum;

void printSCC(){
    int i;
    int *sccMeta, *sccIndex;
    int *res, idx, sum;

    sccMeta = (int*)malloc(sizeof(int)*global_sccNum);  // # of elements in SCC
    sccIndex = (int*)malloc(sizeof(int)*global_sccNum); // index of element in result (sort)
    for(i = 0; i < global_sccNum; i++){
        sccMeta [i] = 0;
        sccIndex[i] = -1;
    }

    for(i = 0; i < global_adjListSize; i++) sccMeta[global_sccInfo[i]]++;   // count

    sum = 0;
    res = (int*)malloc(sizeof(int)*global_adjListSize);
    for(i = 0; i < global_adjListSize; i++){        // scan ssc info of each element in order
        if(sccIndex[global_sccInfo[i]] == -1) {     // if new ssc detected,
            sccIndex[global_sccInfo[i]] = sum;      // set its index to accumulated value
            sum += sccMeta[global_sccInfo[i]];
        }
        idx = (sccIndex[global_sccInfo[i]])++;
        res[idx] = i;
    }

    printf("%d\n", global_sccNum);
    i = 0;
    while(i < global_adjListSize){
        sum = sccIndex[global_sccInfo[res[i]]];         // sum = (last index of current SSC) + 1
        for(;i < sum; i++) printf("%d ", res[i] + 1);
        printf("-1\n");
    }

    return;
}

int dfs(int num){
    NODE* curNode;
    int childRoot;
    int _id;

    global_stack[++global_stackTop] = num;
    _id = global_stackTop + 1;               // id should be larger than 0, since 0 means non-visited
    global_adjList[num].root = _id;
    curNode = (NODE*)&(global_adjList[num]);

    while(curNode->next){
        childRoot = global_adjList[curNode->next->num].root;
        if(childRoot == 0) childRoot = dfs(curNode->next->num);                         // never visited
        if(childRoot < global_adjList[num].root) global_adjList[num].root = childRoot;  // visited but in current stack
        curNode = curNode->next;
    }

    // if num is root, pop until top becomes num
    if(global_adjList[num].root == _id){
        while(_id - 1 <= global_stackTop){
            global_sccInfo[global_stack[global_stackTop]] = global_sccNum;
            global_adjList[global_stack[global_stackTop]].root = global_adjListSize;    // update to max, which means finished
            global_stackTop--;
        }
        global_sccNum++;
        return _id;
    }
    
    return global_adjList[num].root;
}

int findNonVisited(){
    int i;
    for(i = 0; i < global_adjListSize; i++) {
        if(global_adjList[i].root == 0) break;
    }
    return i;
}

int main(void){
    int i;
    int iV, iE, iA, iB;
    NODE *newNode;
    int curNum;
    
    // Scan input
    scanf("%d %d", &iV, &iE);
    global_adjListSize = iV;
    global_adjList = (ADJLIST*)malloc(sizeof(NODE)*iV);
    for(i = 0; i < iV; i++){
        global_adjList[i].root = 0;
        global_adjList[i].next = NULL;
    }
    for(i = 0; i < iE; i++){
        scanf("%d %d", &iA, &iB);
        iA--; iB--;
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->num = iB;
        newNode->next = global_adjList[iA].next;
        global_adjList[iA].next = newNode;
    }

    // Calc SCC
    global_stack = (int*)malloc(sizeof(int)*iV);
    global_sccInfo = (int*)malloc(sizeof(int)*iV);
    global_stackTop = -1;
    global_sccNum = 0;
    while( (curNum = findNonVisited()) < iV ) dfs(curNum);

    // Print in order
    printSCC();

    return 0;
}