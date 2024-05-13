#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X,Y) (((X) < (Y)) ? (X) : (Y))

char ELEMENT[6][3] = {
    {'S', 'R', 'W'},
    {'W', 'S', 'R'},
    {'R', 'W', 'S'},
    {'S', 'W', 'R'},
    {'R', 'S', 'W'},
    {'W', 'R', 'S'}
};

int main(void){
    int i, j;
    int iN, iH;
    char *iArr;
    int **DP;
    int count[6];
    int res;

    scanf("%d %d", &iN, &iH);
    iArr = (char*)malloc(sizeof(char)*(iN+1));
    scanf("%s", iArr);

    // HP == 1
    if(iH == 1) res = 0;
    // HP == 2  // DP
    else if (iH == 2){
        DP = (int**)malloc(sizeof(int*)*3);
        for(i = 0; i < 3; i++) {
            DP[i] = (int*)malloc(sizeof(int)*(iN+1));
            DP[i][0] = 0;
        }
        for(i = 1; i <= iN; i++){
            for(j= 0; j < 3; j++){
                DP[j][i] = MIN(DP[(j+1)%3][i-1] + 1 - (iArr[i-1] == ELEMENT[0][j]), DP[(j+2)%3][i-1] + 1 - (iArr[i-1] == ELEMENT[0][j]));
            }
        }
        res = MIN(DP[0][iN], DP[1][iN]);
        res = MIN(res, DP[2][iN]);
        for(i = 0; i < 3; i++) free(DP[i]);
        free(DP);
    }
    // HP == 3 || (HP > 4 && iN <= 3)
    else if (iH == 3 || (iH > 3 && iN <= 3)) {
        for(i = 0; i < 6; i++) count[i] = 0;
        for(i = 0; i < iN; i++){
            for(j = 0; j < 6; j++){
                if(iArr[i] != ELEMENT[j][i%3]) count[j]++;
            }
        }

        res = count[0];
        for(i = 1; i < 6; i++) res = MIN(res, count[i]);
    }
    // else (HP > 4 && iN > 3)
    else res = -1;

    printf("%d\n", res);

finale:
    free(iArr);

    return 0;
}