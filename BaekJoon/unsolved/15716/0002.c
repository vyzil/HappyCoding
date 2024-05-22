#include <stdio.h>
#include <string.h>

#define DEBUG

#define STR_MAX 10+1
#define N_MAX 200000

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
#define LINE(i) ((((i)+1)/N) * arr[N-1] + (((i)+1)%N ? arr[((i)+1)%N - 1] : 0))
#define ACCUM(i) \
({\
    int _line;\
    int _unitNum = ((i)/N);\
    int _res = (((_unitNum) * (_unitNum - 1)) / 2) * N * arr[N-1] + _unitNum * triUnit; \
    for(_line = N * _unitNum; _line <= i; _line++){\
        _res += LINE(_line);\
    }\
    _res;\
})\

int main(void){
    int i;
    int N, B, X;
    char word[STR_MAX];
    char S[N_MAX][STR_MAX];
    int arr[N_MAX], cnt;
    int triUnit;

    scanf("%d %d", &N, &B);
    scanf("%s %d", word, &X);
    cnt = 0;
    triUnit = 0;
    for(i = 0; i < N; i++) {
        scanf("%s", S[i]);
        if(strcmp(S[i], word) == 0) cnt++;
        arr[i] = cnt;
        triUnit += arr[i];
    }

    if(N == 1){
        printf("%d\n", X);
        return 0;
    }

    // calc period
    int period = 0;
    period = (2 * ACCUM(B-2)) + LINE(B-1) - arr[0];

#ifdef DEBUG
    printf("arr[i]   :"); for(i = 0; i < N; i++) printf("%d ", arr[i]); printf("\n");
    printf("LINE(i)  :"); for(i = 0; i < B-1; i++) printf("%d ", LINE(i)); printf("\n");
    printf("ACCUM(i) :"); for(i = 0; i < B-1; i++) printf("%d ", ACCUM(i)); printf("\n");
    printf("%d\n", period);
#endif

    // move base to right period
    int turn, pass, curNum, curRest;
    pass = (X/period) - (X%period? 0 : 1);
    turn = pass * (2*(B-1));
    curNum = pass * period;
    curRest = X - curNum;
    
#ifdef DEBUG
    printf("==========================\n");
    printf("Passed Period : %d\n", pass);
    printf("+ turn : %d\n", turn);
    printf("+ turn : %d\n", turn);
    printf("+ cNum : %d\n", curNum);
    printf("+ rest : %d\n", curRest);
#endif

    // check phase to check, Increasing or Decreasing
    // Search appropriate kN first, and then search exact line
    int low, mid, high, line;
    if(curRest <= ACCUM(B-1)){ // Increasing Phase
        low = 0; high = (B-1) / N;
        while(low < high){
            mid = (low + high) / 2;
            if(ACCUM(mid * N) <= curRest) low = mid + 1;
            else high = mid;
        }
        low--;
        line = low * N;
        turn += line;
        curNum += ACCUM(line);
        curRest = X - curNum;

    #ifdef DEBUG
        printf("==========================\n");
        printf("Increasing Phase\n");
        printf("+ line : %d\n", line);
        printf("+ low  : %d\n", low);
        printf("+ turn : %d\n", turn);
        printf("+ cNum : %d\n", curNum);
        printf("+ rest : %d\n", curRest);
    #endif

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

    #ifdef DEBUG
        printf("==========================\n");
        printf("Decreasing Phase, INIT\n");
        printf("+ turn : %d\n", turn);
        printf("+ cNum : %d\n", curNum);
        printf("+ rest : %d\n", curRest);
    #endif

        low = 0; high = (B-2) / N;
        while(low < high){
            mid = (low + high) / 2;
            if(ACCUM(mid * N) <= -curRest) low = mid + 1;
            else high = mid;
        }
        
        line = low * N;
        turn -= line;
        curNum -= ACCUM(line-1);
        curRest = X - curNum;

    #ifdef DEBUG
        printf("==========================\n");
        printf("Decreasing Phase\n");
        printf("+ accum: %d\n", ACCUM(line-1));
        printf("+ line : %d\n", line);
        printf("+ low  : %d\n", low);
        printf("+ turn : %d\n", turn);
        printf("+ cNum : %d\n", curNum);
        printf("+ rest : %d\n", curRest);
    #endif

        while(curRest > 0){
            line--;
            turn++;
            curNum += LINE(line);
            curRest = X - curNum;
        }
    }

    printf("%d\n", turn+1);

    return 0;
}