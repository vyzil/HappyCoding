#include <stdio.h>
#include <stdlib.h>

#define INPUT_MAX 501
#define ALPHA_SIZE 'z' - 'a' + 1

typedef struct TRIE{
    char key;
    struct TRIE* child[ALPHA_SIZE];
} trie;


int main(void){
    int i, pos;
    int N, M, res;
    char* tmpStr;
    trie *root, *newNode, *curNode;
    
    root = (trie*)malloc(sizeof(trie));
    tmpStr = (char*)malloc(INPUT_MAX);

    scanf("%d %d", &N, &M);

    // Make Trie of S strings
    for(i = 0; i < N; i++){
        scanf("%s", tmpStr);
        curNode = root;
        for(pos = 0; tmpStr[pos] != '\0'; pos++){
            if(curNode->child[tmpStr[pos] - 'a'] != NULL){
                curNode = curNode->child[tmpStr[pos] - 'a'];
                continue;
            }
            newNode = (trie*)malloc(sizeof(trie));
            newNode->key = tmpStr[pos];
            curNode->child[tmpStr[pos] - 'a'] = newNode;
            curNode = curNode->child[tmpStr[pos] - 'a'];
        }
    }

    // Search Trie if input exist as prefix
    res = 0;
    for(i = 0; i < M; i++){
        scanf("%s", tmpStr);
        curNode = root;
        res++;
        for(pos = 0; tmpStr[pos] != '\0'; pos++){
            if(curNode->child[tmpStr[pos] - 'a'] == NULL){
                res--; break;
            }
            curNode = curNode->child[tmpStr[pos] - 'a'];
        }
    }
    printf("%d\n", res);

    // should free trie...
    free(tmpStr);

    return 0;
}