#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define MAX_LV 200
#define MAX_N 626852
#define MAX_M 200
#define MAX_K 200
#define MAX_MOVING_TIME (ll)MAX_LV * (ll)MAX_N * (ll)MAX_K

int main(void){
    int i, j, k;
    int iN, iM, iK;
    int *userLevel, *monsterLevel;
    int *lvFloor, floor, lv; ll *floorCount;
    int s1, s2;
    int portalTime, walkTime; ll saveTime;
    ll totalMovingTime, minMovingTime, totalSaveTime;
    int res_s1, res_s2; ll res_st;

    scanf("%d %d %d", &iN, &iM, &iK);
    userLevel = (int*)malloc(sizeof(int)*iN);
    monsterLevel = (int*)malloc(sizeof(int)*iM);
    lvFloor = (int*)malloc(sizeof(int)*MAX_LV);
    floorCount = (ll*)malloc(sizeof(ll)*iM);
    

    for(i = 0; i < iN; i++) scanf("%d", &userLevel[i]);
    for(i = 0; i < iM; i++) scanf("%d", &monsterLevel[i]);


    // Count Floor to go for all user and all day
    for(i = 0; i < MAX_LV; i++) lvFloor[i] = -1;
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

    // For(Portal Case), calculate sum of saving time
    // Save shortest moving time
    minMovingTime = MAX_MOVING_TIME;
    s1 = 0;
    for(s2 = s1+1; s2 < iM; s2++){
        totalMovingTime = 0;
        totalSaveTime = 0;
        for(i = 0; i < iM; i++){
            if(floorCount[i] == 0) continue;
            walkTime = i;
            portalTime = s1 + (i - s2 > 0 ? i - s2 : s2 - i);
            saveTime = walkTime - portalTime;
            if(saveTime > 0) {
                totalSaveTime += saveTime * floorCount[i];
                totalMovingTime += portalTime * floorCount[i];
            }
            else totalMovingTime += walkTime * floorCount[i];
            if(totalMovingTime > minMovingTime) break;
        }
        if(minMovingTime > totalMovingTime){
            res_s1 = s1;
            res_s2 = s2;
            res_st = totalSaveTime;
            minMovingTime = totalMovingTime;
        }
    }

    printf("%d %d\n%lld\n", res_s1 + 1, res_s2 + 1, res_st);

    // free
    free(userLevel);
    free(monsterLevel);
    free(lvFloor);
    free(floorCount);

    return 0;
}