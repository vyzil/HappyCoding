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
    ll *dmgArr, iDmg;
    int curIdx, parentIdx, childIdx;
    BOSS *bossArr;
    int curCase, curMeso; ll curDmg, totalTime;
    int maxMeso; ll totalMeso;

    scanf("%d %d %d", &charNum, &useNum, &bossNum);
    dmgArr = (ll*)malloc(sizeof(ll)*charNum);
    bossArr = (BOSS*)malloc(sizeof(BOSS)*bossNum);
    for(i = 0; i < charNum; i++) scanf("%lld", &dmgArr[i]);    
    for(i = 0; i < bossNum; i++) scanf("%lld %d", &bossArr[i].hp, &bossArr[i].meso);

    // highest dmg, for statement : useNum DP
    // MAX : 49 * O(13^2)
    totalMeso = 0;
    while(useNum--){        
        curDmg = 0;
        for(i = 0; i < charNum; i++){
            if(curDmg < dmgArr[i]) {
                curDmg = dmgArr[i];
                curIdx = i;
            }
        }
        dmgArr[curIdx] = 0;

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
    free(dmgArr);
    free(bossArr);
    return 0;
}