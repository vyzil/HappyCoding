#include <stdio.h>
#include <stdlib.h>

typedef struct NODE{    
    int dst;
    int len;
    struct NODE *next;
}NODE;

int main(void){
    int N, src, dst, len, mid;
    int i, try;
    int max, maxIdx;
    NODE **root, *newNode, *curNode;
    int *distance, *queue, queueLow, queueHigh;

    scanf("%d", &N);
    root = (NODE**)malloc(sizeof(NODE*)*N);    
    for(i = 0; i < N; i++){
        scanf("%d", &src);
        root[src-1] = (NODE*)malloc(sizeof(NODE));
        root[src-1]->next = NULL;
        for(scanf("%d", &dst); dst != -1; scanf("%d", &dst)){
            scanf("%d", &len);            
            newNode= (NODE*)malloc(sizeof(NODE));
            newNode->dst = dst-1;
            newNode->len = len;
            newNode->next = root[src-1]->next;
            root[src-1]->next = newNode;
        }
    }

    distance = (int*)malloc(sizeof(int)*N);
    queue = (int*)malloc(sizeof(int)*N);

    for(try = 0, src = 0, max = 0; try < 2; try++){
        queueLow = 0;
        queue[queueLow] = src;
        queueHigh = 1;
        for(i = 0; i < N; i++) distance[i] = 0;
        while(queueHigh > queueLow){
            curNode = root[queue[queueLow]]->next;        
            mid = queue[queueLow++];
            while(curNode){
                dst = curNode->dst;
                len = curNode->len;
                if(src == dst) {
                    curNode = curNode->next;
                    continue;
                }
                if(distance[dst] == 0 || distance[dst] > len + distance[mid]) {
                    distance[dst] = len + distance[mid];
                    queue[queueHigh++] = dst;
                }
                curNode = curNode->next;   
            }
        }

        for(i = 0 ; i < N; i++) {
            if(max < distance[i]) {
                max = distance[i];
                src = i;
            }
        }
    }

    printf("%d\n", max);

    // free should be done..

    return 0;
}