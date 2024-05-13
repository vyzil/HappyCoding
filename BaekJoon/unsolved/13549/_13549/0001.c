#include <stdio.h>

int main(void) {
    int iN, iK;
    int nBit, kBit, tmp;
    int count;
    
    scanf("%d %d", &iN, &iK);

    if(iN <= iK) {
        printf("%d\n", iK - iN);
        return 0;
    }

    nBit = 0; 
    kBit = 0;
    for(tmp = iN; tmp > 0; tmp /= 2) nBit++;
    for(tmp = iK; tmp > 0; tmp /= 2) kBit++;


    return 0;
}