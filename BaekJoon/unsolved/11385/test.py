#!/usr/bin/python3

import sys
from math import ceil, sqrt
input = sys.stdin.readline
w = 3
mod = 998244353

def power(a, b):
    ret = 1
    while b:
        if b&1: ret = (ret * a) % mod
        a = (a * a) % mod
        b = b >> 1
    return ret

def NTT(A, inv=False):
    n = len(A)    
    
    rev = [0] * n
    for i in range(n): # Sort A
        rev[i] = rev[i >> 1] >> 1
        if i&1:
            rev[i] |= n >> 1
        if i < rev[i]: # Swap condition
            A[i], A[rev[i]] = A[rev[i]], A[i]
    
    x = power(w, (mod - 1) // n)
    if inv: x = power(x, mod - 2)
    
    root = [1]
    for i in range(1, n):
        root.append((root[i-1] * x) % mod)

    i = 2
    while i <= n:
        step = n // i
        for j in range(0, n, i):
            for k in range(i>>1):
                u = A[j|k]
                v = (A[j|k|i >> 1] * root[step*k]) % mod
                A[j|k] = (u + v) % mod
                A[j|k|i >> 1] = (u - v) % mod
                if A[j|k|i >> 1] < 0: A[j|k|i >> 1] += mod
        i <<= 1

    if inv:
        t = power(n, mod - 2)
        for i in range(n):
            A[i] = (A[i] * t) % mod

    return A

def multiply(a, b):
    # Check if the length of a and b are both same and power of 2.
    n = len(a)

    # NTT
    A = NTT(a, inv=False)
    B = NTT(b, inv=False)

    # INTT
    C = NTT([(A[i]*B[i]) % mod for i in range(n)], inv=True)

    return C

isPrime = [1]*(1000001)
for i in range(2, ceil(sqrt(1000000))+1):
    if isPrime[i]:
        j = i*i
        while j < 1000001:
            isPrime[j] = 0
            j += i
isPrime[0], isPrime[1] = 0, 0
for _ in range((1<<21)-len(isPrime)): isPrime.append(0)

X1 = isPrime[:]; X2 = isPrime[:]
goldbach = multiply(X1, X2)

T = int(input())
for _ in range(T):
    N = int(input())

    ans = goldbach[N] // 2
    if isPrime[N//2]: ans += 1
    print(ans)