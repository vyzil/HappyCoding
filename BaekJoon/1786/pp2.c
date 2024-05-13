#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000001

int main(void){
    int i;
    int count;
    int *pattern, idx, prev = 0;
	char str1[MAX], search[MAX];

	// gets(str1);
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

    for(i = 0; search[i]; i++) printf("%d", pattern[i]); printf("\n");


    

    return 0;
}
