#include <stdio.h>
#include <string.h>

int main(void){
    int i, j;
    char input[1001];
    int strSize;
    int idx[1000] = {0,};

    scanf("%s", input);
    strSize = strlen(input);
    for(i = 0; i < strSize; i++){
        for(j = i+1; j < strSize; j++){
            if(strcmp(&input[i], &input[j]) > 0) idx[i]++;
            else idx[j]++;            
        }
    }
    
    for(i = 0; i < strSize; i++){
        for(j = 0; j < strSize; j++){
            if(idx[j] == i) break;
        }
        printf("%s\n", &input[j]);
    }

    return 0;
}