#include <stdio.h>

#define P_MAX 51

int main(void){
    int i, j;
    int N, P[10], M;
    int num[10] = {0};

    scanf("%d", &N);
    for(i = 0; i < N; i++) scanf("%d", &P[i]);
    scanf("%d", &M);

    // 0 제외 가장 싼 큰 수
    int used;
    int min, minIdx;
    min = P_MAX;
    minIdx = -1;
    
    used = 0;
    for(i = 1; i < N; i++){
        if(min > P[i]) min = P[i];
        if(min == P[i]) minIdx = i;
    }

    if(minIdx == -1 || P[minIdx] > M) {
        num[0]++;
        goto finale;
    }
    used = P[minIdx];
    num[minIdx]++;

    // 0 포함 가장 싼 큰 수
    min = P_MAX;
    minIdx = -1;
    for(i = 0; i < N; i++){
        if(min > P[i]) min = P[i];
        if(min == P[i]) minIdx = i;
    }

    num[minIdx] += (M - used) / min;
    used += ((M - used) / min) * min;

    // 남은 금액보고 큰 숫자로 바꾸기
    int change, cnt;

    for(i = N-1; i > 0; i--){  // change to i
        for(j = 0; j < i; j++){ // change from j
            if(num[j] == 0) continue;
            change =  P[i] - P[j];
            cnt = num[j];
            if(change != 0) cnt = (cnt > ((M - used) / change) ? ((M - used) / change) : cnt);
            num[i] += cnt;
            num[j] -= cnt;
            used += change * cnt;
        }
    }

finale:
    for(i = N-1; i >= 0; i--){
        while(num[i]-- > 0) printf("%d", i);
    }
    printf("\n");

    return 0;
}