#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI acos(-1.0)
#define INT_X_REAL (int)(x[i].real + (x[i].real > 0 ? 0.5 : -0.5))
#define INT_X_IMAG (int)(x[i].imag + (x[i].imag > 0 ? 0.5 : -0.5))
#define DEBUG_PRINTX printf("x :" ); for(i = 0; i < compSize; i++) printf("(%d+%di) ", INT_X_REAL, INT_X_IMAG); printf("\n")

#define INT_Y_REAL (int)(y[i].real + (y[i].real > 0 ? 0.5 : -0.5))
#define INT_Y_IMAG (int)(y[i].imag + (y[i].imag > 0 ? 0.5 : -0.5))
#define DEBUG_PRINTY printf("y :" ); for(i = 0; i < compSize; i++) printf("(%d+%di) ", INT_Y_REAL, INT_Y_IMAG); printf("\n")

typedef struct complex{
    double real;
    double imag;
} complex;

complex AddComplex(complex a, complex b){
    complex res;
    res.real = a.real + b.real;
    res.imag = a.imag + b.imag;

    return res;
}

complex SubComplex(complex a, complex b){
    complex res;
    res.real = a.real - b.real;
    res.imag = a.imag - b.imag;

    return res;
}

complex MultComplex(complex a, complex b){
    complex res;
    res.real = a.real * b.real - a.imag * b.imag;
    res.imag = a.real * b.imag + a.imag * b.real;

    return res;
}

complex DivComplex(complex a, double N){
    complex res;
    res.real = a.real / N;
    res.imag = a.imag / N;
    
    return res;
}

// saves the res in *x
void PointWiseMult(complex *x, complex *y, int size){
    int i;
    
    for(i = 0; i < size; i++) x[i] = MultComplex(x[i], y[i]);
    return;
}

void FFT(complex *x, int n, int isInv){
    int i, j;
    int sz, s;
    int co, bo;
    int log2n;    
    double ex;
    complex tmpC;
    complex th, w;

    for(log2n = 0; (1<<log2n) < n; log2n++);
    
    for(i = 0; i < n; i++){
        co = i;
        bo = 0;
        for(j = 0; co > 0; j++) {
            bo <<= 1;
            bo |= co & 1;
            co >>= 1;
        }
        bo <<= log2n - j;

        if(bo > i) {
            tmpC = x[i];
            x[i] = x[bo];
            x[bo] = tmpC;
        }
    }

    for(sz = 1; sz < n; sz <<= 1){
        ex = PI/sz;
        if(isInv) ex = -ex;

        w.real = cos(ex);
        w.imag = sin(ex);
        for(s = 0; s < n; s += (sz << 1)){
            th.real = 1.0;
            th.imag = 0.0;
            for(i = 0; i < sz; i++){
                tmpC = MultComplex(x[sz + s + i], th);
                x[s + sz + i] = SubComplex(x[s + i], tmpC);
                x[s + i]      = AddComplex(x[s + i], tmpC);

                th = MultComplex(th, w);
            }
        }
    }
    
    if(isInv) for(i = 0; i < n; i++) x[i] = DivComplex(x[i], n);
 
    return;    
}

int main(void){
    int i, row;
    int n, l, m, W;
    int *sky, *tel, *res;
    int compSize;
    int count;
    complex *x, *y;

    scanf("%d %d %d %d", &n, &l, &m, &W);
    sky = (int*)malloc(sizeof(int)*n*m);
    tel = (int*)malloc(sizeof(int)*l*m);
    res = (int*)calloc(n-l+1, sizeof(int));

    for(i = 0; i < n*m; i++) scanf("%d", &sky[i]);   // [1][2] = 1*n + 2
    for(i = 0; i < l*m; i++) scanf("%d", &tel[i]);   // [1][2] = 1*l + 2

    // for(compSize = 1; compSize < 2*n; compSize <<= 1);
    for(compSize = 1; compSize < n + l; compSize <<= 1);

    x = (complex*)malloc(sizeof(complex)*compSize);
    y = (complex*)malloc(sizeof(complex)*compSize);
    for(row = 0; row < m; row++){
        for(i = 0; i < n; i++) {
            x[i].real = sky[row*n + i]; 
            x[i].imag = 0.0;
        }  
        for(; i < compSize; i++) {
            x[i].real = 0.0;
            x[i].imag = 0.0;
        }
        for(i = 0; i < l; i++) {
            y[l-i-1].real = tel[row*l + i]; 
            y[l-i-1].imag = 0.0; 
        }
        for(; i < compSize; i++) {
            y[i].real = 0.0; 
            y[i].imag = 0.0; 
        }

        FFT(x, compSize, 0); 
        FFT(y, compSize, 0);
        PointWiseMult(x, y, compSize);
        FFT(x, compSize, 1);

        for(i = 0; i < n-l+1; i++) res[i] += (int)(x[i+l-1].real + (x[i+l-1].real > 0 ? 0.5 : -0.5));
    }

    count = 0;
    for(i = 0; i < n-l+1; i++) if(res[i] > W) count++;
    printf("%d\n", count);

}