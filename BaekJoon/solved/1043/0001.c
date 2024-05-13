#include <stdio.h>
#include <stdlib.h>

typedef struct NODE{
    long long bit;
    struct NODE* next;
}NODE;

int main(void) {
    int i;
    int N, M, P, p, n, count, pNum;
    long long lier, tmp;
    long long *party;
    NODE *rootNode, *curNode, *firstNode, *tmpNode;

    rootNode = (NODE*)malloc(sizeof(NODE));
    curNode = rootNode;

    scanf("%d %d", &N, &M);
    party = (long long*)malloc(sizeof(long long) * M);

    scanf("%d", &P);
    for(i = 0, lier = 0; i < P; i++){
        scanf("%lld", &tmp);
        lier |= ((long long)1 << tmp);
    }

    // make party array & linked list
    for(i = 0; i < M; i++){
        scanf("%d", &n);
        tmp = 0;
        while(n--){
            scanf("%d", &p);
            tmp |= ((long long)1 << p);
        }
        party[i] = tmp;
        curNode->next = (NODE*)malloc(sizeof(NODE));
        curNode->next->bit = tmp;
        curNode = curNode->next;
    }
    curNode->next = NULL;

    // complete lier bit
    // 1. merge people
    pNum = M;
    for(i = 1; i <= N; i++){
        if(pNum == 1) break;
        firstNode = NULL;
        curNode = rootNode;
        while(curNode->next){
            if(curNode->next->bit & ((long long)1<<i)){
                if(firstNode == NULL) firstNode = curNode->next;
                else{
                    pNum--;
                    firstNode->bit |= curNode->next->bit;
                    tmpNode = curNode->next;
                    curNode->next = curNode->next->next;
                    free(tmpNode);                 
                    continue;
                }
            }
            curNode = curNode->next;
        }
    }

    // 2. find common people
    curNode = rootNode;
    while(curNode->next){
        tmp = curNode->next->bit;
        if(tmp & lier) lier |= tmp;
        curNode = curNode->next;
    }
    
    // Scan Party
    for(i = 0, count = M; i < M; i++){
        if(party[i] & lier) count--;
    }

    printf("%d\n", count);

    return 0;
}