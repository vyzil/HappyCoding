#include <stdio.h>

#define A 0
#define B 1
#define C 2
#define D 3

#define calcWait(C, D, T) ((T)%((C)+(D)) < (C) ? 0 :  (C)+(D) - ((T)%((C)+(D))))

int main(void){
    int i, j;
    int N;
    int input[100000][4];
    int res, minTime;


    scanf("%d", &N);
    for(i = 0; i < N; i++){
        for(j = 0; j < 4; j++) scanf("%d", &input[i][j]);
    }

    res = 0;
    for(i = 0; i < N; i++){
        minTime = input[i][A] + calcWait(input[i][C], input[i][D], res);
        if(minTime > input[i][B]) minTime = input[i][B];
        res += minTime;
    }
    printf("%d\n", res);
    return 0;
}