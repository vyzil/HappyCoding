#include <stdio.h>
#include <stdlib.h>

#define BYTE 8

typedef struct NODE{
    int  numFront; 
    int* fronts;      // Index array, saving front node
} node;

int main(void){
    int i;
    int N, M;
    int A, B;
    int frontIdx;    
    int *frontQ, qFirst, qLast;
    node **Nodes, *newNode, *curNode;
    
    scanf("%d %d", &N, &M);
    
    Nodes = (node**)malloc(sizeof(node*)*N);
    frontQ = (int*)malloc(sizeof(int)*N);   // not recursive
    qFirst = 0; qLast = 0;
    
    // Nodes init
    for(i = 0; i < N; i++){
        newNode = (node*)malloc(sizeof(node));
        newNode->numFront = 0;
        newNode->fronts = (int*)malloc(sizeof(int)*(N/BYTE));
        Nodes[i] = newNode;
    }

    // Make Graph
    for(i = 0; i < M; i++){
        scanf("%d %d", &A, &B);
        Nodes[B-1]->numFront++;
        Nodes[B-1]->fronts[(A-1)/BYTE] |= (1 << (A-1)%BYTE);
    }

    // Make frontQ
    for(i = 0; i < N; i++) if(Nodes[i]->numFront == 0) frontQ[qLast++] = i;

    // print by pop frontQ
    while(qFirst != qLast){
        frontIdx = frontQ[qFirst];
        printf("%d ", frontIdx+1);
        for(i = 0; i < N; i++) {
            if((Nodes[i]->fronts[frontIdx/BYTE] && (1 << frontIdx%BYTE) )  == 1){
                Nodes[i]->fronts[frontIdx/BYTE] ^= (1 << frontIdx%BYTE);
                if(--(Nodes[i]->numFront) == 0) frontQ[qLast++] = i;
            }
        }
        qFirst++;
    }
    printf("\n");

    for(i = 0; i < N; i++) {
        free(Nodes[i]->fronts);
        free(Nodes[i]);
    }
    free(Nodes);
    free(frontQ);

    return 0;
}