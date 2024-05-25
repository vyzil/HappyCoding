#include <stdio.h>
#include <stdlib.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))

int main(void){
    int i, j;
    int N, Q;
    int l, r, cnt, max, range;
    char *inputStr;

    scanf("%d", &N);
    inputStr = (char*)malloc(sizeof(char)*N);
    scanf("%s", inputStr);
    scanf("%d", &Q);

    while(Q--){        
        scanf("%d %d", &l, &r);
        l--; r--;

        max = 0;
        for(i = l; i < r; i++){
            range = MIN(i - l, r - (i + 1));
            cnt = 0;
            for(j = 0; j <= range; j++){
                if(inputStr[i-j] == inputStr[i+1+j]) cnt++;
            }
            if(cnt > max) max = cnt;
        }
        printf("%d\n", max);
    }

    return 0;
} 