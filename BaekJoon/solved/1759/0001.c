#include <stdio.h>
#include <stdlib.h>

typedef struct NODE{
    char alphabet;
    struct NODE * next;
}NODE;

int main(void){
    int i;
    int L, C;
    char alpha;
    char *alphaArr, *curString;
    int  *indexArr, last;
    int  aeiou;
    NODE *rootNode, *curNode, *newNode;

    rootNode = (NODE*)malloc(sizeof(NODE));
    rootNode->next = NULL;

    scanf("%d %d", &L, &C);

    for(i = 0; i < C; i++){
        scanf(" %c", &alpha);
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->alphabet = alpha;        

        curNode = rootNode;
        while(curNode->next){
            if(curNode->next->alphabet > alpha) break;
            curNode = curNode->next;
        }
        newNode->next = curNode->next;
        curNode->next = newNode;
    }

    alphaArr  = (char*)malloc(C);
    indexArr  = (int*)malloc(sizeof(int)* L);
    curString = (char*)malloc(L+2);
    for(i = 0, curNode = rootNode->next; curNode; i++, curNode = curNode->next) alphaArr[i] = curNode->alphabet;
    for(i = 0; i < L; i++) indexArr[i] = i;

    indexArr[L-1]--;
    curString[L] = '\n';
    curString[L+1] = '\0';
    while(1){
        // Increase one
        last = L-1;
        while(++indexArr[last] >= C - (L - 1 - last)){
            last--;
            if(last < 0) return 0;
        }
        // Arrage Index
        while(last++ < L-1) indexArr[last] = indexArr[last-1] + 1;
        
        // Check aeiou
        aeiou = 0;
        for(i = 0; i < L; i++) {
            curString[i] = alphaArr[indexArr[i]];
            if(curString[i] == 'a' || curString[i] == 'e' || curString[i] == 'i' || curString[i] == 'o' || curString[i] == 'u') aeiou++;
        }

        // Print if condition matches
        if(aeiou >= 1 && L - aeiou >= 2) printf("%s", curString);
    }

    return 0;
}