#include <stdio.h>

#define N_MAX 100001

int arr[N_MAX], arrSize;
int valid[N_MAX];

int DFS(int num){
    int res;
    
    valid[num] = 1;

    if(arr[num] == num) {
        valid[num] = -1;
        return -2;
    }

    // If in Stack
    if(valid[arr[num]] > 0) {
        valid[num] = -1;
        return arr[num];
    }

    // Already has a Team
    if(valid[arr[num]] < 0){
        valid[num] = -2;
        return valid[num];
    }
    // Never visited
    if(valid[arr[num]] == 0) { // X visited
        res = DFS(arr[num]);
        if(res < 0) {
            valid[num] = res;
            return res;
        }
        else {
            valid[num] = -1;
            if(res != num) return res;
            else return -2;
        }
    }

    return 0;
}


int main(void){
    int i, cnt;
    int TC;

    scanf("%d", &TC);
    while(TC--){
        scanf("%d", &arrSize);
        for(i = 1; i <= arrSize; i++) {
            scanf("%d", &arr[i]);
            valid[i] = 0;
        }

        for(i = 1; i <= arrSize; i++){
            if(valid[i] == 0) DFS(i);
        }

        cnt = 0;
        for(i = 1; i <= arrSize; i++){
            if(valid[i] == -2) cnt++;
        }

        printf("%d\n", cnt);
    }

    return 0;
}