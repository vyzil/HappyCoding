#include <stdio.h>
#include <stdlib.h>

typedef struct DATA{
    int num;
    struct DATA *next;
}data;

typedef struct NODE{
    int  numFront; 
    data* connects;      // Linked List
} node;

int main(void){
    int i;
    int N, M;
    int A, B;
    int frontIdx;    
    int *frontQ, qFirst, qLast;
    data *newData, *curData, *prevData;
    node **Nodes, *newNode, *curNode;
    
    scanf("%d %d", &N, &M);
    
    Nodes = (node**)malloc(sizeof(node*)*N);
    frontQ = (int*)malloc(sizeof(int)*N);   // not recursive
    qFirst = 0; qLast = 0;
    
    // Nodes init
    for(i = 0; i < N; i++){
        newNode = (node*)malloc(sizeof(node));
        newNode->numFront = 0;
        newNode->connects = (data*)malloc(sizeof(data));
        Nodes[i] = newNode;
    }

    // Make Graph
    for(i = 0; i < M; i++){
        scanf("%d %d", &A, &B);
        Nodes[B-1]->numFront++;
        newData = (data*)malloc(sizeof(data));
        newData->num = A-1;
        newData->next = Nodes[B-1]->connects->next;
        Nodes[B-1]->connects->next = newData;
    }

    // Make frontQ
    for(i = 0; i < N; i++) if(Nodes[i]->numFront == 0) frontQ[qLast++] = i;

    // print by pop frontQ
    while(qFirst != qLast){
        frontIdx = frontQ[qFirst];
        printf("%d ", frontIdx+1);
        for(i = 0; i < N; i++) {
            prevData = Nodes[i]->connects;
            curData = Nodes[i]->connects->next;
            while(curData){
                if(curData->num == frontIdx){
                    if(--(Nodes[i]->numFront) == 0) frontQ[qLast++] = i;
                    prevData->next = curData->next;
                    free(curData);
                    break;
                }
                prevData = curData;
                curData = curData->next;
            }
        }
        qFirst++;
    }
    printf("\n");

    // should free datastructure..

    return 0;
}