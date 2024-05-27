#include <stdio.h>

#define PRINTRES(x, y) (printf("! %d %d\n", (x), (y)))

typedef struct _NODE{
    int l, r;
} NODE;

char ask(int l, int r){
    char res[2];
    printf("AK %d %d\n", l, r); fflush(stdout);
    scanf("%s", res);
    return res[0];
}

int main(void){
    int TC;
    int i, j, cnt;
    int l ,r;
    int N, range, isSame;
    NODE candidate[5]; int found;
    char res[50];

    scanf("%d", &TC);
    while(TC--){
        scanf("%d", &N);
        r = (1+N)/2;
        int count = 0;
        for(l = 1; r <= N; l++, r++){
            res[l] = ask(l, r);
            count++;
        }
        found = 0;
        candidate[0].l = 0; candidate[0].r = 0;
        candidate[1].l = 0; candidate[1].r = 0;
        for(i = 1; i < N; i++){
            for(j = i+1; j <= N; j++){
                isSame = 1;                
                r = (1+N)/2;
                for(l = 1; r <= N; l++, r++){
                    cnt = 0;
                    if(l <= i && i <= r) cnt++;
                    if(l <= j && j <= r) cnt++;
                    if((cnt == 1 && res[l] != 'O') || (cnt != 1 && res[l] != 'X')){
                        isSame = 0;
                        break;
                    }
                }
                if(isSame) {
                    candidate[found].l = i;
                    candidate[found].r = j;
                    found++;
                }
            }
        }
        if(found == 1) PRINTRES(candidate[0].l, candidate[0].r);
        else { // found == 2
            l = candidate[0].l;
            if(candidate[0].l == candidate[1].l || candidate[0].l == candidate[1].r) l = candidate[0].l;
            r = l;
            
            if(ask(l, r) == 'O') PRINTRES(candidate[0].l, candidate[0].r);
            else PRINTRES(candidate[1].l, candidate[1].r);
        }
        printf("%d %d\n", count, found);
        fflush(stdout);
    }

    return 0;
}