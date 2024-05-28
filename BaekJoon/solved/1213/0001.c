#include <stdio.h>
#include <string.h>

#define alpha ('Z' - 'A' + 1)
#define atoi(x) ((x) - 'A')
#define itoa(x) ((x) + 'A')

int main(void){
    int i, j, idx;
    int len;
    char input[51];
    char res[51];
    int buffer[alpha] = {0, };
    int one = 0;

    scanf("%s", input);
    for(len = 0; input[len]; len++){
        buffer[atoi(input[len])]++;
    }

    one = len % 2;
    idx = 0;
    res[len] = '\0';
    for(i = 0; i < alpha; i++){
        if(buffer[i] > 1){
            for(j = 0; j < buffer[i]/2; j++) {
                res[idx] = itoa(i);
                res[len-1-idx] = itoa(i);
                idx++;
            }
            buffer[i] %= 2;
        }
        if(buffer[i]){
            if(one--) res[len/2] = itoa(i);
            else{
                strcpy(res, "I'm Sorry Hansoo\0");
                break;
            }
        }
    }
    printf("%s\n", res);
    

    return 0;
}