#include <stdio.h>

#define ll long long

const ll weight[5] = {1, 1000, 10000000, 100000000000, 100000000000000};

int main(void){
    int i;
    int N, num, input;
    char buffer[2002];
    ll A, B;
    scanf("%d", &N);

    while(N--){
        A = 0; B = 0;
        scanf("%d", &num);
        for(i = 0; i < num; i++){
            scanf("%d", &input);
            A += (weight[input]);
        }
        scanf("%d", &num);
        for(i = 0; i < num; i++){
            scanf("%d", &input);
            B += (weight[input]);
        }

        if(A > B) printf("A\n");
        else if (A < B) printf("B\n");
        else printf("D\n");
    }

    return 0;
}