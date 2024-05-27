#include <stdio.h>

#define sq(x) ((x)*(x))

int main(void){
    int TC;
    int x1, y1, x2, y2, r1, r2;
    int dist, res;

    scanf("%d", &TC);
    while(TC--){
        scanf("%d %d %d %d %d %d", &x1, &y1, &r1, &x2, &y2, &r2);
        dist = sq(x1-x2) + sq(y1-y2);
        if(dist == 0 && r1 == r2) res = -1;
        else if (dist == sq(r1+r2) || dist == sq(r1-r2)) res = 1;
        else if (sq(r1-r2) < dist && dist < sq(r1+r2))res = 2;
        else res = 0;
        printf("%d\n", res);
    }

    return 0;
}