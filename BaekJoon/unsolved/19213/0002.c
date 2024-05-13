#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b);

int main(void){
    
    int i, j, k, t, tmpA, tmpB;
    int n, totalCase, subCase, num, count;
    int*  a;
    int** arr;    
    int* tmp;
    
    n = 5;

    arr = (int**)malloc(sizeof(int*) * n);
    a = (int*)malloc(sizeof(int)*n);
    totalCase = 1;
    
    arr[0] = (int*)malloc(sizeof(int));
    arr[0][0] = 1;
    a[0] = 1;

    printf("Malloc, ");
    for(i = 1; i <n; i++){  // a_n 경우의 수
        arr[i] = (int*)calloc(pow(2, i) - 1, sizeof(int));   // 숫자의 범위, count를 저장
    }
    printf("Done\n");
    
    totalCase = 1;


    for(i = 1; i < n; i++){
        for(j = 0; j < totalCase; j++){     // a_(n-1) 까지 모든 조합의 갯수
            subCase = 1;
            // 1. fix number
            for(k = 1; k < i; k++){     // a_1 부터 선택                
                subCase = (pow(2,k) - 1);
                a[k] = j%subCase + 2;
            }
            printf("%d :", i);
            for(k = 0; k < i; k++) printf(" %d", a[k]);
            printf("\n");

            // 2. caculate
            for(k = 0; k < i * i; k++){
                tmpA = a[k/i];
                tmpB = a[k%i];
                num = a[k/i] + a[k%i];
                tmpA -= 2;
                tmpB -= 2;
                if (k/i == 0) tmpA = 0;
                if (k%i == 0) tmpB = 0;
                count = arr[k/i][tmpA] * arr[k%i][tmpB];
                arr[i][num-2] += count;    // 1만 추가하는게 아니라, 경우의 수 만큼 추가해줘야함 
                    // 다시 생각해봐야 할듯, 2의 경우의 수 2 3 4 와 3의 경우의 수는 연관관계
                    // 즉, a_2가 2라면 a_3은 절대 8이 안나옴 -> 이 부분 생각해봐야할듯...
            }             
        }    
        totalCase *= (pow(2, i) - 1); 
    }

    int everX, everX2, total, tmpGCD, tmpH, tmpL;
    totalCase = 1;
    for (i = 0; i < n; i++){
        everX = 0;
        everX2 = 0;
        total = 0;
        int* res = arr[i];
        if(i != 0) totalCase = (pow(2, i) - 1);
        printf("arr[%d]", i);
        for (j = 0; j < totalCase; j++ ) {
            printf(" (%d, %d)", j+2, res[j]);
            if(i != 0) {
                everX += res[j] * (j+2);
                everX2 += res[j] * pow((j+2), 2);
                total += res[j];
            } else {
                everX += res[j] * (j+1);
                everX2 += res[j] * pow(j+1, 2);
                total += res[j];
            } 
        }
        
        printf("\n\tTotal   : %d", total);
        printf("\n\tXtotal  : %d", everX);
        printf("\n\tX2total : %d", everX2);

        tmpGCD = gcd(everX, total);
        tmpH = everX / tmpGCD;
        tmpL = total / tmpGCD;
        printf("\n\tEverX  : %d", tmpH);
        if(tmpL != 1) printf("/%d", tmpL);


        tmpGCD = gcd(everX2, total);
        tmpH = everX2 / tmpGCD;
        tmpL = total / tmpGCD;
        printf("\n\tEverX2 : %d", tmpH);
        if(tmpL != 1) printf("/%d", tmpL);
        printf("\n");
    }

    return 0;
}

int gcd(int a, int b){
    int tmp;

    while(b != 0){
        int tmp = a % b;
        a = b;
        b = tmp;
    }

    return a;
}