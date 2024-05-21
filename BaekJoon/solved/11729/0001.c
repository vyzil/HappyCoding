#include <stdio.h>

int tower[4];

void move(int src, int dst, int mid, int num){
    if(num == 1){
        printf("%d %d\n", src, dst);
        tower[src]--;
        tower[dst]++;
        return;
    }

    move(src, mid, dst, num-1);
    printf("%d %d\n", src, dst);    
    tower[src]--;
    tower[dst]++;
    move(mid, dst, src, num-1);

    return;
}

int main(void){
    int i;
    int N, K;
    scanf("%d", &N);

    tower[1] = N;
    tower[2] = 0;
    tower[3] = 0;

    for(i = 0, K = 1; i < N; i++, K <<= 1);
    printf("%d\n", K-1);
    move(1, 3, 2, N);

    return 0;
}