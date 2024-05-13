#include <stdio.h>
#include <stdlib.h>

#define ll long long

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
    int curCase, curMeso; ll curDmg, totalTime;
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

    // highest dmg, for statement : useNum DP
    // MAX : 49 * O(13^2)
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

        // Brute-force
        maxMeso = 0;
        for(i = 0; i < (1 << bossNum); i++){
            curCase = i;
            totalTime = 0;
            curMeso = 0;
            for(j = 0; curCase > 0 ; j++){
                if(curCase & 1) {
                    totalTime += KILL_TIME(bossArr[j].hp, curDmg);
                    curMeso += bossArr[j].meso;
                }
                if(totalTime > 900) break;
                curCase >>= 1;
            }
            if(totalTime <= (ll)900 && maxMeso < curMeso) maxMeso = curMeso;
        }
        totalMeso += maxMeso;
    }
    printf("%lld\n", totalMeso);

finale:
    free(dmgHeap);
    free(bossArr);
    return 0;
}