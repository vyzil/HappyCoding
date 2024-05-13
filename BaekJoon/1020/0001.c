#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct _NODE{
    int num;
    struct _NODE *next;
} NODE;

int DIGIT_COUNT[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 5};

NODE *global_countDigit;
NODE *global_countRange;

void makeGlobalParam(){
    int i, j;
    int check;
    NODE *curNode, *newNode;

    global_countDigit = (NODE*)malloc(sizeof(NODE)*8);
    global_countRange = (NODE*)malloc(sizeof(NODE)*10);

    for(i = 0; i < 8 ; i++) global_countDigit[i].next = NULL;
    for(i = 0; i < 10; i++) global_countRange[i].next = NULL;

    for(i = 9; i >= 0 ; i--){
        newNode = (NODE*)malloc(sizeof(NODE));
        newNode->num = i;
        newNode->next = global_countDigit[DIGIT_COUNT[i]].next;
        global_countDigit[DIGIT_COUNT[i]].next = newNode;
    }

    for(i = 0; i < 10; i++){
        check = 0;
        curNode = &global_countRange[i];
        for(j = i; j < 10; j++){
            if((check & (1 << DIGIT_COUNT[j])) != 0) continue;
            newNode = (NODE*)malloc(sizeof(NODE));
            newNode->num = DIGIT_COUNT[j];
            newNode->next = NULL;
            curNode->next = newNode;
            curNode = curNode->next;
            check |= (1 << DIGIT_COUNT[j]);
        }
    }

    return;
}

void freeGlobalParam(){

    free(global_countDigit);
    free(global_countRange);
    return;
}

int main(void){
    int i, j;
    char iStr[16];
    long long iNum, resNum;
    int matchingNum, left, right, curNum, match;
    int curCount;
    NODE *curNode;
    makeGlobalParam();

    iNum = 0;
    scanf("%s", iStr);
    for(i = 0; i < strlen(iStr); i++)
        iNum = iNum * 10 + (iStr[i] - '0');

    resNum = iNum;
    matchingNum = 0;
    left = 0;
    right = 0;
    match = 0;
    for(i = strlen(iStr) - 1; i >= 0; i--){
        resNum /= 10;
        curNum = iStr[i] - '0';
        matchingNum += DIGIT_COUNT[iStr[i] - '0'];
        if(curNum + 1 > 9) {
            left += 2;
            right += 7;
            continue;
        }
        curNode = &global_countRange[curNum+1];
        while(curNode->next){
            if(curNode->next->num + left <= matchingNum && matchingNum <= curNode->next->num + right) {
                match = 1;
                break;
            }
            curNode = curNode->next;
        }
        if(match) break;

        left += 2;
        right += 7;
    }

    // Overflow Logic Should be Here
    if(match){
        curCount = curNode->next->num;
        curNode = &global_countDigit[curCount];
        while(curNode->next){        
            if(curNode->next->num > curNum) break;
            curNode = curNode->next;
        }
        resNum *= 10;
        resNum += curNode->next->num;
        matchingNum -= DIGIT_COUNT[curNode->next->num];
    }
    else {
        resNum = 1;
    }
    left  -= 2;
    right -= 7;

    // Reversing
    for(i++; i < strlen(iStr); i++){
        resNum *= 10;
        for(j = 0; j < 10; j++){
            if(DIGIT_COUNT[j] + left <= matchingNum && matchingNum <= DIGIT_COUNT[j] + right) break;
        }
        resNum += j;
        matchingNum -= DIGIT_COUNT[j];
        left -= 2;
        right -= 7;
    }
    
    printf("%lld\n", resNum - iNum);

    freeGlobalParam();
    return 0;
}