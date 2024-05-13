#include <stdio.h>

int main(void){
    int i;
    int iN; 
    int iA, iB, iC;
    int windowMax[3], max0, max1, max2;
    int windowMin[3], min0, min1, min2;

    for(i = 0; i < 3; i++) {
        windowMax[i] = 0;
        windowMin[i] = 0;
    }

    scanf("%d", &iN);
    for(i = 0; i < iN; i++){
        scanf("%d %d %d", &iA, &iB, &iC);
        max0 = windowMax[0] > windowMax[1] ? windowMax[0] : windowMax[1];
        max2 = windowMax[1] > windowMax[2] ? windowMax[1] : windowMax[2];
        max1 = max0 > max2 ? max0 : max2;
        windowMax[0] = iA + max0;
        windowMax[1] = iB + max1;
        windowMax[2] = iC + max2;

        min0 = windowMin[0] < windowMin[1] ? windowMin[0] : windowMin[1];
        min2 = windowMin[1] < windowMin[2] ? windowMin[1] : windowMin[2];
        min1 = min0 < min2 ? min0 : min2;
        windowMin[0] = iA + min0;
        windowMin[1] = iB + min1;
        windowMin[2] = iC + min2;
    }

    max0 = windowMax[0] > windowMax[1] ? windowMax[0] : windowMax[1];
    max2 = windowMax[1] > windowMax[2] ? windowMax[1] : windowMax[2];
    max1 = max0 > max2 ? max0 : max2;

    min0 = windowMin[0] < windowMin[1] ? windowMin[0] : windowMin[1];
    min2 = windowMin[1] < windowMin[2] ? windowMin[1] : windowMin[2];
    min1 = min0 < min2 ? min0 : min2;

    printf("%d %d\n", max1, min1);

    return 0;
}