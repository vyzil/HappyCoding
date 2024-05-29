#include <stdio.h>

int f(int n) {
    // if (n == 0) return 1;
    // int sum = 0;
    // for(int i = 0; i < n; i++)
    //     sum += f(i);
    // return sum % 13;
    if (n == 0) return 1;
    int arr[] = {7, 1, 2, 4, 8, 3, 6, 12, 11, 9, 5, 10};
    return arr[n%12];
}

int main(){
    char ans[] = "rgjgmbuyhbfcx";
    for(int i = 0; i < 13; i++)
        ans[i] ^= f(13+i*i*i);
    puts(ans);

}