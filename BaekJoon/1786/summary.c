// ****************************************************************
// # [Customized KMP : Explanation] by SWShin
// Pattern saves index of next value to compare
//
// example 01) 
// index   : 0 1 2 3  4
// text    : A B A B 'A' B A B A B C
// search  : A B A B 'C'
// pattern :-1 0 0 1  2      
// 
// When mismatch happens on comparing 'A'(text[4]) and 'C'(search[4]),
// Then, it should check if 'A' matches search[pattern[4]].
// search[pattern[4]] is search[2] and it is 'A' that matches.
// So in next loop, it compares search[2 + 1] and text[4 + 1].
// 
// example 02) 
// index   : 0 1 2 3  4
// text    : A B C B 'A' B A B A B C
// search  : A B C A 'C'
// pattern :-1 0 0 0  1      
// 
// Again mismatch happens on comparing 'A'(text[4]) and 'C'(search[4]),
// Now it checks if 'A' matches search[pattern[4]].
// search[pattern[4]] is search[1] and it is 'B' that still does not match.
// So, it checks if 'A' matches search[pattern[1]] which is 'A'(search[0]).
// In next loop, it compares search[0 + 1] and text[4 + 1].
// 
// If all wrong and checking meets search[pattern[0]],
// since pattern[0] is '-1', it stops loop
// In next loop, it compares search[0] and text[4 + 1].
// ****************************************************************

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

    // To make this pattern, we should hold previous status
    // because it depends on whether previous value matches prefix.
    pattern = (int*)malloc(sizeof(int)*strlen(search));
    pattern[0] = -1;
    prev = 0;
    for(idx = 0, i = 1; search[i] ;i++){
        while(idx >= 0 && search[i] != search[idx]) idx = pattern[idx];
        idx++;
        pattern[i] = prev;
        prev = idx;
    }
    patternLen = i;

    headNode = (NODE*)malloc(sizeof(NODE));
    curNode = headNode;
    count = 0;
    
    // KMP Search
    i = 0;
    idx = 0;    
    while(cur = text[i]){
        while( idx >= 0 && cur != search[idx]) idx = pattern[idx];
        idx++;
        if(idx == patternLen){       
            idx--;
            curNode->idx = i - idx + 1;
            curNode->next = (NODE*)malloc(sizeof(NODE));
            curNode = curNode->next;
            count++;
            idx = pattern[idx];
            continue;
        }
        i++;
    }

    curNode = headNode;
    printf("%d\n", count);
    for(i = 0; i < count; i++) {
        printf("%d ", curNode->idx);
        curNode = curNode->next;
    }
    printf("\n");

    return 0;
}