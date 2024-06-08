#include <stdio.h>

#define E_MODE 1
#define W_MODE 2

int main(void){
    int i;
    int N; 
    char iStr[1001];
    int mode, cnt; 

    scanf("%d", &N);
    scanf("%s", iStr);

    mode = E_MODE;
    cnt = 1;
    for(i = 0; i < N; i++){
        if(iStr[i] == 'E' && mode == W_MODE){
            cnt++;   
            mode = E_MODE;
        }
        else if(iStr[i] == 'W' && mode == E_MODE) mode = W_MODE;
    }

    printf("%d\n", cnt);

    return 0;
}