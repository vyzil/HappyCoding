#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI acos(-1.0)


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
    int i, tmp, max;
    int N, size;
    complex *x, *y;

    scanf("%d", &N);
    size = 1;
    while(size < 2*N) size *= 2;

    x = (complex*)calloc(size, sizeof(complex));
    y = (complex*)calloc(size, sizeof(complex));
    for(i = 0; i < N; i++){
        scanf("%d", &tmp);
        x[i].real = tmp;
        x[N + i].real = tmp;
    }
    for(i = 2*N;i<size;i++) x[i].real = 0;

    for(i = N - 1; i >= 0; i--) {
        scanf("%d", &tmp);
        y[i].real = tmp;
    }
    for(i = N; i < size; i++) y[i].real = 0;
    
    fft(x, size, 0);
    fft(y, size, 0);
    pointwise_multiply(x, y, size);
    fft(x, size, 1);

    max = 0;
    for(i = 0; i < size; i++) {
        tmp = (int)(x[i].real + (x[i].real > 0 ? 0.5 : -0.5));
        if(tmp > max) max = tmp;
    }
    printf("%d\n", max);

    return 0;
}
