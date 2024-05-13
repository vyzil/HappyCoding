#include <stdio.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0

typedef struct _NODE{
    int num;    // either start or end+1
    struct _NODE *next;
} NODE;

int *g_HEAP;    // MIN_HEAP
int g_HEAP_SIZE;

void insertHeap(int num){
    int curIdx, parentIdx;

    g_HEAP_SIZE++;
    curIdx = g_HEAP_SIZE;
    while(curIdx > 1){
        parentIdx = curIdx / 2;
        if(g_HEAP[parentIdx] < num) break;
        g_HEAP[curIdx] = g_HEAP[parentIdx];
        curIdx = parentIdx;
    }
    g_HEAP[curIdx] = num;

    return;
}

void deleteHeap(){  // no need to pop
    int num;
    int curIdx, childIdx;

    num = g_HEAP[g_HEAP_SIZE];
    curIdx = 1;
    while(2 * curIdx < g_HEAP_SIZE){
        childIdx = 2*curIdx;
        if(childIdx + 1 < g_HEAP_SIZE && g_HEAP[childIdx] > g_HEAP[childIdx + 1]) childIdx++;
        if(num < g_HEAP[childIdx]) break;
        g_HEAP[curIdx] = g_HEAP[childIdx];
        curIdx = childIdx;
    }
    g_HEAP[curIdx] = num;

    g_HEAP_SIZE--;

    return;
}

int main(void){
    int i;
    int N, Q;
    int a, b, x;
    NODE *range, *newNode, *curNode;
    int *color, *isPaint;
    
    scanf("%d %d", &N, &Q);
    range = (NODE*)malloc(sizeof(NODE)*N);
    color = (int*)malloc(sizeof(int)*Q);
    isPaint = (int*)malloc(sizeof(int)*Q);
    g_HEAP = (int*)malloc(sizeof(int)*(Q+1));
    g_HEAP_SIZE = 0;

    for(i = 0; i < N; i++){
        range[i].num = 0;
        range[i].next = NULL;
    }
    for(i = 0; i < Q; i++) isPaint[i] = FALSE;
    
    for(i = 0; i < Q; i++){
        scanf("%d %d %d", &a, &b, &x);
        a--; b--;
        color[i] = x;

        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->num = i;
        newNode->next = range[a].next;
        range[a].next = newNode;

        if(b + 1 < N){            
            newNode = (NODE*)malloc(sizeof(NODE));
            newNode->num = i;
            newNode->next = range[b+1].next;
            range[b+1].next = newNode;
        }
        
    }

    for(i = 0; i < N; i++){
        curNode = &range[i];
        while(curNode->next){
            if(isPaint[curNode->next->num] == FALSE){
                insertHeap(curNode->next->num);
                isPaint[curNode->next->num] = TRUE;
            }
            else isPaint[curNode->next->num] = FALSE;   // if TRUE
            curNode = curNode->next;
        }
        while(g_HEAP_SIZE > 0 && isPaint[g_HEAP[1]] == FALSE) deleteHeap();

        if(g_HEAP_SIZE > 0) printf("%d ", color[g_HEAP[1]]);
        else printf("0 ");
    }

    printf("\n");

    // nodes connected to "range" should be free
    free(range);
    free(color);
    free(isPaint);
    free(g_HEAP);

    return 0;
}