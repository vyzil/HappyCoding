#include <stdio.h>

int main(void){
    int i;
    int diff[4], res[3];
    int a, b;
    for(i = 0; i < 4; i++){
        scanf("%d %d", &a, &b);
        diff[i] = b - a;
    }


    for(i = 3; i > 0; i--){
        res[i-1] = diff[i];
        diff[i-1] += diff[i];
    }

    for(i = 0; i < 3; i++) printf("%d\n", res[i]);

}