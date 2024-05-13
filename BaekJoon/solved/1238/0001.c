#include <stdio.h>
#include <stdlib.h>

#define TMAX 1000 * 100

typedef struct NODE{
    int end;
    int time;
    struct NODE * next;
} NODE;

void dijkstra(NODE** graphArr, int start, int size, int* dijk){
    int i, j;
    int min, *checked, curIdx; 
    int curTime;
    NODE *curNode;

    checked = (int*)calloc((size+1), sizeof(int));
    for(i = 0; i < size+1; i++) dijk[i] = TMAX;
    dijk[start] = 0;
    for(i = 0; i < size; i++){
        min = TMAX;
        for(j = 1;j <= size; j++){
            if(checked[j] == 0 && dijk[j] < min){
                curIdx = j;
                min = dijk[j];
            }
        }
        checked[curIdx] = 1;
        curNode = graphArr[curIdx];
        while(curNode->next){
            if(checked[curNode->next->end] == 0){
                curTime = dijk[curIdx] + curNode->next->time;
                if(curTime < dijk[curNode->next->end]) dijk[curNode->next->end] = curTime;                
            }
            curNode = curNode->next;
        }
    }
    free(checked);

    return;
}

int main(void){
    int i;
    int iN, iM, iX;
    int iStart, iEnd, iTime;
    NODE **roadArr, **reverseArr, *newNode1, *newNode2;
    int *dijkXN, *dijkNX;
    int res;

    scanf("%d %d %d", &iN, &iM, &iX);

    roadArr = (NODE**)malloc(sizeof(NODE*)*(iN+1));
    reverseArr = (NODE**)malloc(sizeof(NODE*)*(iN+1));
    for(i = 0; i <= iN; i++) {
        roadArr[i] = (NODE*)malloc(sizeof(NODE));
        reverseArr[i] = (NODE*)malloc(sizeof(NODE));
        roadArr[i]->next = NULL;
        reverseArr[i]->next = NULL;
    }
    for(i = 0; i < iM; i++){
        scanf("%d %d %d", &iStart, &iEnd, &iTime);

        newNode1 = (NODE*)malloc(sizeof(NODE));
        newNode1->end = iEnd;
        newNode1->time = iTime;
        newNode1->next = roadArr[iStart]->next;
        roadArr[iStart]->next = newNode1;       

        newNode2 = (NODE*)malloc(sizeof(NODE));
        newNode2->end = iStart;
        newNode2->time = iTime;
        newNode2->next = reverseArr[iEnd]->next;
        reverseArr[iEnd]->next = newNode2;       
    }

    dijkXN = (int*)malloc(sizeof(int)*(iN+1));
    dijkNX = (int*)malloc(sizeof(int)*(iN+1));
    dijkstra(roadArr, iX, iN, dijkXN);
    dijkstra(reverseArr, iX, iN, dijkNX);

    res = 0;
    for(i = 1; i <= iN; i++) {
        if(dijkXN[i] + dijkNX[i] > res) res = dijkXN[i] + dijkNX[i];
    }

    printf("%d\n", res);


    return 0;
}