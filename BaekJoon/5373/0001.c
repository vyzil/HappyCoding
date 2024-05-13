#include <stdio.h>
#include <stdlib.h>

/* 
 * Position = [S]ide << 3 + Index
 *     ___ ___ ___
 *    |_0_|_1_|_2_|
 *    |_7_|_X_|_3_|
 *    |_6_|_5_|_4_|
 * 
 *  [U]p   [D]own [F]ront 
 *  [B]ack [L]eft [R]ight
 */

#define POS(x,y) ((x) << 3) + (y)

#define U 0
#define D 1
#define F 2
#define B 3
#define L 4
#define R 5
#define S_NUM 6
#define I_NUM 8
#define R_NUM 2 * S_NUM

char Color[S_NUM] = {'w', 'y', 'r', 'o', 'g', 'b'};
int Rotate[R_NUM][S_NUM][I_NUM];

// side1 -> side2 -> side3 -> side4 -> side1, clock wise
void calcSideRotate(int method, int side[4], int start[4]){
    int i, j;
    int wise;
    wise = method / S_NUM == 1 ? -1 : 1;
    for(i = 0; i < 4; i++){        
        for(j = 0; j < 3; j++){
            Rotate[method][side[i]][(start[i] + j) % I_NUM] = POS(side[(i+wise+4)%4], (start[(i+wise+4)%4] + j) % I_NUM);
        }
    }
    return;    
}

void calcRotate(){ // inverse : (+) <-> (-)
    int i, j, k, idx;
    int side[4], start[4];

    // 1. init
    for(i = 0; i < R_NUM; i++){
        for(j = 0; j < S_NUM; j++){
            for(k = 0; k < I_NUM; k++) Rotate[i][j][k] = POS(j, k);
        }
    }

    // 2. face rotate
    for(i = 0; i < S_NUM; i++){
        for(j = 0; j < I_NUM; j++) Rotate[i][i][j] = POS(i, (j+2) % I_NUM);
        for(j = 0; j < I_NUM; j++) Rotate[i+S_NUM][i][j] = POS(i, (j-2+I_NUM) % I_NUM);
    }

    // 3. side rotate
    // U
    side [0] = F; side [1] = L; side [2] = B; side [3] = R;
    start[0] = 0; start[1] = 0; start[2] = 4; start[3] = 0;
    calcSideRotate(U , side, start);
    calcSideRotate(U + S_NUM , side, start);

    // D
    side [0] = B; side [1] = L; side [2] = F; side [3] = R;
    start[0] = 0; start[1] = 4; start[2] = 4; start[3] = 4;
    calcSideRotate(D , side, start);
    calcSideRotate(D + S_NUM , side, start);

    // F
    side [0] = D; side [1] = L; side [2] = U; side [3] = R;
    start[0] = 0; start[1] = 2; start[2] = 4; start[3] = 6;
    calcSideRotate(F , side, start);
    calcSideRotate(F + S_NUM , side, start);

    // B
    side [0] = U; side [1] = L; side [2] = D; side [3] = R;
    start[0] = 0; start[1] = 6; start[2] = 4; start[3] = 2;
    calcSideRotate(B , side, start);
    calcSideRotate(B + S_NUM , side, start);

    // L
    side [0] = D; side [1] = B; side [2] = U; side [3] = F;
    start[0] = 6; start[1] = 6; start[2] = 6; start[3] = 6;
    calcSideRotate(L , side, start);
    calcSideRotate(L + S_NUM , side, start);

    // R
    side [0] = D; side [1] = F; side [2] = U; side [3] = B;
    start[0] = 2; start[1] = 2; start[2] = 2; start[3] = 2;
    calcSideRotate(R , side, start);
    calcSideRotate(R + S_NUM , side, start);

    return;
}

void cubing(){
    int i, j;
    int iN, pos, curSide, curIdx;
    int curMethod;
    int *seq;
    int posArr[8];
    char iRot[3];

    for(i = 0; i < I_NUM; i++) posArr[i] = POS(U, i);
    
    scanf("%d", &iN);
    seq = (int*)malloc(sizeof(int)*iN);
    for(pos = iN-1; pos >= 0 ; pos--){
        scanf("%s", iRot);
        switch(iRot[0]) {
            case 'U': curMethod = U; break;
            case 'D': curMethod = D; break;
            case 'F': curMethod = F; break;
            case 'B': curMethod = B; break;
            case 'L': curMethod = L; break;
            case 'R': curMethod = R; break;
            default : curMethod = -1; break;
        }
        if(iRot[1] == '+') curMethod += S_NUM;
        seq[pos] = curMethod;
        getchar();
    }

    for(i = 0; i < iN; i++){
        curMethod = seq[i];
        for(j = 0; j < I_NUM; j++){
            curSide = posArr[j] / I_NUM;
            curIdx  = posArr[j] % I_NUM;
            posArr[j] = Rotate[curMethod][curSide][curIdx];
        }
    }

    printf("%c%c%c\n", Color[posArr[0]/I_NUM], Color[posArr[1]/I_NUM], Color[posArr[2]/I_NUM]);
    printf("%c%c%c\n", Color[posArr[7]/I_NUM], Color[U]              , Color[posArr[3]/I_NUM]);
    printf("%c%c%c\n", Color[posArr[6]/I_NUM], Color[posArr[5]/I_NUM], Color[posArr[4]/I_NUM]);

    free(seq);

    return;
}

int main(void){
    int i;
    int iT;

    calcRotate();

    scanf("%d", &iT);
    while(iT--) cubing();

    return 0;
}