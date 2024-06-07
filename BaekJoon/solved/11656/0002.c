/*
 * Referenced https://www.acmicpc.net/source/7075347 
 * wrote by cgiosy
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STR_MAX 1001

int cmp(const void *a, const void *b){
    return strcmp(*(char **)a, *(char **)b);
}

int main(void){
    int i;
    char *input;
    char **res;
    int strSize;

    input = (char*)malloc(sizeof(char)*STR_MAX);
    scanf("%s", input);
    strSize = strlen(input);
    res = (char**)malloc(sizeof(char*)*strSize);

    for(i = 0; i < strSize; i++) res[i] = input+i;
    qsort(res, strSize, sizeof(char*), cmp);
    for(i = 0; i < strSize; i++) printf("%s\n", res[i]);

    free(input);
    free(res);

    return 0;
}