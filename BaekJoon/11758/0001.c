#include <stdio.h>

typedef struct POINT{
    int x;
    int y;    
} point;

int main(void){
    point P1, P2, P3;
    int A[3]; // A[0] * x + A[1] * y + A[2] = 0
    int res;

    scanf("%d %d", &P1.x, &P1.y);
    scanf("%d %d", &P2.x, &P2.y);
    scanf("%d %d", &P3.x, &P3.y);

    A[0] = - (P2.y - P1.y);
    A[1] =   (P2.x - P1.x);
    A[2] = - (A[0] * P1.x + A[1] * P1.y);

    res = A[0] * P3.x + A[1] * P3.y + A[2];
    printf("%d\n", (res > 0) - (res < 0));

    return 0;
}