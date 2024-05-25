#include <stdio.h>
#include <stdlib.h>

#define atoi(a) ((a) - '0')

typedef struct _NODE{
    struct _NODE *next[11]; // 10 = end
} NODE;

void iterFree(NODE *root){
    int i;
    for(i = 0; i < 11; i++){
        if(root->next[i]) iterFree(root->next[i]);
    }
    free(root);
    return;
}

int main(void){
    int i, j;
    int TC;
    int N;
    char buf[11];
    int res;
    NODE *root, *curNode;

    scanf("%d", &TC);

    while(TC--){
        scanf("%d", &N);
        root = (NODE*)calloc(1, sizeof(NODE));

        res = 1;
        for(i = 0; i < N; i++){
            scanf("%s", buf);
            if(res){
                curNode = root;
                for(j = 0; res && buf[j]; j++){
                    if(curNode->next[atoi(buf[j])] == NULL) curNode->next[atoi(buf[j])] = (NODE*)calloc(1, sizeof(NODE));
                    if(curNode->next[10]) res = 0;
                    curNode = curNode->next[atoi(buf[j])];
                }
                if(res && curNode->next[10] == NULL) curNode->next[10] = (NODE*)calloc(1, sizeof(NODE));           
                for(j = 0; j < 10; j++){
                    if(curNode->next[j]) res = 0;
                }
            }
        }

        if(res) printf("YES\n");
        else printf("NO\n");

        iterFree(root);
    }

    return 0;
}