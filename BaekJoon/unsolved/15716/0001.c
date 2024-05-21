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

    scanf("%d %d", &N, &B);
    scanf("%s %d", word, &X);
    cnt = 0;
    for(i = 0; i < N; i++) {
        scanf("%s", S[i]);
        if(strcmp(S[i], word) == 0) cnt++;
        arr[i] = cnt;
    }
    


    return 0;
}