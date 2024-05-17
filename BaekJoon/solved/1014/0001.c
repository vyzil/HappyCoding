#include <stdio.h>
#include <stdlib.h>

int main(void){
    int TC, N, M;
    int i;
    char *strBuf;
    int *curDP, *prevDP, *swap; int dpSize;
    int cur, prev, count, check, max, raw, idx;

    scanf("%d", &TC);
    while(TC--){
        scanf("%d %d", &N, &M);
        strBuf = (char*)malloc(sizeof(char)*(M+2));
        for(dpSize = 1, i = 0; i < M; i++) dpSize <<= 1;
        curDP = (int*)calloc(dpSize, sizeof(int));
        prevDP = (int*)calloc(dpSize, sizeof(int));
        
        for(raw = 0; raw < N; raw++){
            scanf("%s", strBuf);
            for(cur = 0; cur < dpSize; cur++){
                curDP[cur] = 0;       
                // check if cur is ok
                check = 0;
                count = 0;
                idx = 0;
                for(i = cur; !check && i > 0; i >>= 1){
                    if(i % 0b100 == 0b11) check = 1;
                    if(i % 0b10) {
                        if(strBuf[idx] == 'x') check = 1;
                        count++;
                    }
                    idx++;
                }
                if(check) continue;
                for(prev = 0; prev < dpSize; prev++){
                    // check if prev is ok
                    check = 0;
                    for(i = prev; !check && i > 0; i >>= 1){
                        if(i % 0b100 == 0b11) check = 1;
                    }
                    if(check) continue;
                    if((prev << 1) & cur || prev & (cur << 1)) continue;
                    if(curDP[cur] < prevDP[prev] + count) curDP[cur] = prevDP[prev] + count;
                }
            }
            // for(i = 0; i < dpSize; i++) printf("%d ", curDP[i]); printf("\n");
            swap = curDP;
            curDP = prevDP;
            prevDP = swap;
        }

        max = 0;
        for(cur = 0; cur < dpSize; cur++){
            if(max < prevDP[cur]) max = prevDP[cur];
        }
        printf("%d\n", max);

        free(strBuf);
        free(curDP);
        free(prevDP);
    }

    return 0;
}