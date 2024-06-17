#include <stdio.h>

typedef struct _POINT{
    int x, y;
} POINT;

int main(void){
    int i;
    int N;
    int dist, idx;
    POINT prev, cur;

    scanf("%d", &N);
    scanf("%d %d", &cur.x, &cur.y);
    idx = 0;
    for(i = 0; i < N-1; i++){
        prev.x = cur.x; prev.y = cur.y;
        scanf("%d %d", &cur.x, &cur.y);
        dist  = (cur.x > prev.x ? 1 : -1) * (cur.x - prev.x);
        dist += (cur.y > prev.y ? 1 : -1) * (cur.y - prev.y);

        if(dist % 2) {
            idx = i+1;
            break;
        }
    }

    
    if(idx){
        printf("YES\n");
        printf("%d ", idx);
        for(i = 1; i <= N; i++){
            if(i != idx && i != idx+1){
                printf("%d ", i);
            }
        }
        printf("%d\n", idx+1);
    }
    else printf("NO\n");

    return 0;
}