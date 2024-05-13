#include <stdio.h>
#include <stdlib.h>

#define N_MAX 20002
#define NOT(x, n) (2*(n) - (x))

typedef struct _NODE{
    int num;
    struct _NODE *next;
} NODE;


NODE* global_adjList;
int   global_N;
int   global_listSize;
int*  global_stack;
int   global_stackTop;
int*  global_checkList;

int dfs(int num){
    int i;
    int _id;
    int childRoot;
    NODE* curNode;

    global_stackTop++;
    global_stack[global_stackTop] = num;
    _id = global_stackTop + 1;
    global_adjList[num].num = _id;
    curNode = &global_adjList[num];

    while(curNode->next){
        childRoot = global_adjList[curNode->next->num].num;
        if(childRoot == 0) childRoot = dfs(curNode->next->num);
        if(childRoot < global_adjList[num].num) global_adjList[num].num = childRoot;
        if(childRoot == -1) return -1;
        curNode = curNode->next;
    }

    if(global_adjList[num].num == _id){
        for(i = 0; i < global_listSize; i++) global_checkList[i] = 0;
        while(_id - 1 <= global_stackTop){
            global_adjList[global_stack[global_stackTop]].num = global_listSize;
            if(global_checkList[NOT(global_stack[global_stackTop], global_N)] == 1) return -1;
            global_checkList[global_stack[global_stackTop]] = 1;
            global_stackTop--;
        }
        return _id;
    }

    return global_adjList[num].num;
}

int checkNewNode(NODE *arr,int iN){
    int i;
    for(i = 0; i < 2*(iN+1); i++){
        if(arr[i].num == 0) break;
    }
    return i;
}

// { 0, 1, ...., iN, iN + 1, iN + 2, ... 2 * iN + 1 }
// (0, 1, 2, ... iN-1) iN (iN + 1, 2*iN) 2*iN + 1
// -iN ... -1 , 1 ... iN
// 0 .... iN - 1, x , iN + 1 ... 2*iN
// NOT -> 2*iN - x
int main(void){
    int i;
    int iN, iM;
    int ix1, ix2;
    NODE *newNode;

    scanf("%d %d", &iN, &iM);
    global_N = iN;
    global_listSize = 2*(iN+1);
    global_adjList = (NODE*)malloc(sizeof(NODE)*global_listSize);    
    for(i = 0; i < global_listSize; i++){
        global_adjList[i].num = 0;
        global_adjList[i].next = NULL;
    }
    global_adjList[iN].num = N_MAX;
    global_adjList[2*iN+1].num = N_MAX;
    for(i = 0; i < iM; i++){
        scanf("%d %d", &ix1, &ix2);
        ix1 += iN;
        ix2 += iN;
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->num = ix2;
        newNode->next = global_adjList[NOT(ix1, iN)].next;
        global_adjList[NOT(ix1, iN)].next = newNode;
        
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->num = ix1;
        newNode->next = global_adjList[NOT(ix2, iN)].next;
        global_adjList[NOT(ix2, iN)].next = newNode;
    }
    
    global_stack = (int*)malloc(sizeof(int)*global_listSize);
    global_stackTop= -1;
    global_checkList = (int*)malloc(sizeof(int)*global_listSize);
    while((i = checkNewNode(global_adjList, iN)) < global_listSize) {
        if (dfs(i) == -1) break;
    }

    if(i == global_listSize) printf("1\n");
    else printf("0\n");

    free(global_adjList);
    free(global_stack);
    free(global_checkList);

    return 0;
}