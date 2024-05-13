#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *  <num> : A, B, C ...
 *  <opA> : + -
 *  <opB> : * /
 *  <bracket> : '('
 *  
 *  If <num> comes, print <num>, and print <opB> if <opB> is on top of the stack.
 *  If <opA> comes, pop and print until it reaches <bracket>, push new <opA>
 *  If <opB> comes, pop <opB> until it reaches <bracket> if there is, and push new <opA>
 *  If <bracket> comes, push to stack
 *  If ')' comes, pop and print until it reaches <bracket>
 * 
 *  
 */

int main(void){
    int i;
    char inputStr[101];
    char *opArr;
    char curC;
    int inputLen;
    int opTop;
    

    scanf("%s", inputStr);
    inputLen = strlen(inputStr);
    opArr = (char*)malloc(inputLen);

    i = 0;
    opTop = 0;
    while(inputStr[i] != '\0'){
        curC = inputStr[i];
        if('A' <= curC && curC <= 'Z'){ // <num>
            printf("%c", curC);
            if(opTop > 0 && (opArr[opTop-1] == '*' || opArr[opTop-1] == '/')) printf("%c", opArr[--opTop]);
        }
        else if(curC == '+' || curC == '-'){ // <opA>
            while(opTop > 0 && opArr[opTop-1] != '('){
                printf("%c", opArr[--opTop]);
            }
            opArr[opTop++] = curC;
        }
        else if(curC == '*' || curC == '/'){ // <opB>
            while(opTop > 0 && (opArr[opTop-1] == '*' || opArr[opTop-1] == '/')) {
                printf("%c", opArr[--opTop]);
            }
            opArr[opTop++] = curC;
        }
        else if(curC == '(') { // <bracket>
            opArr[opTop++] = curC;
        }
        else if(curC == ')') {
            while(opArr[--opTop] != '('){
                printf("%c", opArr[opTop]);
            }
        }

        i++;
    }

    while(opTop > 0){
        printf("%c", opArr[--opTop]);
    }

    printf("\n");
    free(opArr);

    return 0;
}