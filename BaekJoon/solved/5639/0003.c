// 포기 :
// Others 코드를 reversive fuction call하지 않고 작성해보려고 했으나
// 어차피 필요한 메모리 공간이 function call이랑 크게 차이가 없음
// 근데 코드는 매우 길어짐

#include <stdio.h>

#define KEY_MAX 1000000

int main(void){
    int i;
    int iNum;
    int iArr[10000], arrSize;
    int rStart[10000], rEnd[10000];
    int curIdx;

    arrSize = 0;
    while(scanf("%d", &iNum) != EOF) iArr[arrSize++] = iNum;

    for(i = 0; i < arrSize; i++) rStart[i] = 0;
    curIdx = 0;
    rEnd[0] = arrSize-1;
    while(curIdx >= 0){
        if(rStart[curIdx] == 0){
            for(i = curIdx+1; i < rEnd[curIdx]; i++){
                if(iArr[curIdx] < iArr[i]) break;
            }
            rStart[curIdx] = i;
            if(rEnd[curIdx+1] == 0) {
                rEnd[curIdx+1] = i - 1;
                curIdx = curIdx + 1;
                continue;
            }
            if(rEnd[i] == 0) {
                rEnd[i] = rEnd[curIdx];
                curIdx = i;
                continue;
            }
        }
        
    }


    return 0;
}