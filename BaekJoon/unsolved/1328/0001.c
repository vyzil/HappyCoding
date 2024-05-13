#include <stdio.h>

int combination(int n, int r){
    if(r < 0) return 0;

    int i, res;
    r = n-r > r? r : n - r;
    for(i = n, res = 1; i >= n-r; i--) res *= i;
    for(i = 1, res = 1; i <= r; i++) res /= i;

    return res;
}

int main(void){
    int N, L, R, space;
    int count;
    scanf("%d %d %d", &N, &L, &R);

    // Fix building
    // mid
    N -= 1;
    L -= 1;
    R -= 1;
    count = combination(L + R, L);

    // unfixed
    N -= (L + R);   // remain building
    space = L + R;
    count *= combination(N, space - 1);

    printf("%d\n", count);

    return 0;
}