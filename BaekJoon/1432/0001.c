#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE{
    int num;
    struct _NODE *next;
} NODE;

int findLargeStart(NODE *graph, int size){
    int i;
    for(i = size-1; i >= 0; i--){
        if(graph[i].num == 0) break;
    }
    return i;
}

int main(void){
    int i, j;
    int iN;
    char iTmp;
    int *res, idx;
    NODE *graph, *newNode, *curNode;

    scanf("%d", &iN);
    getchar();
    graph = (NODE*)malloc(sizeof(NODE)*iN);
    for(i = 0; i < iN; i++) {
        graph[i].num = 0;
        graph[i].next = NULL;
    }

    for(i = 0; i < iN; i++){
        for(j = 0; j < iN; j++){
            scanf("%c", &iTmp);
            if(iTmp == '1'){
                newNode = (NODE*)malloc(sizeof(NODE));
                newNode->num = i;
                newNode->next = graph[j].next;
                graph[j].next = newNode;
                graph[i].num++;
            }
        }
        getchar();
    }

    idx = iN-1;
    res = (int*)malloc(sizeof(int)*iN);
    while((i = findLargeStart(graph, iN)) >= 0){
        res[i] = idx--;
        curNode = &(graph[i]);
        while(curNode->next){
            graph[curNode->next->num].num--;
            curNode = curNode->next;
        }
        graph[i].num = -1;
    }

    if(idx != -1) printf("-1");
    else{
        for(i = 0; i < iN; i++) printf("%d ", res[i] + 1);
    }
    printf("\n");
    
    free(graph);

    return 0;
}