#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000
#define CTOI(c) ((c) - '0')

int main(void){
    int i, cLen;
    int dp[3] = {0, 0, 0};
    char cipher[5002];
    
    scanf("%s", cipher);
    cLen = strlen(cipher);
    
    if(cLen <= 0 || cLen == 1 && cipher[0] == '0') {
        printf("0\n");
        return 0;
    }
    if(cLen == 1){
        printf("1\n");
        return 0;
    }

    if(CTOI(cipher[0]) != 0) dp[0] = 1;
    if(CTOI(cipher[1]) != 0) dp[1] = dp[0];
    if(CTOI(cipher[0]) != 0 && CTOI(cipher[0]) * 10 + CTOI(cipher[1]) <= 26) dp[1] += 1;
    for(i = 2; cipher[i]; i++) {
        dp[i%3] = 0;
        if(CTOI(cipher[i]) != 0) dp[i%3] = dp[(i-1)%3];
        if(CTOI(cipher[i-1]) != 0 && CTOI(cipher[i-1]) * 10 + CTOI(cipher[i]) <= 26) dp[i%3] = (dp[i%3] + dp[(i-2)%3]) % MOD;
    }

    printf("%d\n", dp[(cLen-1)%3]);

    return 0;
}