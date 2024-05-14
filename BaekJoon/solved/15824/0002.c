#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007
#define ll long long


void sort(int* arr, int low, int high){
    int* tmp, aIdx, bIdx, tIdx;

    if(low >= high) return;

    sort(arr, low, (low+high)/2);
    sort(arr, (low+high)/2 + 1, high);

    tmp = (int*)malloc(sizeof(int)*(high-low+1));
    aIdx = low;
    bIdx = (low+high)/2 + 1;

    for(tIdx = 0; tIdx < high-low+1; tIdx++){
        if(bIdx > high) tmp[tIdx] = arr[aIdx++];
        else if (aIdx > (low+high)/2) tmp[tIdx] = arr[bIdx++];
        else if(arr[aIdx] < arr[bIdx]) tmp[tIdx] = arr[aIdx++];
        else tmp[tIdx] = arr[bIdx++];
    }
    
    for(tIdx = 0; tIdx < high-low+1; tIdx++) arr[low+tIdx] = tmp[tIdx];

    free(tmp);

    return;
}


int main(void){
    int i;
    int N;
    int *arr;
    ll pow, acc, res;

    scanf("%d", &N);
    arr = (int*)malloc(sizeof(int)*N);
    for(i = 0; i < N ;i ++) scanf("%d", &arr[i]);

    // sort input
    sort(arr, 0, N-1);
    // for(i = 0; i < N; i++) printf("%d ", arr[i]); printf("\n");

    // calc
    res = 0;
    pow = 1;
    acc = 0;
    for(i = 1; i < N; i++){
        pow = (pow << 1) % MOD;
        acc = ((acc << 1) + (ll)arr[i-1]) % MOD;
        res = (res + (((pow-1) * arr[i]) % MOD) - acc) % MOD;
        if(res < 0) res += MOD;
    }
    
    printf("%lld\n", res);
    free(arr);

    return 0;    
}