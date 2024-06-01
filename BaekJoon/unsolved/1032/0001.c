#include <stdio.h>

int main(void){
    int i;
    int N;
    char res[51];
    char input[51];

    scanf("%d", &N);
    scanf("%s", res);
    while(--N){
        scanf("%s", input);
        for(i = 0; res[i]; i++){
            if(res[i] != '?' && res[i] != input[i]) res[i] = '?';
        }
    }
    printf("%s\n", res);
}