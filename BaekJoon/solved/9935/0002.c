#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    int i;
    int textTop, buffTop;
    int isBomb;
    int bombSize;
    char text[1000001];
    char *buff;
    char bomb[37];

    scanf("%s", text);
    scanf("%s", bomb);
    bombSize = strlen(bomb);    
    buff = (char*)malloc(sizeof(char)*(strlen(text) + 1));

    textTop = 0;
    buffTop = 0;
    while(text[textTop]){        
        buff[buffTop++] = text[textTop++];                
        isBomb = 1;
        while(isBomb == 1){
            if(buffTop < bombSize) break;
            for(i = 0; i < bombSize; i++){
                if(buff[buffTop - bombSize + i] != bomb[i]) {
                    isBomb = 0;
                    break;
                }
            }
            if(isBomb == 1) buffTop -= bombSize;            
        }
        buff[buffTop] = '\0';
    }

    if(strlen(buff) > 0) printf("%s\n", buff);
    else printf("FRULA\n");

    return 0;
}