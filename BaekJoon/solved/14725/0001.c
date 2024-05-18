#include <stdio.h>
#include <stdlib.h>

#define STR_MAX 16
#define ALPHA 28

#define atoi(x) (x == '.' ? 0 : ( x == '-'? 1 :((x) - 'A' + 2)))

typedef struct _NODE{
    char c;
    struct _NODE *next[ALPHA];
} NODE;


NODE g_trie;
char g_buf[STR_MAX];

void printTrie(NODE* curNode, int idx, int height){
    int i, j;
    char c;

    c = curNode->c;
    if('A' <= c && c <= 'Z') g_buf[idx++] = curNode->c;
    
    for(i = 0; i < ALPHA; i++){
        if(curNode->next[i] != NULL) {
            if(curNode->next[i]->c == '.'){ // print leaf (can be subString)
                for(j = 0; j < height; j++) printf("--");
                g_buf[idx] = '\0';
                printf("%s\n", g_buf);
                continue;
            }
            else if(curNode->next[i]->c == '-') {   // print & move childNode
                for(j = 0; j < height; j++) printf("--");
                g_buf[idx] = '\0';
                printf("%s\n", g_buf);
                printTrie(curNode->next[i], 0, height+1);
            }
            else printTrie(curNode->next[i], idx, height);
        }
    }
        
    return;
}

NODE *makeNode(char c){
    int i;
    NODE *res;
    res = (NODE*)malloc(sizeof(NODE));
    res->c = c;
    for(i = 0; i < ALPHA; i++) res->next[i] = NULL;
    return res;
}

int main(void){
    int i;
    int N, K;
    char iStr[STR_MAX];
    NODE *curNode;

    scanf("%d",  &N);

    while(N--){
        scanf("%d ", &K);

        curNode = &g_trie;
        while(K--){
            scanf("%s", iStr);
            for(i = 0; iStr[i]; i++){
                if(curNode->next[atoi(iStr[i])] == NULL){
                    curNode->next[atoi(iStr[i])] = makeNode(iStr[i]);
                }
                curNode = curNode->next[atoi(iStr[i])];
            }
            if(K > 0){
                if(curNode->next[atoi('-')] == NULL){
                    curNode->next[atoi('-')] = makeNode('-');
                }
                curNode = curNode->next[atoi('-')];
            }
            else{
                if(curNode->next[atoi('.')] == NULL){
                    curNode->next[atoi('.')] = makeNode('.');
                }
                curNode = curNode->next[atoi('.')];
            }
        }
    }

    printTrie(&g_trie, 0, 0);

    return 0;
}