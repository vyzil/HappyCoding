#include <stdio.h>

#define PRINTRES(x) (printf("! %d %d\n", (x).l, (x).r))

typedef struct _NODE{
    int l, r;
} NODE;

char ask(int l, int r){
    char res[2];
    printf("AK %d %d\n", l, r); fflush(stdout);
    scanf("%s", res);
    return res[0];
}

NODE BinarySearch(int N){
    int l, r, mid;
    NODE result;

    l = 1;
    r = N/2 + 1;
    while(l != r){
        mid = (l + r)/2;
        if(ask(l, mid) == 'O') r = mid;
        else l = mid+1;
    }
    result.l = l;
    
    l = N/2 + 2;
    r = N;    
    while(l != r){
        mid = (l + r)/2;
        if(ask(l, mid) == 'O') r = mid;
        else l = mid+1;
    }
    result.r = r;

    return result;
}

NODE Solve(int N){
    int i, j, cnt;
    int l, r;
    char response[50];
    int isSame;
    NODE candidate[5]; int found;
    NODE result;

    response[1] = 'X';
    l = 2;
    r = N/2 + 2;
    int count = 1; //** debug
    for(; r <= N; l++, r++){
        response[l] = ask(l, r);
        count++; //** debug
    }
    found = 0;
    candidate[0].l = 0; candidate[0].r = 0;
    candidate[1].l = 0; candidate[1].r = 0;
    for(i = 1; i < N; i++){
        for(j = i+1; j <= N; j++){
            isSame = 1;                
            r = N/2 + 1;
            for(l = 1; r <= N; l++, r++){
                cnt = 0;
                if(l <= i && i <= r) cnt++;
                if(l <= j && j <= r) cnt++;
                if((cnt == 1 && response[l] != 'O') || (cnt != 1 && response[l] != 'X')){
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
    result.l = candidate[0].l;
    result.r = candidate[0].r;
    if(found == 2){
        l = candidate[0].l;
        if(candidate[0].l == candidate[1].l || candidate[0].l == candidate[1].r) l = candidate[0].r;
        r = l;
        count++; //**debug
        if(ask(l, r) == 'X') {
            result.l = candidate[1].l;
            result.r = candidate[1].r;
        }
    }
    // printf("%d %d\n", count, found); //** debug
    // for(int i = 0; i < found ;i++){
    //     printf("found : %d %d\n", candidate[i].l, candidate[i].r);
    // }
    return result;
}

int main(void){
    int TC;    
    int N;
    NODE result;
    char response;

    scanf("%d", &TC);
    while(TC--){
        scanf("%d", &N);
        if(N == 2){
            result.l = 1;
            result.r = 2;
        }
        if(N == 3){
            result.l = 1;
            result.r = 2;
            if(ask(1, 2) == 'O') {
                if(ask(1, 1) == 'O') result.r = 3;
                else result.l = 3;
            }
        }
        if (N > 3){
            response = ask(1, N/2 + 1);
            if (response == 'O') result = BinarySearch(N);
            else result = Solve(N);
        }
        PRINTRES(result);
        fflush(stdout);
    }

    return 0;
}