#include <stdio.h>

int main(void){
    int i;
    int N, res;

    scanf("%d", &N);
    res = 0;
    for(i = 5; i <= N; i++){
        if(!(i%5)) res++;
        if(!(i%25)) res++;
        if(!(i%125)) res++;
    }
    printf("%d\n", res);
    return 0;
}