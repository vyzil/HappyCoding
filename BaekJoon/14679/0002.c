#include <stdio.h>
#include <math.h>

#define RES_MOD 1000000007
#define ATK_MOD 100
#define DEF_MOD 3
#define  HP_MOD 1000

#define isOP()  (YW.atk > DEF_MOD + HP_MOD) || (YW.def > ATK_MOD - 1 && YW.hp > HP_MOD - 1) ? 1 : 0

typedef struct OBJECT{
    long long atk;
    long long def;
    long long hp;
} object;


object YW, MON;
object pParam, aParam; // power, add
int monAtkArr[ATK_MOD + 2];
int monDefArr[DEF_MOD + 2];
int monHpArr [ HP_MOD + 2];


int fastPow(int n, int k, int mod){
    int res, tmp;
    if(n == 1) return 1;
    
    res = 1;
    tmp = n;

    while(k > 0){
        if(k%2) res = (res * tmp) % mod;
        k >>= 1;
        tmp = (tmp * tmp) % mod;
    }
    return res;
}

int fight(){    // 0 : YW win, 1 : MON win
    double ywDmg, monDmg;

    ywDmg = YW.atk - MON.def;
    if(ywDmg < 1) ywDmg = 1;
    monDmg = MON.atk - YW.def;
    if(monDmg < 1) monDmg = 1;
    if(ceil(YW.hp / monDmg) < ceil(MON.hp / ywDmg) ) return 1;

    return 0;
}

void absorb(){
    YW.atk += MON.atk;
    YW.def += MON.def;
    YW.hp  += MON.hp ;
    return;    
}

void nextChallenger(int num){
    MON.atk = monAtkArr[num % (ATK_MOD + 1) + 1];
    MON.def = monDefArr[num % (DEF_MOD + 1) + 1];
    MON.hp  = monHpArr [num % ( HP_MOD + 1) + 1];
    return;
}

void calcMonArr(){
    int i;
    monAtkArr[0] = MON.atk;
    monDefArr[0] = MON.def;
    monHpArr [0] = MON.hp;
    for(i = 1; i <= ATK_MOD + 1; i++) monAtkArr[i] = (fastPow(monAtkArr[i-1], pParam.atk, ATK_MOD) + aParam.atk) % ATK_MOD + 1;
    for(i = 1; i <= DEF_MOD + 1; i++) monDefArr[i] = (fastPow(monDefArr[i-1], pParam.def, DEF_MOD) + aParam.def) % DEF_MOD + 1;
    for(i = 1; i <= HP_MOD  + 1; i++) monHpArr [i] = (fastPow(monHpArr [i-1], pParam.hp,  HP_MOD)  + aParam.hp ) % HP_MOD  + 1;

    return;
}

int main(void){
    int i, mNum;

    scanf("%d", &mNum);
    scanf("%lld %lld %lld", &YW.atk,  &YW.def,  &YW.hp);
    scanf("%lld %lld %lld", &MON.atk, &MON.def, &MON.hp);
    scanf("%lld %lld", &pParam.atk, &aParam.atk);
    scanf("%lld %lld", &pParam.def, &aParam.def);
    scanf("%lld %lld", &pParam.hp , &aParam.hp);

    calcMonArr();

    if(fight()) {
        printf("-1\n");
        return 0;
    }
    absorb();

    for(i = 0; i < mNum; i++){
        nextChallenger(i);
        if(fight()) {
            printf("-1\n");
            return 0;
        }
        absorb();
        if(isOP()) break;
    }

    for(i++ ; i < mNum; i++){
        nextChallenger(i);
        absorb();
    }

    printf("%lld %lld %lld\n", YW.atk % RES_MOD, YW.def % RES_MOD, YW.hp % RES_MOD);

    return 0;
}