#include <stdio.h>
#include <string.h>


#define STR_MAX 12
#define N_MAX 200001

#define ll long long
typedef unsigned __int128 u128;

void print_u128(u128 value) {
    char buffer[40];
    int i = 0;
    do {
        buffer[i++] = (value % 10) + '0';
        value /= 10;
    } while (value != 0);
    while (--i >= 0) {
        putchar(buffer[i]);
    }
    // putchar('\n');
}

/*
 *
 * N = 3, B = 4
 * 0 : a
 * 1 : a b
 * 2 : a b c    (B-2)
 * 3 : a b c a  (B-1)
 * 4 : a b c
 * 5 : a b
 * ---- One Period ----
 * 4 : a
 */


// Only available in increasing phase
// i in below macro is idx of line
// LINE(i) returns # of words at line i, 
// ACCUM(i) returns # of words until line i in that period
#define LINE(i) ((((u128)(i)+1)/N) * arr[N-1] + (((u128)(i)+1)%N ? arr[((u128)(i)+1)%N - 1] : 0))
#define ACCUM(i) \
({\
    u128 _line;\
    u128 _unitNum = ((u128)(i)/N);\
    u128 _res = (((_unitNum) * (_unitNum - 1)) / 2) * N * arr[N-1] + _unitNum * triUnit; \
    for(_line = N * _unitNum; _line <= (u128)i; _line++){\
        _res += LINE(_line);\
    }\
    _res;\
})\

int main(void){
    ll i;
    ll N;
    ll B, X;
    char word[STR_MAX];
    char S[STR_MAX];
    ll arr[N_MAX], cnt;
    ll triUnit;

    scanf("%lld %lld", &N, &B);
    scanf("%s %lld", word, &X);
    cnt = 0;
    triUnit = 0;
    for(i = 0; i < N; i++) {
        scanf("%s", S);
        if(strcmp(S, word) == 0) cnt++;
        arr[i] = cnt;
        triUnit += arr[i];
    }

    if(N == 1){
        printf("%lld\n", X);
        return 0;
    }

    // calc period
    u128 period = 0;
    period = (2 * ACCUM(B-2)) + LINE(B-1) - arr[0];    
    
    // move base to right period
    ll turn, pass, curNum, curRest;
    pass = (ll)(((u128)X/period) - (u128)((u128)X%period? 0 : 1));
    turn = pass * (2*(B-1));
    curNum = pass * period;
    curRest = X - curNum;

    // check phase to check, Increasing or Decreasing
    // Search appropriate kN first, and then search exact line
    ll low, mid, high, line;
    if((u128)curRest <= ACCUM(B-1)){ // Increasing Phase
        low = 0; high = (B-1) / N;
        while(low < high){
            mid = (low + high) / 2;
            if(ACCUM(mid * N) <= (u128)curRest) low = mid + 1;
            else high = mid;
        }
        low--;
        line = low * N;
        turn += line;
        curNum += ACCUM(line);
        curRest = X - curNum;

        while(curRest > 0){
            line++;
            turn++;
            curNum += LINE(line);
            curRest = X - curNum;
        }
    }
    else {  // decreasing Phaselow = 0; high = (B-1) / N;
        turn += 2*(B - 1);
        curNum += period + arr[0];
        curRest = X - curNum;

        low = 0; high = (B-2) / N;
        while(low < high){
            mid = (low + high) / 2;
            if(ACCUM(mid * N) <= (u128)(-curRest)) low = mid + 1;
            else high = mid;
        }
        
        line = low * N;
        turn -= line;
        curNum -= (ll)ACCUM(line-1);
        curRest = X - curNum;

        while(curRest > 0){
            line--;
            turn++;
            curNum += LINE(line);
            curRest = X - curNum;
        }
    }

    print_u128(turn+1);

    return 0;
}