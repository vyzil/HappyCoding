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
    int count, prev;
    int *pattern, patternLen, idx, match;
	char text[MAX], search[MAX];
    char cur;
    NODE *headNode, *curNode;

	gets(text);
	gets(search);

    pattern = (int*)malloc(sizeof(int)*strlen(search));
    pattern[0] = -1;
    prev = 0;
    for(idx = 0, i = 1; search[i] ;i++){
        if(search[i] == search[idx]) idx++;  
        else {
            idx = pattern[idx];
            while(idx >= 0){
                if(search[i] == search[idx]) {
                    idx++;
                    break;
                }
                idx = pattern[idx];
            }
        }
        if(idx == -1) idx++;
        pattern[i] = prev;
        prev = idx;       
    }
    patternLen = i;

    // KMP
    headNode = (NODE*)malloc(sizeof(NODE));
    curNode = headNode;
    count = 0;
    
    i = 0;
    idx = 0;    
    while(cur = text[i]){
        match = 0;
        if(cur == search[idx]){
            idx++; match = 1;
            if(idx == patternLen){  
                idx--;              
                curNode->idx = i - idx + 1;
                curNode->next = (NODE*)malloc(sizeof(NODE));
                curNode = curNode->next;
                count++;
                match = 0;
            }
        }
        if(match == 0) {
            idx = pattern[idx];
            while(idx >= 0){
                if(cur == search[idx]) {
                    idx++;
                    break;
                }
                idx = pattern[idx];
            }
            if(idx == -1) idx++;
        }
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