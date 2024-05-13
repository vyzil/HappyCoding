#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define TIME_LIMIT 900

// KILLTIME(boss_hp, dmg)
#define KILL_TIME(x, y) (((ll)(x) / (ll)(y)) + ((ll)(x) % (ll)(y) ? 1 : 0))

typedef struct _BOSS{
    ll hp;
    int meso;
} BOSS;

int main(void){
    int i, j;
    int charNum, useNum, bossNum;
    ll *dmgHeap, iDmg;
    int curIdx, parentIdx, childIdx;
    BOSS *bossArr;
    ll DP[TIME_LIMIT+1];
    ll curDmg, curKillTime;
    int maxMeso; ll totalMeso;    

    scanf("%d %d %d", &charNum, &useNum, &bossNum);
    dmgHeap = (ll*)malloc(sizeof(ll)*(charNum + 1)); // max heap
    bossArr = (BOSS*)malloc(sizeof(BOSS)*bossNum);

    dmgHeap[0] = 0;
    for(i = 0; i < charNum; i++) {
        scanf("%lld", &iDmg);
        // insert Heap
        dmgHeap[0]++;
        curIdx = dmgHeap[0];
        while(curIdx > 1){
            parentIdx = curIdx / 2;
            if(dmgHeap[parentIdx] > iDmg) break;
            dmgHeap[curIdx] = dmgHeap[parentIdx];
            curIdx = parentIdx;
        }
        dmgHeap[curIdx] = iDmg;
    }
    
    for(i = 0; i < bossNum; i++) scanf("%lld %d", &bossArr[i].hp, &bossArr[i].meso);

    totalMeso = 0;
    while(useNum--){        
        curDmg = dmgHeap[1];
        // deleteHeap
        curIdx = 1;
        while(curIdx*2 < dmgHeap[0]){
            childIdx = curIdx*2;
            if(childIdx + 1 < dmgHeap[0] && dmgHeap[childIdx + 1] > dmgHeap[childIdx]) childIdx++;
            if(dmgHeap[childIdx] < dmgHeap[dmgHeap[0]]) break;
            dmgHeap[curIdx] = dmgHeap[childIdx];
            curIdx = childIdx;
        }
        dmgHeap[curIdx] = dmgHeap[dmgHeap[0]];
        dmgHeap[0]--;

        // DP
        for(i = 0; i <= TIME_LIMIT; i++) DP[i] = 0;
        for(i = 0; i < bossNum; i++){
            curKillTime = KILL_TIME(bossArr[i].hp, curDmg);
            for(j = TIME_LIMIT; j >= curKillTime; j--){
                if(DP[j] < DP[j - curKillTime] + bossArr[i].meso) DP[j] = DP[j - curKillTime] + bossArr[i].meso;
            }
        }
        maxMeso = 0;
        for(i = 0; i <= TIME_LIMIT; i++) {
            if(maxMeso < DP[i]) maxMeso = DP[i];
        }
        totalMeso += maxMeso;
    }
    printf("%lld\n", totalMeso);

finale:
    free(dmgHeap);
    free(bossArr);
    return 0;
}