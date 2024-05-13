#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI acos(-1.0)

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
    
    for(i = 0; i < size; i++) {
        y[i].imag = -y[i].imag;
        x[i] = MultComplex(x[i], y[i]);
    }
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
    int i;
    int n, l, m;
    long long W;
    int compSize;
    int count;
    complex *x, *y;

    scanf("%d %d %d %lld", &n, &l, &m, &W);

    for(compSize = 1; compSize < (n + l)*m; compSize <<= 1);
    x = (complex*)malloc(sizeof(complex)*compSize);
    y = (complex*)malloc(sizeof(complex)*compSize);

    for(i = 0; i < n*m; i++) scanf("%le", &x[i].real); 
    for(i = 0; i < l*m; i++) scanf("%le", &y[n*(i/l) + (i%l)].real);

    FFT(x, compSize, 0); 
    FFT(y, compSize, 0);
    PointWiseMult(x, y, compSize);
    FFT(x, compSize, 1);

    count = 0;
    for(i = 0; i < n-l+1; i++) if((long long)(x[i].real + (x[i].real > 0 ? 0.5 : -0.5)) > W) count++;
    printf("%d\n", count);

    return 0;
}