#include <stdio.h>
#include <stdlib.h>

// 2^64 - 2^32 + 1
// #define P 0xffffffff00000001ull
// #define W 3
#define P 998244353
#define W 3
#define ull unsigned long long


ull power (ull x, ull k){
    ull res = 1;
    while(k){
        if(k & 1)  res = (res * x) % P;
        x = (x * x) % P;
        k >>= 1;
    }
    return res;
}


// NTT CT : no->bo
void NTT(ull* poly, int size, int isInv){
    int i, j, k, o, r; 
    int log2S, swap;
    ull pRoot, *omega;
    int step, chunk;
    ull u, v, t;

    // Calc Omega (n-th Primitive Root)
    omega = (ull*)calloc(size, sizeof(ull));    
    pRoot = power(W, (P-1)/size);    // n_th primitive root
    if(isInv) pRoot = power(pRoot, (P-2));   // modular inverse
    
    // Prepare Omegas
    omega[0] = 1;
    for(i = 1; i < size; i++) omega[i] = (omega[i-1] * pRoot) % P;

    // Bit reverse
    for(log2S = 0; (1 << log2S) < size; log2S++);
    for(i = 0; i < size; i++){
        o = i;
        r = 0;
        for(j = 0; o != 0; j++){
            r <<= 1;
            r |= o & 1;
            o >>= 1;
        }
        r <<= log2S - j;
        if(r > i){
            swap = poly[i];
            poly[i] = poly[r];
            poly[r] = swap;
        }
    }

    for(i = 2; i <= size; i <<= 1){
        step = size / i;
        for(j = 0; j < size; j+= i){
            for(k = 0; k < (i>>i); k++){
                u = poly[j | k];
                v = (poly[j | k | i >> 1] * omega[step * k]) % P;
                poly[j | k] = (u + v) % P;
                poly[j | k | i >> 1] = (u - v) % P;
                if(poly[j | k | i >> 1] < 0) poly[j | k | i >> 1] += P;
            }
        }
    }
    
    if(isInv){
        t = power((ull)size, (ull)(P-2));
        for(i = 0;i < size; i++) poly[i] = (poly[i] * t) % P;
    }

    free(omega);
    return;
}

int main(void){
    int i;
    int aDegree, bDegree, resDegree;
    int polySize;
    ull *polyA, *polyB;

    scanf("%d %d", &aDegree, &bDegree);
    resDegree = aDegree + bDegree + 1;
    for(polySize = 1; polySize <= resDegree; polySize <<= 1);
    polyA = (ull*)calloc(polySize, sizeof(ull));
    polyB = (ull*)calloc(polySize, sizeof(ull));
    for(i = 0; i < aDegree+1; i++) scanf("%llu", &polyA[i]);
    for(i = 0; i < bDegree+1; i++) scanf("%llu", &polyB[i]);


    

    NTT(polyA, polySize, 0);
    NTT(polyA, polySize, 1);
    for(i = 0; i < polySize; i++) printf("%llu ", polyA[i]); printf("\n");
    // NTT(polyB, polySize, 0);
    // for(i = 0; i < polySize; i++) polyA[i] = (polyA[i] * polyB[i]) % P;
    // NTT(polyA, polySize, 1);

    
    // for(i = 0; i < polySize; i++) printf("%llu ", polyA[i]); printf("\n");
    
    free(polyA);
    free(polyB);
    
    return 0;
}