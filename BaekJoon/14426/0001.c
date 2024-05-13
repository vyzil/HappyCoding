#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MAX 500

typedef struct TEMP{
    char* str;
    struct TEMP *next;
}temp;

int binarySearch(char* check, char** dict, int size){
    int low, mid, high;
    int c, len;
    int res;

    len = strlen(check);
    low = 0; 
    high = size - 1;
    res = 0;
    while(low <= high){
        mid = (low + high) / 2;
        c = strncmp(check, dict[mid], len);
        if (c > 0) low = mid + 1;
        else if (c < 0) high = mid - 1;
        else {
            res = 1;
            break;
        }
    }
    return res;
}

int main(void){
    int i;
    int N, M;
    int count;
    char **dict, *tmpStr; // Check
    temp *head, *newNode, *curNode, *prevNode;

    tmpStr = (char*)malloc(N_MAX + 1);

    scanf("%d %d", &N, &M);
    
    head = (temp*)malloc(sizeof(temp));
    for(i = 0; i < N; i++) {
        newNode = (temp*)malloc(sizeof(temp));
        newNode->str = (char*)malloc(N_MAX + 1);
        scanf("%s", newNode->str);

        prevNode = head;
        curNode = head->next;
        while(curNode){
            if(strcmp(curNode->str, newNode->str) > 0) break;
            prevNode = curNode;
            curNode = curNode->next;
        }
        prevNode->next = newNode;
        newNode->next = curNode;
    }

    dict = (char**)malloc(sizeof(char*)*N);
    prevNode = head;
    for(curNode = head->next, i = 0 ; curNode ; curNode = curNode->next) {
        free(prevNode);
        dict[i++] = curNode->str;
        prevNode = curNode;
    }
    free(prevNode);

    count = 0;
    for(i = 0; i < M; i++) {
        scanf("%s", tmpStr);
        if(binarySearch(tmpStr, dict, N) == 1) {
            count++;
        }
    }

    printf("%d\n", count);

    free(dict);
    free(tmpStr);

    return 0;
}