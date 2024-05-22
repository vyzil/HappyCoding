#include <stdio.h>
#include <string.h>

#define STR_MAX 10+1
#define N_MAX 200000

int main(void){
    int i;
    int N, B, X;
    char word[STR_MAX];
    char S[N_MAX][STR_MAX];
    int arr[N_MAX], cnt;
    int tri[N_MAX], triRev[N_MAX];

    scanf("%d %d", &N, &B);
    scanf("%s %d", word, &X);
    cnt = 0;
    for(i = 0; i < N; i++) {
        scanf("%s", S[i]);
        if(strcmp(S[i], word) == 0) cnt++;
        arr[i] = cnt;
    }

    tri[0] = arr[0];
    triRev[0] = arr[N-1];
    for(i = 1; i < N; i++){
        tri[i] = tri[i-1] + arr[i];
        triRev[i] = triRev[i-1] + arr[i];
    }
    
    int unit, period;
    int leftMax, midMax;
    int turn, numLeft, numUnit, inTri;
    // init
    turn = 0;
    unit = arr[N-1];
    numUnit = ((B-1)/N);
    inTri = tri[N-1];

    // calc period 
    #define ACCUM(i) (((i) * ((i)- 1))/2) * N * arr[N-1] + (i) * inTri
    #define LINE(i) ((i)/N) * arr[N-1] + ((i)%N > 0 ? arr[((i)%N) - 1] : 0)
    period = 0;
    period += ACCUM(numUnit); //((numUnit * (numUnit - 1))/2) * N * arr[N-1] + (numUnit) * inTri;
    for(i = 0; i < (B-1)%N; i++) period += (numUnit) * arr[N-1] + arr[i];
    leftMax = period;
    period <<= 1;
    period += LINE(B); // (B/N) * arr[N-1] + (B%N > 0 ? arr[(B%N) - 1] : 0);
    midMax = period - leftMax;
    period -= arr[0];

    // move base to right period
    int div;
    div = X/period;
    if(X%period == 0) div--;
    printf(":: %d\n", div);
    
    turn = div * (2*B -1);
    numLeft = X - div * period;
    printf("%d %d\n", turn, numLeft);
    

    // check if left/mid/right 0/1/2
    #define LEFT 0
    #define MID 1
    #define RIGHT 2
    int status = -1;
    
    if(numLeft <= leftMax) status = LEFT;
    else if(numLeft <= midMax) status = MID;
    else status = RIGHT;

    if(status == MID) {
        turn += B;
        printf("%d\n", turn);
        return 0;
    }

    // Binary Search Unit
    int high, low, mid;
    int line;

    low = 0;
    high = (B-1) / N;
    if(status == LEFT){
        printf("LEFT : %d\n", turn);
        while(low < high){
            mid = (low + high) / 2;
            if(ACCUM(mid) < numLeft) low = mid+1;
            else high = mid;
        }
        if(numLeft <= ACCUM(low)) low--;
        printf("%d\n", low);
        printf("1. %d %d\n", numLeft, ACCUM(low));
        turn += low * N;
        numLeft -= ACCUM(low);
        line = low * N;
        printf("LEFT(%d) : %d\n", turn, numLeft);
        while(numLeft > 0){
            turn++;
            line++;
            numLeft -= LINE(line);
            printf("\t%d %d\n", numLeft, LINE(line));
        }
    }
    else if(status == RIGHT){
        printf("RIGHT : %d\n", turn);
        int minus;
        while(low < high){
            mid = (low + high) / 2;
            if(ACCUM(mid) < period + arr[0] - numLeft) low = mid+1;
            else high = mid;
        }
        // if(numLeft <= (period + arr[0]) - ACCUM(low)) low++;
        printf("-- %d\n", low);
        printf("\t%d %d\n", numLeft, ACCUM(low));
        turn += 2*B - low;
        numLeft += ACCUM(low) - (period + arr[0]);
        printf("%d\n", low);
        printf("\t%d %d\n", numLeft, ACCUM(low));
        line = B - low;        
        printf("RIGHT: %d\n", turn);
        while(numLeft > 0){
            turn++;
            line++;
            numLeft -= LINE(line);
            printf("%d %d\n", numLeft, LINE(line));
            printf("in %d %d\n", numLeft, LINE(line));
        }
    }

    printf("%d\n", turn);


    return 0;
}