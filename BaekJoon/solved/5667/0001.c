#include <stdio.h>

#define MODE0 0
#define MODE1 1

int main(void){
    int i;
    int N;
    int X, cnt0, cnt1, mode0, mode1;

    while(scanf("%d", &N) != EOF){
        mode0 = MODE0;      
        cnt0 = 0;

        mode1 = MODE1;
        cnt1 = 0;

        for(i = 0; i < N; i++) {
            scanf("%d", &X);
            // mode0
            if(mode0 == MODE0 && X == 0) {
                mode0 = MODE1;
                cnt0++;
            }
            else if (mode0 == MODE1 && X == 0) mode0 = MODE0;
            else if (mode0 == MODE0 && X == 1) mode0 = MODE1;

            // mode1
            if(mode1 == MODE0 && X == 0) {
                mode1 = MODE1;
                cnt1++;
            }
            else if (mode1 == MODE1 && X == 0) mode1 = MODE0;
            else if (mode1 == MODE0 && X == 1) mode1 = MODE1;
        }

        if(mode1 == MODE0) cnt1++;

        printf("%d\n", cnt0 < cnt1 ? cnt0 : cnt1);
    }

    return 0;
}