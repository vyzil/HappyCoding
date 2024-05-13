#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#define PI acos(-1.0)

void fft(complex double* x, int N) {
    if(N <= 1) return;

    complex double t;
    complex double *even, *odd;

    even = (complex double*)malloc(sizeof(complex double)*N/2);
    odd  = (complex double*)malloc(sizeof(complex double)*N/2);

    for(int i = 0; i < N/2; i++) {
        even[i] = x[2*i];
        odd[i]  = x[2*i + 1];
    }

    fft(even, N/2);
    fft(odd, N/2);

    for(int i = 0; i < N/2; i++) {
        t = cexp(-2 * I * PI * i / N) * odd[i];
        x[i]       = even[i] + t;
        x[i + N/2] = even[i] - t;
    }
    free(even);
    free(odd);

    return;
}

void ifft(complex double* x, int N) {
    if(N <= 1) return;

    complex double t;
    complex double *even, *odd;

    even = (complex double*)malloc(sizeof(complex double)*N/2);
    odd  = (complex double*)malloc(sizeof(complex double)*N/2);

    for(int i = 0; i < N/2; i++) {
        even[i] = x[2*i];
        odd[i]  = x[2*i + 1];
    }

    ifft(even, N/2);
    ifft(odd, N/2);

    for(int i = 0; i < N/2; i++) {
        t = cexp(2 * I * PI * i / N) * odd[i];
        x[i]       = (even[i] + t) / 2.0;
        x[i + N/2] = (even[i] - t) / 2.0;
    }

    free(even);
    free(odd);

    return;
}

int main() {
    int i, tmp, sum, pos;
    int aSize, bSize, unit, fftSize, padding;
    int *res;
    char A[300001];
    char B[300001];
    char subStr[5];
    complex double *x, *y;

    unit = 10;

    scanf("%s", A);
    scanf("%s", B);
    // no multiply need
    if( (strlen(A) == 1 && A[0] == '0') || (strlen(B) == 1 && B[0] == '0')) {
        printf("0\n");
        return 0;
    }

    aSize = strlen(A);
    bSize = strlen(B);

    tmp = (aSize > bSize ? aSize : bSize);    
    fftSize = 1;
    while(fftSize < 2*tmp) fftSize *= 2;    
    
    // complex double x[fftSize], y[fftSize];
    x = (complex double*)malloc(sizeof(complex double)*fftSize);
    y = (complex double*)malloc(sizeof(complex double)*fftSize);
  
    // x = [0, 0, 0, 0, 893, 7243, 5849, 3284]
    padding = fftSize - aSize;
    for(i = 0; i < padding; i++) x[i] = 0;
    for (; i < fftSize; i++) x[i] = (int)A[i - padding] - '0';

    // y = [0, 0, 0, 0, 238, 9473, 2894, 7329]
    padding = fftSize - bSize;
    for(i = 0; i < padding; i++) y[i] = 0;
    for (; i < fftSize; i++) y[i] = (int)B[i- padding] - '0';
        
    // x, y to evaluation form & point-wise mult & to coefficient form

    fft(x, fftSize);
    fft(y, fftSize);
    for(i = 0; i < fftSize; i++) x[i] *= y[i];
    ifft(x, fftSize);

    // calc (x*y)(10)
    res = (int*)malloc(sizeof(int)*fftSize);
    sum = 0;
    pos = 0;    
    i = fftSize - 2;
    for(; i >= 0; i--){
        sum += (int)(creal(x[i]) + (creal(x[i]) > 0 ? 0.5 : -0.5));
        res[pos++] = sum % unit;
        sum /= unit;
    }

    res[pos++] = sum;

    while(res[--pos] == 0);
    printf("%d", res[pos]);
    for(i = pos - 1; i >= 0; i--) {
        printf("%d", res[i]);
    }
    printf("\n");

    free(res);
    free(y);
    free(x);

    return 0;
}
