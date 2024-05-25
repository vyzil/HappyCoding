#include <stdio.h>

#define SPACE 10
#define ABS(x) ((x) > 0 ? (x) : -(x))

int main(void){
    int i; char C;
    int bot, box, goal;
    for(i = 0; i < SPACE; i++) {
        C = getchar();
        if(C == '.') continue;
        else if(C == '@') bot = i;
        else if(C == '#') box = i;
        else goal = i; // C == '!'
    }
    
    if((goal - box) * (box - bot) > 0) printf("%d\n", ABS(goal - bot) - 1);
    else printf("-1\n");
    
    return 0;
}