#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define MAX_LV 200
#define MAX_N 626852
#define MAX_M 200
#define MAX_K 200
#define MAX_MOVING_TIME (ll)MAX_LV * MAX_N * MAX_K
#define DEBUG(arr,max)  for(i = 0; i < max; i++) printf("%d ", arr[i]);printf("\n");

int main(void){
    int i, j, k;
    int iN, iM, iK;
    int *userLevel, *monsterLevel;
    int *lvFloor, *floorCount, floor, lv;
    int s1, s2;
    int portalTime, walkTime, saveTime;
    ll totalMovingTime, minMovingTime, totalSaveTime;
    int res_s1, res_s2, res_st;

    scanf("%d %d %d", &iN, &iM, &iK);
    userLevel = (int*)malloc(sizeof(int)*iN);
    monsterLevel = (int*)malloc(sizeof(int)*iM);
    lvFloor = (int*)malloc(sizeof(int)*MAX_LV);
    floorCount = (int*)malloc(sizeof(int)*iM);
    

    for(i = 0; i < iN; i++) scanf("%d", &userLevel[i]);
    for(i = 0; i < iM; i++) scanf("%d", &monsterLevel[i]);
    for(i = 0; i < MAX_LV; i++) lvFloor[i] = -1;


    // Count Floor to go for all user and all day
    for(i = 0; i < iM; i++) lvFloor[monsterLevel[i]] = i;
    floor = lvFloor[0];
    for(i = 1; i < MAX_LV; i++) {
        if(lvFloor[i] != -1) floor = lvFloor[i];
        else lvFloor[i] = floor;
    }
    
    for(i = 0; i < iM; i++) floorCount[i] = 0;
    for(i = 0; i < iN; i++){
        lv = userLevel[i];
        for(j = lv; (j < lv + iK) && (j < MAX_LV); j++) {
            floorCount[lvFloor[j]]++;
        }
    }

    DEBUG(lvFloor, MAX_LV);
    DEBUG(floorCount, iM);

    // For(Portal Case), calculate sum of saving time
    // save shortest time
    minMovingTime = MAX_MOVING_TIME;
    for(s1 = 0; s1 < iM; s1++){
        for(s2 = s1+1; s2 < iM; s2++){
            totalMovingTime = 0;
            totalSaveTime = 0;
            for(i = 0; i < iM; i++){
                if(floorCount[i] == 0) continue;
                walkTime = i;
                portalTime = s1 + (i - s2 > 0 ? i - s2 : s2 - i);
                saveTime = walkTime - portalTime;
                totalMovingTime += (saveTime > 0 ? portalTime : walkTime) * floorCount[i];
                if(saveTime > 0) totalSaveTime += saveTime * floorCount[i];
            }
            if(minMovingTime > totalMovingTime){
                res_s1 = s1;
                res_s2 = s2;
                res_st = totalSaveTime;
                minMovingTime = totalMovingTime;
            }
        }
    }

    printf("%d %d\n%d\n", res_s1 + 1, res_s2 + 1, res_st);

    // free
    free(userLevel);
    free(monsterLevel);
    free(lvFloor);
    free(floorCount);

    return 0;
}