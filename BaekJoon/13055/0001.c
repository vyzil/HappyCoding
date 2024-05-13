#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI acos(-1.0)
#define STR_MAX 1000000
#define PRECISE(x) (int)((x) + ((x) > 0 ? 0.5 : -0.5))

typedef struct _COMPLEX{
    double real;
    double imag;
} COMPLEX;

COMPLEX addComplex(COMPLEX a, COMPLEX b){
    COMPLEX c;
    c.real = a.real + b.real;
    c.imag = a.imag + b.imag;

    return c;
}

COMPLEX subComplex(COMPLEX a, COMPLEX b){
    COMPLEX c;
    c.real = a.real - b.real;
    c.imag = a.imag - b.imag;

    return c;
}

COMPLEX multComplex(COMPLEX a, COMPLEX b){
    COMPLEX c;
    c.real = a.real * b.real - a.imag * b.imag;
    c.imag = a.imag * b.real + a.real * b.imag;

    return c;
}

COMPLEX divComplex(COMPLEX a, int n){
    COMPLEX c;
    c.real = a.real / n;
    c.imag = a.imag / n;

    return c;
}


void fft(COMPLEX *x, int n, int isInv){
    int i, j, sz, s;
    int r, o, log2n;
    double ex;
    COMPLEX th, w;
    COMPLEX temp;

    for(log2n = 0; (1 << log2n) < n; log2n++);

    for(i = 0; i < n; i++){
        o = i;
        r = 0;
        for(j = 0; o > 0; j++){
            r <<= 1;
            r |= (o & 1);
            o >>= 1;
        }
        r <<= log2n - j;
        if(r > i){
            temp = x[i];
            x[i] = x[r];
            x[r] = temp;
        }
    }

    for(sz = 1; sz < n; sz <<= 1){
        ex = PI / sz;
        if(isInv) ex = -ex;

        w.real = cos(ex);
        w.imag = sin(ex);
        for(s = 0; s < n; s+=(sz<<1)){
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
    if(isInv) for(i = 0; i < n; i++) x[i] = divComplex(x[i], n);

    return;
}

// res save to x;
void pointwise_multiply(COMPLEX *x, COMPLEX *y, int size){
    int i;
    
    for(i = 0; i < size; i++) x[i] = multComplex(x[i], y[i]);

    return;
}


int main(void){
    int i;
    COMPLEX *iA, *iB;
    int strLen, fftSize;
    char str[STR_MAX];

    scanf("%s", str);
    strLen = strlen(str);
    for(fftSize = 1; fftSize < 2*strLen; fftSize <<= 1);
    iA = (COMPLEX*)malloc(sizeof(COMPLEX)*fftSize);
    iB = (COMPLEX*)malloc(sizeof(COMPLEX)*fftSize);
    
    for(i = 0; i < strLen; i++){
        if(str[i] == 'A') iA[fftSize - i].real = 1;
        else iB[i].real = 1;
    }

    fft(iA, fftSize, 0);
    fft(iB, fftSize, 0);
    pointwise_multiply(iA, iB, fftSize);
    fft(iA, fftSize, 1);

    for(i = fftSize - 1; i >= fftSize - strLen + 1; i--) printf("%d\n", PRECISE(iA[i].real));

    free(iA);
    free(iB);

    return 0;
}