#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000001

int main(void){
    int  i;
    int  count, prev;
    int  *pattern, patternLen, idx, match;
    int  res[MAX];
	char text[MAX], search[MAX];
    char cur;

	gets(text);
	gets(search);

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
    
    // KMP Search
    count = 0;
    i = 0;
    idx = 0;    
    while(cur = text[i]){
        while( idx >= 0 && cur != search[idx]) idx = pattern[idx];
        idx++;
        if(idx == patternLen){       
            idx--;
            res[count++] = i - idx + 1;
            idx = pattern[idx];
            continue;
        }
        i++;
    }

    printf("%d\n", count);
    for(i = 0; i < count; i++) printf("%d ", res[i]);
    printf("\n");

    return 0;
}