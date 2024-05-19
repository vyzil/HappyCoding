#include <stdio.h>

#define ll long long
#define atoi(x) ((x) - 'A')
#define SIZE_MAX 12
#define NUM_MAX 10
#define SUM_MAX 100000000000000

int main(void){
    int i, j;
    int N;
    char input[SIZE_MAX + 1];
    int strSize;
    ll buf[NUM_MAX] = {0,}, alpha;
    int nonZero[NUM_MAX] = {0,};
    int value[NUM_MAX] = {-1,};

    for(i = 0; i < NUM_MAX; i++){
        buf[i] = 0;
        nonZero[i] = 0;
        value[i] = -1;
    }

    scanf("%d", &N);
    while(N--){
        scanf("%s", input);
        
        nonZero[atoi(input[0])] = 1;
        for(i = 0, alpha = 1; input[i]; i++) alpha *= 10; alpha /= 10;
        for(i = 0; input[i]; i++){
            buf[atoi(input[i])] += alpha;
            alpha /= 10;
        }
    }

    // select zero
    int minIdx, maxIdx, cnt; ll min, max, sum;
    min = SUM_MAX;
    cnt = 0;
    for(i = 0; i < NUM_MAX; i++){
        if(buf[i] == 0) break;
        else cnt++;
        if(nonZero[i]) continue;
        if(min > buf[i]) {
            min = buf[i];
            minIdx = i;
        }
    }
    if(cnt == NUM_MAX) value[minIdx] = 0;


    for(i = NUM_MAX-1; i > 0; i--){
        max = 0;
        maxIdx = -1;
        for(j = 0; j < NUM_MAX; j++){
            if(value[j] != -1) continue;
            if(max < buf[j]){
                max = buf[j];
                maxIdx = j;
            }
        }
        if(maxIdx == -1) break;
        value[maxIdx] = i;
    }

    sum = 0;
    for(i = 0; i < NUM_MAX; i++){
        if(value[i] > 0) sum += buf[i] * value[i];
    }

    printf("%lld\n", sum);

    return 0;
}