#include <stdio.h>
#include <stdlib.h>

typedef struct POINT{
    int x;
    int y;
} point;

typedef struct EVENT{
    int distance;
    point car1;
    point car2;
} evnt;

int main(void){
    int i, j;
    int N, W;
    int curX, curY, case1Distance, case2Distance;
    evnt tmp[2];
    evnt DP[2];
    int *DP_seq[2];
    int idx, *seq;
        
    scanf("%d", &N);
    scanf("%d", &W);

    DP_seq[0] = (int*)malloc(sizeof(int)*(W+1));
    DP_seq[1] = (int*)malloc(sizeof(int)*(W+1));

    DP[0].distance = 0; DP[1].distance = 0;
    DP[0].car1.x = 1;   DP[1].car1.x = 1; 
    DP[0].car1.y = 1;   DP[1].car1.y = 1;
    DP[0].car2.x = N;   DP[1].car2.x = N; 
    DP[0].car2.y = N;   DP[1].car2.y = N;

    for(i = 1; i <= W; i++){
        scanf("%d %d", &curX, &curY);
        
        // DP0 (Car1 solve)
        case1Distance = DP[0].distance + abs(DP[0].car1.x - curX) + abs(DP[0].car1.y - curY);  // privious Car 1 solved
        case2Distance = DP[1].distance + abs(DP[1].car1.x - curX) + abs(DP[1].car1.y - curY);  // privious Car 2 solved
        if(case1Distance <= case2Distance){  // prev, car1 solved
            tmp[0].distance = case1Distance;
            tmp[0].car2.x = DP[0].car2.x;
            tmp[0].car2.y = DP[0].car2.y;
            DP_seq[0][i] = 1;
        }
        else {                              // prev, car2 solved
            tmp[0].distance = case2Distance;
            tmp[0].car2.x = DP[1].car2.x;
            tmp[0].car2.y = DP[1].car2.y;
            DP_seq[0][i] = 2;
        }
        tmp[0].car1.x = curX;
        tmp[0].car1.y = curY;
        
        // DP1 (Car2 solve)
        case1Distance = DP[0].distance + abs(DP[0].car2.x - curX) + abs(DP[0].car2.y - curY);  // privious Car 1 solved
        case2Distance = DP[1].distance + abs(DP[1].car2.x - curX) + abs(DP[1].car2.y - curY);  // privious Car 2 solved
        if(case1Distance <= case2Distance){  // prev, car1 solved
            tmp[1].distance = case1Distance;
            tmp[1].car1.x = DP[0].car1.x;
            tmp[1].car1.y = DP[0].car1.y;
            DP_seq[1][i] = 1;
        }
        else {                              // prev, car2 solved
            tmp[1].distance = case2Distance;
            tmp[1].car1.x = DP[1].car1.x;
            tmp[1].car1.y = DP[1].car1.y;
            DP_seq[1][i] = 2;
        }
        tmp[1].car2.x = curX;
        tmp[1].car2.y = curY;

        for(j = 0; j < 2; j++){
            DP[j].distance = tmp[j].distance;
            DP[j].car1.x = tmp[j].car1.x;
            DP[j].car1.y = tmp[j].car1.y;
            DP[j].car2.x = tmp[j].car2.x;
            DP[j].car2.y = tmp[j].car2.y;
        }
    }

    seq = (int*)malloc(sizeof(int)*W);
    idx = (DP[0].distance > DP[1].distance?  1 : 0);
    printf("%d\n", (DP[0].distance > DP[1].distance?  DP[1].distance : DP[0].distance));
    for(i = W; i > 0; i--){
        seq[i - 1] = idx + 1;
        idx = DP_seq[idx][i] - 1;
    }
    for(i = 0; i < W; i++) printf("%d\n", seq[i]);

    return 0;
}
