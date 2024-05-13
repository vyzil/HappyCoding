#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>

#define PI acos(-1.0)

void fft(complex double* x, int N) {
    if(N <= 1) return;

    complex double t;
    complex double even[N/2], odd[N/2];
    for(int i = 0; i < N/2; i++) {
        even[i] = x[2*i];
        odd[i] = x[2*i + 1];
    }

    fft(even, N/2);
    fft(odd, N/2);

    for(int i = 0; i < N/2; i++) {
        t = cexp(-2 * I * PI * i / N) * odd[i];
        x[i] = even[i] + t;
        x[i + N/2] = even[i] - t;
    }
}

void ifft(complex double* x, int N) {
    if(N <= 1) return;

    complex double t;
    complex double even[N/2], odd[N/2];
    for(int i = 0; i < N/2; i++) {
        even[i] = x[2*i];
        odd[i] = x[2*i + 1];
    }

    ifft(even, N/2);
    ifft(odd, N/2);

    for(int i = 0; i < N/2; i++) {
        t = cexp(2 * I * PI * i / N) * odd[i];
        x[i] = (even[i] + t) / 2.0;
        x[i + N/2] = (even[i] - t) / 2.0;
    }
}

int main() {
    int i, tmp, sum, pos;
    int aSize, bSize, unit, fftSize, padding, unitV;
    int *res;
    char A[300001];
    char B[300001];
    char subStr[5];

    // 10^4 기준으로 divide
    unit = 4;

    scanf("%s", A);
    scanf("%s", B);
    aSize = strlen(A)/unit + 1;
    bSize = strlen(B)/unit + 1;

    tmp = (aSize > bSize ? aSize : bSize);    
    fftSize = 1;
    while(fftSize < 2*tmp) fftSize *= 2;
    
    complex double x[fftSize], y[fftSize];
  
    // x = [0, 0, 0, 0, 893, 7243, 5849, 3284]
    padding = fftSize - aSize;
    for(i = 0; i < padding; i++) x[i] = 0;
    tmp = strlen(A)%unit;
    if(tmp != 0){
        strncpy(subStr, A, tmp);
        subStr[tmp] = '\0';
        x[i++] = atoi(subStr);    
    }
    for (; i < fftSize; i++) {
        strncpy(subStr, A + tmp, unit);
        subStr[4] = '\0';
        x[i] = atoi(subStr);     
        tmp += unit;
    }

    // y = [0, 0, 0, 0, 238, 9473, 2894, 7329]
    padding = fftSize - bSize;
    for(i = 0; i < padding; i++) y[i] = 0;
    tmp = strlen(B)%unit;
    if(tmp != 0){
        strncpy(subStr, B, tmp);
        subStr[tmp] = '\0';
        y[i++] = atoi(subStr);    
    }
    for (; i < fftSize; i++) {
        strncpy(subStr, B + tmp, unit);
        subStr[unit] = '\0';
        y[i] = atoi(subStr);     
        tmp += unit;
    }
        
    // x, y to evaluation form & point-wise mult & to coefficient form
    fft(x, fftSize);
    fft(y, fftSize);

    for(i = 0; i < fftSize; i++) x[i] *= y[i];

    ifft(x, fftSize);

    // calc (x*y)(unitV)
    res = (int*)malloc(sizeof(int)*fftSize);
    unitV = pow(10, unit);
    sum = 0;
    pos = 0;
    for(i = fftSize-1; i >= 0; i--){
        if(creal(x[i]) == 0) continue;
        sum += (int)(creal(x[i]) + (creal(x[i]) ? 0.5 : -0.5));
        res[pos++] = sum % unitV;
        sum /= unitV;
    }

    res[pos++] = sum;

    while(res[--pos] == 0);
    printf("%d", res[pos]);
    for(i = pos - 1; i >= 0; i--) {
        printf("%04d", res[i]);
    }
    printf("\n");

    return 0;
}
