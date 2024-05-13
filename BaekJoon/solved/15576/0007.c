#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI acos(-1.0)
#define INPUT_MAX 1000001

typedef struct COMPLEX{
    double real;
    double imag;
} complex;

complex addComplex(complex a, complex b){
    complex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    
    return result;
}

complex subComplex(complex a, complex b){
    complex result;
    result.real = a.real - b.real;
    result.imag = a.imag - b.imag;

    return result;
}

complex multComplex(complex a, complex b){
    complex result;
    result.real = (a.real * b.real) - (a.imag * b.imag);
    result.imag = (a.real * b.imag) + (a.imag * b.real);

    return result;
}

complex divComplex(complex a, int n){
    complex result;
    result.real = a.real / n;
    result.imag = a.imag / n;

    return result;
}

// Iterative FFT : bo -> no (bit-reverse order to nomal order)
void fft(complex *x, int n, int is_inv) {
    int i, j, sz, s;
    int o, r; // original, reverse
    int log2n;
    double ex;
    complex th, w;
    complex temp;
    
    // make bit-reverse order
    for(log2n = 0; (1 << log2n) < n; log2n++);
    
    for(i = 0; i < n; i++){
        o = i;
        r = 0;
        for(j = 0; o != 0; j++){
            r <<= 1;
            r |= o & 1;
            o >>= 1;
        }
        r <<= log2n - j;
        if(r > i) {
            temp = x[i];
            x[i] = x[r];
            x[r] = temp;
        }
    }

    for(sz = 1; sz < n; sz <<= 1){
        ex = PI/sz;
        if(is_inv) ex = -ex;

        w.real = cos(ex);
        w.imag = sin(ex);
        for(s = 0; s < n; s += (sz << 1)){
            th.real = 1.0;
            th.imag = 0.0;
            for(i = 0; i < sz; i++){
                temp = multComplex(x[s + sz + i], th);
                x[s + sz + i] = subComplex(x[s + i], temp);
                x[s + i]      = addComplex(x[s + i], temp);

                th = multComplex(th, w);
            }
        }
    }
    
    if(is_inv) for(i = 0; i < n; i++) x[i] = divComplex(x[i], n);


    return;
}

// res save to x;
void pointwise_multiply(complex *x, complex *y, int size){
    int i;

    for(i = 0; i < size; i++) x[i] = multComplex(x[i], y[i]);

    return;
}

int main() {
    int i, tmp, sum, pos;
    int aSize, bSize, unit, fftSize, padding;
    char *res;
    char *A;
    char *B;
    complex *x, *y;

    unit = 10;

    A = (char*)malloc(INPUT_MAX);
    B = (char*)malloc(INPUT_MAX);

    scanf("%s", A);
    scanf("%s", B);

    // no multiply need
    if( (strlen(A) == 1 && A[0] == '0') || (strlen(B) == 1 && B[0] == '0')) {
        printf("0\n");
        free(A); free(B);
        return 0;
    }

    aSize = strlen(A);
    bSize = strlen(B);

    tmp = (aSize > bSize ? aSize : bSize);   
    tmp <<= 1; 
    fftSize = 1;
    while(fftSize < tmp) fftSize *= 2;    
    
    // complex double x[fftSize], y[fftSize];
    x = (complex*)malloc(sizeof(complex)*fftSize);
    y = (complex*)malloc(sizeof(complex)*fftSize);
  
    // put each value in x
    padding = fftSize - aSize;
    for(i = 0; i < padding; i++) x[i].real = 0;
    for (; i < fftSize; i++) x[i].real = (int)A[i - padding] - '0';

    // put each value in y
    padding = fftSize - bSize;
    for(i = 0; i < padding; i++) y[i].real = 0;
    for (; i < fftSize; i++) y[i].real = (int)B[i- padding] - '0';
        
    free(A);
    free(B);
    // x, y to evaluation form & point-wise mult & to coefficient form

    fft(x, fftSize, 0);
    fft(y, fftSize, 0);
    pointwise_multiply(x, y, fftSize);
    fft(x, fftSize, 1);

    // calc (x*y)(10) & parse result
    res = (char*)malloc(fftSize + 1);
    pos = fftSize;
    res[pos--] = '\0';
    sum = 0;
    for(i = fftSize - 2; i >= 0; i--){
        sum += (int)(x[i].real + (x[i].real > 0 ? 0.5 : -0.5));
        res[pos--] = ((char)(sum % unit)) + '0';
        sum /= unit;
    }

    while(sum != 0){
        res[pos--] = ((char)(sum % unit))  + '0';
        sum /= unit;
    }    

    while(res[++pos] == '0');
    printf("%s\n", res+pos);

    free(res);
    free(x);
    free(y);

    return 0;
}
