#include <stdio.h>
#include <string.h>

int main(void){
    int i;
    int textTop, buffTop;
    int isBomb;
    int bombSize;
    char text[1000001];
    char buff[1000001];
    char bomb[37];

    scanf("%s", text);
    scanf("%s", bomb);
    bombSize = strlen(bomb);    

    textTop = 0;
    buffTop = 0;
    while(text[textTop]){        
        buff[buffTop++] = text[textTop++];      // Add to Buffer
                
        isBomb = 1;
        while(isBomb == 1){                     // Keep detecting bomb until no bomb on top 
            if(buffTop < bombSize) break;       // if buffer is not enough for bomb, exit
            for(i = 0; i < bombSize; i++){      // Detect Bomb on Top
                if(buff[buffTop - bombSize + i] != bomb[i]) {   // if Top is innocent, break
                    isBomb = 0;
                    break;
                }
            }
            if(isBomb == 1){                    // if bomb detected, change bufftop to exclude bomb
                buffTop -= bombSize;
            }
        }
        buff[buffTop] = '\0';                   // Make sure the buff string ends before bomb
    }

    if(strlen(buff) > 0) printf("%s\n", buff);
    else printf("FRULA\n");

    return 0;
}