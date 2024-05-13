#include <stdio.h>
#include <stdlib.h>

typedef struct NODE{
    int num;
    int visited;
    struct NODE *parent;
    struct NODE *lChild;
    struct NODE *rChild;
} NODE;

int main(void){
    int iNum, treeSize;
    NODE *rootNode, *curNode, *newNode;
    NODE **nodeStack;
    int stackTop;


    treeSize = 0;
    if(scanf("%d", &iNum) == EOF) return 0;        
    newNode = (NODE*)malloc(sizeof(NODE));
    newNode->num = iNum;
    newNode->visited = 0;
    newNode->parent = NULL;
    newNode->lChild = NULL;
    newNode->rChild = NULL;
    rootNode = newNode;
    treeSize++;

    curNode = rootNode;
    while(scanf("%d", &iNum) == 1){
        treeSize++;
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->num = iNum;
        newNode->visited = 0;
        newNode->lChild = NULL;
        newNode->rChild = NULL;
        if(iNum < curNode->num){
            curNode->lChild = newNode;
        }
        else {
            curNode;
            while(curNode->parent && curNode->parent->num < iNum){
                curNode = curNode->parent;
            }
            while(curNode->rChild){
                curNode = curNode->rChild;
            }
            curNode->rChild = newNode;
        }
        newNode->parent = curNode;
        curNode = newNode;        
    }
    
    nodeStack = (NODE**)malloc(sizeof(NODE)*treeSize);
    stackTop = -1;
    nodeStack[++stackTop] = rootNode;
    while(stackTop >= 0){
        curNode = nodeStack[stackTop];
        if(curNode->lChild && curNode->lChild->visited == 0) {
            nodeStack[++stackTop] = curNode->lChild;
            continue;
        }
        if(curNode->rChild && curNode->rChild->visited == 0) {
            nodeStack[++stackTop] = curNode->rChild;
            continue;
        }
        printf("%d\n", curNode->num);
        curNode->visited = 1;
        stackTop--;
    }

    // free should be done..

    return 0;
}