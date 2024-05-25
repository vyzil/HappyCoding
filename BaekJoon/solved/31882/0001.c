#include <stdio.h>
#include <stdlib.h> 

#define ll long long

#define POINT(k) (((k)*((k)+1)*((k)+2))/6)

int main(void){
    int i;
    int N;
    char *input;
    ll res, adding;

    scanf("%d", &N);
    input = (char*)malloc(sizeof(char)*(N+1));
    scanf("%s", input);

    res = 0;
    adding = 0;
    for(i = 0; i <= N; i++){
        if(input[i] == '2') adding++;
        else {
            if(adding) res += POINT(adding);
            adding = 0;
        }
    }
    printf("%lld\n", res);

    free(input);

    return 0;
}