#include <stdio.h>

#define CANDY_TYPE 1000000
#define TREE_SIZE 2097152

int g_segTree[TREE_SIZE] = {0};

int popCandy(int idx, int start, int end, int num){
    int res;
    res = -1;
    if(start == end) res = start;
    else if(num <= g_segTree[2*idx]) res = popCandy(2*idx, start, (start+end)/2, num);
    else res = popCandy(2*idx+1, (start+end)/2 + 1, end, num - g_segTree[2*idx]);
    g_segTree[idx]--;
    return res;
}

void updateCandy(int idx, int start, int end, int num, int count){
    int res;
    if(start != end) {
        if(start <= num && num <= (start + end)/2) updateCandy(2*idx, start, (start+end)/2, num, count);
        if((start + end)/2 + 1 <= num && num <= end) updateCandy(2*idx+1, (start+end)/2 + 1, end, num, count);
    }
    g_segTree[idx] += count;
    return;
}

int main(void) {
    int n;
    int a, b, c;

    scanf("%d", &n);
    while(n--){
        scanf("%d", &a);
        if(a == 1) { // one candy
            scanf("%d", &b);
            printf("%d\n", popCandy(1, 0, CANDY_TYPE-1, b)+1);
        }
        else {  // a == 2 : many candy
            scanf("%d %d", &b, &c);
            updateCandy(1, 0, CANDY_TYPE-1, b-1, c);
        }
    }

    return 0;
}