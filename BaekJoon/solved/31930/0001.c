#include <stdio.h>

#define PRINTRES(x, y) (printf("! %d %d\n", (x), (y)))

int main(void){
    int TC;
    int i;
    int N;
    int found;
    int num[4];
    char res[2];

    scanf("%d", &TC);
    while(TC--){
        scanf("%d", &N);

        found = 0;
        for(i = 2; i < N; i++){
            printf("AK %d %d\n", i, i+1); fflush(stdout);
            scanf("%s", res);
            if(res[0] == 'O') num[found++] = i;
        }
        if(found == 1){
            if(num[0] == 3) PRINTRES(num[0]-1, num[0]);
            else PRINTRES(num[0], num[0]+1);
        }
        else if(found == 2){
            if(num[0] == 2 && num[1] == N-1) PRINTRES(num[0], num[1]+1);
            else PRINTRES(num[0]+1, num[1]);
        }
        else if(found == 3){
            if(num[0] == 2) PRINTRES(num[0], num[2]);
            else PRINTRES(num[1], num[2]+1);
        }
        else {  // found = 4
            PRINTRES(num[1], num[3]);
        }
        fflush(stdout);
    }

    return 0;
}