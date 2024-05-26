#include <stdio.h>

#define PRINTRES(x, y) (printf("! %d %d\n", (x), (y)))

int N = 92;
int arr[92];

char ask(int l, int r){
    char res[2];
    if(found == 2) return "X";
    printf("AK %d %d\n", l, r); fflush(stdout);
    scanf("%s", res);
    return res[0];
}

int found;
int num[2];

// low ~ mid, mid+1 ~ high-1, high
void ak47(int low, int high, int left){
    int mid;
    int res, l, r;

    if(left == 1 || high - low < 2){
        if(low == high) {
            num[found++] = low;
            return;
        }
        mid = (low + high) / 2;
        if(ask(low, mid) == 'O') ak47(low, mid, left);
        else ak47(mid+1, high, left);
        return;
    }
    else {  // left == 2 and high - low >= 2
        mid = (low + high-1)/2;
        l = (ask(low, mid) == 'O');
        r = (ask(mid+1, high-1) == 'O');         
        if(l + r == 2 || l + r == 0){
            ak47(low, mid, 2);
            ak47(mid+1, high-1, 2);
        }
        else if(l + r == 1){
            num[found++] = high;
            if(l) ak47(low, mid, 1);
            else ak47(mid+1, high-1, 1);
        }        
        return;
    }
    return;
}

int main(void){
    int TC;
    int i;
    int N;
    int found;
    char res[2];

    

    found = 0; num[0] = 0; num[1] = 0;
    ak47(2, N, 2);
    printf("! %d %d\n", num[0], num[1]); fflush(stdout);

    return 0;
}