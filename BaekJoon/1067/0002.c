#include <stdio.h>
#include <complex.h>
#include <math.h>

#define _USE_MATH_DEFINES

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
        t = cexp(-2 * I * M_PI * i / N) * odd[i];
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
        t = cexp(2 * I * M_PI * i / N) * odd[i];
        x[i] = (even[i] + t) / 2.0;
        x[i + N/2] = (even[i] - t) / 2.0;
    }
}

int main() {
    int i, tmp, max;
    int N, size;

    scanf("%d", &N);
    size = 1;
    while(size < 2*N) size *= 2;

    complex double x[size], y[size];
    for(i = 0; i < N; i++){
        scanf("%d", &tmp);
        x[i] = tmp;
        x[N + i] = tmp;
    }
    for(i = 2*N;i<size;i++) x[i] = 0;

    for(i = 0; i < N; i++) {
        scanf("%d", &tmp);
        y[i] = tmp;
    }
    for(i = N; i < size; i++) y[i] = 0;
    
    fft(x, size);
    fft(y, size);

    for(int i = 0; i < size; i++) x[i] *= conj(y[i]);

    ifft(x, size);

    max = 0;
    for(i = 0; i < size; i++) {
        tmp = (int)(creal(x[i]) + (creal(x[i]) ? 0.5 : -0.5));
        if(tmp > max) max = tmp;
    }
    printf("%d\n", max);

    return 0;
}
