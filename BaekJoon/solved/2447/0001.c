#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i, j, r, c;
    int N, div, isStar;
    char *buff;
    scanf("%d", &N);
    buff = (char*)malloc(sizeof(char)*N);

    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            r = i;
            c = j;
            isStar = 1;
            div = N/3;
            while(div){
                if(r / div == 1 && c / div == 1){
                    isStar = 0;
                    break;
                }
                r -= (r / div) * div;
                c -= (c / div) * div;
                div /= 3;
            }
            if(isStar) buff[j] = '*';
            else buff[j] = ' ';
        }
        printf("%s\n", buff);
    }

    free(buff);

    return 0;
}