#include <stdio.h>

int main(void){
    int cnt; double score;
    char buf[1001];
    scanf("%s", buf);

    cnt = 0; score = 0.0;
    for(int i = 0; buf[i]; i++){
        if(buf[i] == '+') score += 0.5;
        else{
            score += ('E'-buf[i] > 0 ? 'E'-buf[i] : 0);
            cnt++;
        }
    }

    printf("%f\n", score/cnt);

}