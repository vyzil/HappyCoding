#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct NODE{    
    char alpha;
    int  count;
} NODE;

typedef struct SNODE{
    int count;
    struct SNODE *next;
}snode;

int main(void){
    int i, j, idx;
    int N;
    int arrTop, num, sum;
    char tmpStr[9];
    NODE arr[10];
    snode *root, *newSNode, *curSNode;

    for(i = 0 ; i < 10; i ++) {
        arr[i].alpha = '\0';
        arr[i].count = 0;
    }
    scanf("%d", &N);

    arrTop = 0;
    for(i = 0; i < N; i++){
        scanf("%s", tmpStr);
        idx = 0;
        num = pow(10, strlen(tmpStr)-1);
        while(tmpStr[idx]){
            for(j = 0; j < arrTop; j++) {
                if (arr[j].alpha == tmpStr[idx]) break;
            }
            if(j == arrTop) arr[arrTop++].alpha = tmpStr[idx];            
            arr[j].count += num;
            num /= 10;
            idx++;
        }
    }

    root = (snode*)malloc(sizeof(snode));
    root->next = NULL;

    for(i = 0; i < arrTop; i++){
        newSNode = (snode*)malloc(sizeof(snode));
        newSNode->count = arr[i].count;
        curSNode = root;
        while(curSNode->next){
            if(curSNode->next->count < newSNode->count) break;
            curSNode = curSNode->next;
        }
        newSNode->next = curSNode->next;
        curSNode->next = newSNode;
    }

    sum = 0;
    num = 9;
    for(curSNode = root->next; curSNode; curSNode = curSNode->next){
        sum += (curSNode->count) * num;
        num--;
    }
    printf("%d\n", sum);

    return 0;
}