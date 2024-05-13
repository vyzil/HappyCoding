#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main_bak01(void);
int gcd(int a, int b);

int main_bak03(void){
    
    int i, j, k, t;
    int n, totalCase, subCase, num;
    int*  a;
    int** arr;    
    int* tmp;
    
    n = 4;

    arr = (int**)malloc(sizeof(int*) * n);
    a = (int*)malloc(sizeof(int)*n);
    totalCase = 1;
    
    arr[0] = (int*)malloc(sizeof(int));
    // printf("%p\n", arr[0]);
    arr[0][0] = 1;
    a[0] = 1;

    for(i = 1; i <n; i++){  // a_n 경우의 수
        arr[i] = (int*)calloc(pow(2, i) - 1, sizeof(int));   // 숫자의 범위, count를 저장
    }
    
    totalCase = 1;


    for(i = 1; i < n; i++){
        // calc a_n
        // 1. Case
        // printf("total : %d\n", totalCase);
        for(j = 0; j < totalCase; j++){     // a_(n-1) 까지 모든 조합의 갯수
            subCase = 1;
            // 1. fix number
            for(k = 1; k < i; k++){     // a_1 부터 선택                
                subCase *= (pow(2,k) - 1);
                a[k] = j%subCase + 2;
            }

            // printf("%d :", i);
            // for(k = 0; k < i; k++) printf(" %d", a[k]);
            // printf("\n");

            // 2. caculate
            for(k = 0; k < i * i; k++){   // 덧셈 경우의 수 선택
                num = a[k/i] + a[k%i];
                // printf("%d\n", num);
                arr[i][num-2]++;
            }             
        }    
        totalCase *= (pow(2, i) - 1); 
    }

    int tmp2, total;
    totalCase = 1;
    for (i = 0; i < n; i++){
        tmp2 = 0;
        total = 0;
        int* res = arr[i];
        if(i != 0) totalCase = (pow(2, i) - 1);
        printf("arr[%d]", i);
        for (j = 0; j < totalCase; j++ ) {
            printf(" %d", res[j]);
            if(i != 0) tmp2 += (int)(res[j] * (j+2));
            else tmp2 += res[j];
            total += res[j];
        }
        tmp2 /= total;
        printf(" ever : %d", tmp2 );
        printf("\n");
    }

    return 0;
}


int main_bak02(void){
    
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
        // arr[i] = (int*)malloc(sizeof(int)*totalCase);   // 경우의 수 만큼 할당
        for(j = 0; j < totalCase; j++){     // case 번호
            int subCase = 1;
            // 1. fix number
            for(k = 1; k < i; k++){     // a_1 부터 선택                
                subCase *= k * k;
                a[k] = arr[k][j%subCase];
            }
            for(k = 0; k < i; k++) printf("a%d : %d\n", k, a[k]);

            // 2. caculate
            for(k = 0; k < i * i; k++){   // 덧셈 경우의 수 선택
                arr[i][j*i*i + k] = a[k/i] + a[k%i];
                printf("%d\n", a[k/i] + a[k%i]);
            }             
        }     
    }

    totalCase = 1;
    for (i = 0; i < n; i++){
        int* res = arr[i];
        if(i != 0) totalCase *= i*i;
        printf("arr[%d]", i);
        for (j = 0; j < totalCase; j++ ) printf(" %d", res[j]);
        printf("\n");
    }

    return 0;
}



int main_bak01(void){
    int i, div;
    int n;          // input, [0:10^6]
    int *A_H;    // numerator of E(a_n)
    int *A_L;    // denominator of E(a_n)
    int *S_H;    // numerator of Sum // SUM = a0 ~ an
    int *S_L;    // denominator of Sum

    scanf("%d", &n);
    A_H = (int*)malloc(sizeof(int)*n);
    A_L = (int*)malloc(sizeof(int)*n);
    S_H = (int*)malloc(sizeof(int)*n);
    S_L = (int*)malloc(sizeof(int)*n);

    A_H[0] = 1;
    A_L[0] = 1;
    S_H[0] = 1;
    S_L[0] = 1;

    for(i = 1; i <= n; i++){
        A_H[i] = 2 * S_H[i-1];
        A_L[i] = i * S_L[i-1];
        // Make A reduced fraction
        div = gcd(A_H[i], A_L[i]);
        A_H[i] /= div;
        A_L[i] /= div;

        S_H[i] = S_H[i-1] * A_L[i] + S_L[i-1] * A_H[i];
        S_L[i] = A_L[i] * S_L[i-1];
        // Make S reduced fraction
        div = gcd(S_H[i], S_L[i]);
        S_H[i] /= div;
        S_L[i] /= div;
        
        // printf("A[%d] = %d/%d\n", i, A_H[i], A_L[i]);   
        printf("S[%d] = %d/%d\n", i, S_H[i], S_L[i]);       
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