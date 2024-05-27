#include <stdio.h>

typedef struct _NODE{
    int l, r;
} NODE;

char ask(int l, int r){
    char res[2];
    printf("AK %d %d\n", l, r); fflush(stdout);
    scanf("%s", res);
    return res[0];
}

int BinarySearch(int N, int l, int r){
    int mid;

    while(l != r){
        mid = (l + r)/2;
        if(ask(l, mid) == 'O') r = mid;
        else l = mid+1;
    }

    return l;
}

NODE Solve(int N){
    int l, r;
    NODE result;

    l = 1;
    r = N/2 + 1;
    result.l = r-1;
    result.r = r;
    for(; r <= N; l++, r++) {
        if(ask(l, r) == 'O') {
            if(l == 1){
                result.l = BinarySearch(N, l, r);
                result.r = BinarySearch(N, r+1, N);
            }
            else if (r < N-1){
                if(ask(l-1, l-1) == 'O') {
                    result.l = l-1;
                    result.r = BinarySearch(N, l, N/2 + 1);
                }
                else {
                    result.l = r;
                    result.r = BinarySearch(N, r+1, N);
                }
            } 
            else if(r == N - 1){
                if(ask(l+1, r+1) ==  'O'){
                    result.l = l-1;
                    if(ask(l+1, l+1) == 'O') result.r = l+1;
                    else result.r = l+2;
                }
                else{
                    if(ask(r+1, r+1) == 'O'){
                        result.l = r;
                        result.r = r+1;
                    }
                    else{
                        result.l = l-1;
                        result.r = l;
                    }
                }
            }
            else {  // r == N
                if(ask(l, l) == 'O') result.l = l;
                else result.l = l+1;
            }
            break;
        }      
    }

    return result;
}

int main(void){
    int TC;    
    int N;
    NODE result;
    
    scanf("%d", &TC);
    while(TC--){
        scanf("%d", &N);
        result = Solve(N);
        (printf("! %d %d\n", result.l, result.r));
        fflush(stdout);
    }
    return 0;
}