#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b);

int main(void){
    
    int i, j, k, t;
    int n, totalCase;
    int*  a;
    int** arr;    
    int* tmp;
    
    n = 5;

    arr = (int**)malloc(sizeof(int*) * n);
    a = (int*)malloc(sizeof(int)*n);
    totalCase = 1;
    
    arr[0] = (int*)malloc(sizeof(int));
    printf("%p\n", arr[0]);
    arr[0][0] = 1;
    a[0] = 1;

    totalCase = 1;
    for(i = 1; i <n; i++){
        totalCase = totalCase * i * i;      // a_n 경우의 수
        arr[i] = (int*)malloc(sizeof(int)*totalCase);   // 경우의 수 만큼 할당
    }
    
    totalCase = 1;


    for(i = 1; i < n; i++){
        // calc a_n
        // 1. Case
        totalCase = totalCase * i * i;      // a_n 경우의 수
        printf("totalCase : %d\n", totalCase);
        for(j = 0; j < totalCase; j++){     // case 번호
            int subCase = 1;
            // 1. fix number
            for(k = 1; k < i; k++){     // a_1 부터 선택                
                subCase *= k * k;
                a[k] = arr[k][j%subCase];
            }
            
            // printf("%d :", i);
            // for(k = 0; k < i; k++) printf(" %d", a[k]);
            // printf("\n");

            // 2. caculate
            for(k = 0; k < i * i; k++){   // 덧셈 경우의 수 선택
                // printf("arr[%d][%d] = a[%d] + a[%d]\n", i, j*i*i + k, k/i, k%i );
                arr[i][j*i*i + k] = a[k/i] + a[k%i];
            }             
        }     
    }

    totalCase = 1;
    int total, everX, everX2, tmpGCD, tmpXL, tmpXH, tmpX2L, tmpX2H, tmpVL, tmpVH;
    int count[100] = {0,};
    for (i = 0; i < n; i++){
        int* res = arr[i];
        if(i != 0) totalCase *= i*i;

        for(j = 0; j < 100; j++) count[j] = 0;
        for(j = 0; j < totalCase; j++ ) count[res[j]]++;
        
        printf("arr[%d]", i);
        for(j = 0; j < pow(2,i) + 1; j++) {
            printf(" %d", count[j]);
        }
        printf("\n");
        
        total = 0;
        everX = 0;
        everX2  = 0;
        for(j = 0; j < pow(2,i)+1; j++){
            total += count[j];
            everX += count[j] * j;
            everX2 += count[j] * pow(j, 2);
        }

        printf("\n\tTotal  : %d", total);
        tmpGCD = gcd(everX, total);
        tmpXH = everX / tmpGCD;
        tmpXL = total / tmpGCD;
        printf("\n\tEverX  : %d", tmpXH);
        if(tmpXL != 1) printf("/%d", tmpXL);

        tmpGCD = gcd(everX2, total);
        tmpX2H = everX2 / tmpGCD;
        tmpX2L = total / tmpGCD;
        printf("\n\tEverX2 : %d", tmpX2H);
        if(tmpX2L != 1) printf("/%d", tmpX2L);

        tmpVH = tmpX2H * pow(tmpXL, 2) - tmpX2L * pow(tmpXH, 2) ;
        tmpVL = tmpX2L * pow(tmpXL,2);
        tmpGCD = gcd(tmpVH, tmpVL);
        tmpVH /= tmpGCD;
        tmpVL /= tmpGCD;        
        printf("\n\tVAR    : %d", tmpVH);
        if(tmpVL != 1) printf("/%d", tmpVL);
        printf("\n");
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