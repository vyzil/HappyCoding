#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000001

typedef struct NODE{
    int idx;
    struct NODE *next;
} NODE;

int main(void){
    int i;
    int count;
    int *pattern, patternLen, idx;
	char text[MAX], search[MAX];
    char cur;
    NODE *headNode, *curNode;

	gets(text);
	gets(search);

    pattern = (int*)malloc(sizeof(int)*strlen(search));
    pattern[0] = 0;
    for(idx = 0, i = 1; search[i] ;i++){
        do {
            if(search[i] == search[idx]) {
                idx++;
                break;
            }
            idx = pattern[idx - 1];
        } while(idx>0);
        pattern[i] = idx;
    }
    patternLen = i;

    // KMP 
    // exception : patternLen = 1;
    headNode = (NODE*)malloc(sizeof(NODE));
    curNode = headNode;
    i = 0;
    idx = 0;
    count = 0;
    while(cur = text[i]){       
        do{
            if(search[idx] == cur){
                idx++;
                if(idx >= patternLen){
                    curNode->idx = i - patternLen + 1 + 1;
                    curNode->next = (NODE*)malloc(sizeof(NODE));
                    curNode = curNode->next;
                    count++;
                    idx = pattern[idx - 2];
                    continue;
                }
                break;
            }
            idx = pattern[idx - 1];
        } while(idx > 0);       
        i++;
    }

    printf("%d\n", count);
    curNode = headNode;
    for(i = 0; i < count; i++) {
        printf("%d ", curNode->idx);
        curNode = curNode->next;
    }
    printf("\n");

    return 0;
}