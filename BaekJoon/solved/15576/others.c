#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979

char buf[600003];

typedef struct COMPLEX 
{
    double real_val;
    double img_val;
} complex;

/* Function for adding two complex numbers */
complex addComplex(complex a, complex b)
{
    complex result;

    result.real_val = a.real_val + b.real_val;
    result.img_val = a.img_val + b.img_val;

    return result;
}

/* Function for subtracting two complex numbers */
complex subComplex(complex a, complex b)
{
    complex result;

    result.real_val = a.real_val - b.real_val;
    result.img_val = a.img_val - b.img_val;

    return result;
}

/* Function for multiplying two complex numbers */
complex multiplyComplex(complex a, complex b)
{
    complex result;

    result.real_val = (a.real_val * b.real_val) 
                    - (a.img_val * b.img_val);
    result.img_val = (a.real_val * b.img_val)
                    + (a.img_val * b.real_val);

    return result;
}

/* Function for dividing complex number a by integer r */
complex divideComplex(complex a, int n)
{
    complex result;

    result.real_val = a.real_val / n;
    result.img_val = a.img_val / n;

    return result;
}

/* Function for FFT */
void FFT(complex *P, int n, int is_inv)
{
    /* Get bit reversal and exchange element for in-place FFT*/
    int r, cb, nb;
    complex temp;

    for (nb = 0; (1 << nb) < n; nb += 1);

    for (int i = 0; i < n; i++)
    {
        r = 0;
        cb = 0;
        while (cb < nb) 
        {
            r |= (((i >> cb) & 1) << (nb - cb - 1));
            cb++;
        }
        if (r > i)
        {
            temp = P[i];
            P[i] = P[r];
            P[r] = temp;
        }
    }

    /* Get Fourier Transform by using Bottom-up way */
    double ex;
    complex th, w;

    for (int sz = 1; sz < n; sz <<= 1)
    {
        ex = PI / sz;
        if (is_inv) ex = -ex;

        w.real_val = cos(ex);
        w.img_val = sin(ex);
        for (int s = 0; s < n; s += (sz << 1))
        {
            th.real_val = 1.0;
            th.img_val = 0.0;
            for (int i = 0; i < sz; i++)
            {
                temp = multiplyComplex(P[s + sz + i], th);
                P[s + sz + i] = subComplex(P[s + i], temp);
                P[s + i] = addComplex(P[s + i], temp);

                th = multiplyComplex(th, w);
            }
        }
    }

    /* Divide result by n for inverse FFT */
    if (is_inv)
    {
        for (int i = 0; i < n; i++) P[i] = divideComplex(P[i], n);
    }

    return;
}

/* This function multiplies A_real and B_real by using FFT,
and store value of A * B to result. */
void multiplyLargeInteger
(complex *A, complex *B, int sizeN, int *result)
{
    FFT(A, sizeN, 0);
    FFT(B, sizeN, 0);

    complex temp;
    for (int i = 0; i < sizeN; i++)
    {
        A[i] = multiplyComplex(A[i], B[i]);
    }

    FFT(A, sizeN, 1);

    for (int i = 0; i < sizeN; i++)
    {
        result[i] = (int)(A[i].real_val + 0.5);
    }
    for (int i = 1; i < sizeN; i++)
    {
        result[i] += result[i - 1] / 100;
        result[i - 1] = result[i - 1] % 100;
    }

    return; 
}

/* From string, store the value of A and B. 
Each element at A and B will be less than 10000. */
void parser
(char *buf, complex *A, int lenA, complex *B, int lenB)
{
    char *temp;
    int count, idx, digit;
    
    temp = buf + lenA + lenB;
    count = 0;
    idx = 0;
    for (int i = lenB; i > 0; i--, temp--, count++)
    {
        idx += count >> 1;
        count = count & 1;

        if (!count) digit = 1;
        else digit = 10;
    
        B[idx].real_val = B[idx].real_val + (*temp - '0') * digit;
    }

    temp--;
    count = 0;
    idx = 0;
    for (int i = lenA; i > 0; i--, temp--, count++)
    {
        idx += count >> 1;
        count = count & 1;

        if (!count) digit = 1;
        else digit = 10;
    
        A[idx].real_val = A[idx].real_val + (*temp - '0') * digit;
    }

    return;
}

/* Print the multiplied result. */
void printResult(int *result, int sizeN)
{
    int idx = sizeN - 1;

    while((!result[idx]) && (idx > 0)) idx--;

    if (!idx && !result[idx]) 
    {
        printf("0\n");
        return;
    }

    int len = 0, count = 0;

    if (result[idx] / 10 != 0) 
    {
        buf[len++] = ((char)(result[idx] / 10)) + '0';
    }
    buf[len++] = ((char)(result[idx] % 10)) + '0';
    idx--;

    while (idx >= 0)
    {
        buf[len++] = ((char)(result[idx] / 10)) + '0';  
        buf[len++] = ((char)(result[idx] % 10)) + '0';
        idx--;
    }

    buf[len++] = '\n';

    fwrite(buf, sizeof(char), len, stdout);

    return;
}

/* From stdin, get two numbers A and B and print the result of A * B */
int main(void)
{
    char *temp;
    int lenA = 0, lenB = 0;
    int sizeA, sizeB, sizeN;

    fgets(buf, 600005, stdin);

    temp = buf;
    while(*temp != ' ') 
    {
        lenA++;
        temp++;
    }
    temp++;
    while ((*temp != '\0')&&(*temp != '\n'))
    {
        lenB++;
        temp++;
    }
    
    sizeA = (lenA + 1) >> 1;
    sizeB = (lenB + 1) >> 1;

    sizeN = 1;
    if (sizeA > sizeB) while (sizeN < sizeA) sizeN <<= 1;
    else while (sizeN < sizeB) sizeN <<= 1;
    sizeN <<= 1;

    int *result;
    complex *A, *B;

    result = (int *)calloc(sizeN, sizeof(int));
    A = (complex *)calloc(sizeN, sizeof(complex));
    B = (complex *)calloc(sizeN, sizeof(complex));
    
    parser(buf, A, lenA, B, lenB);

    multiplyLargeInteger(A, B, sizeN, result);

    printResult(result, sizeN);

    return 0;
}