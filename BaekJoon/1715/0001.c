#include <stdio.h>
#include <stdlib.h>

int delete(int* arr, int size){
    int res;
    int curIdx, tmp, minIdx;

    if(size == 0) return -1;

    curIdx = 1;
    res = arr[curIdx];
    tmp = arr[size];
    while(curIdx*2 < size){ 
        minIdx = curIdx*2;
        if((curIdx*2+1 < size) && (arr[minIdx] > arr[curIdx*2+1])) minIdx = curIdx*2+1;
        if(arr[minIdx] > tmp) break;
        arr[curIdx] = arr[minIdx];
        curIdx = minIdx;
    }
    arr[curIdx] = tmp;

    return res;
}

void insert(int *arr, int num, int size){
    int curIdx;
    curIdx = size+1;
    while(arr[curIdx/2] > num){
        arr[curIdx] = arr[curIdx/2];
        curIdx /= 2;
    }
    arr[curIdx] = num;

    return;
}

int main(void){
    int i;
    int N;
    int *arr, tmp;
    int first, second, size;
    int sum;

    scanf("%d", &N);
    arr = (int*)malloc(sizeof(int)*(N+1));
    arr[0] = 0;
    for(i = 0 ; i < N; i++) {
        scanf("%d", &tmp);
        insert(arr, tmp, i);      
    }

    sum = 0;
    size = N;
    first = delete(arr, size--);
    while((second = delete(arr, size--)) > 0 ){        
        sum += (first + second);
        insert(arr, (first + second), size++);        
        first = delete(arr, size--);
    }

    printf("%d\n", sum);

    return 0;
}