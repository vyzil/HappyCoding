#include <stdio.h>
#include <stdlib.h>

#define ll long long

#define MOD 100003
#define LOG_MAX 20

typedef struct _NODE{
    int func[2];    // f = func[0], g = func[1];
} NODE; 

NODE *g_segTree; int g_treeSize;
int **g_fnx[2];

void update(int idx, int start, int end, int s, int e, int func_num){
    if(e < start || end < s) return;
    if(s <= start && end <= e) {
        g_segTree[idx].func[func_num]++;
        return;
    }
    for(int i = 0; i < 2; i++){
        g_segTree[2*idx].func[i] += g_segTree[idx].func[i];
        g_segTree[2*idx+1].func[i] += g_segTree[idx].func[i];
        g_segTree[idx].func[i] = 0;
    }
    update(2*idx, start, (start + end)/2, s, e, func_num);
    update(2*idx+1, (start + end)/2 + 1, end, s, e, func_num);

    return;
}

NODE query(int idx, int start, int end, int num){
    if(start == end) return g_segTree[idx];

    for(int i = 0; i < 2; i++){
        g_segTree[2*idx].func[i] += g_segTree[idx].func[i];
        g_segTree[2*idx+1].func[i] += g_segTree[idx].func[i];
        g_segTree[idx].func[i] = 0;
    }
    if(num <= (start + end)/2) return query(2*idx, start, (start + end)/2, num);
    else return query(2*idx+1, (start + end)/2 + 1, end, num);
}

int main(void){
    int i, j;
    int N, Q;
    int t, l, r, x;
    int *inputArr;

    scanf("%d %d", &N, &Q);
    inputArr = (int*)malloc(sizeof(int)*(N+1));
    for(i = 1; i <= N; i++) scanf("%d", &inputArr[i]);

    // 1. Pre-compute function values in Sparse Matrix form;
    g_fnx[0] = (int**)malloc(sizeof(int*)*LOG_MAX);
    g_fnx[1] = (int**)malloc(sizeof(int*)*LOG_MAX);
    
    g_fnx[0][0] = (int*)malloc(sizeof(int)*MOD);
    g_fnx[1][0] = (int*)malloc(sizeof(int)*MOD);
    for(j = 1; j < MOD; j++){
        g_fnx[0][0][j] = (int)((((ll)2 * (ll)j * (ll)j - (ll)1)) % MOD);
        g_fnx[1][0][j] = (int)((((ll)4 * (ll)j * (ll)j * (ll)j - (ll)3 * (ll)j)) % MOD);
    }    
    for(i = 1; i < LOG_MAX; i++){
        g_fnx[0][i] = (int*)malloc(sizeof(int)*MOD);
        g_fnx[1][i] = (int*)malloc(sizeof(int)*MOD);
        for(j = 1; j < MOD; j++){
            g_fnx[0][i][j] = g_fnx[0][i-1][g_fnx[0][i-1][j]];
            g_fnx[1][i][j] = g_fnx[1][i-1][g_fnx[1][i-1][j]];
        }
    }

    // 2. Handling Query with Lazy SegTree;
    NODE count;
    int res, idx;

    for(g_treeSize = 1; g_treeSize < N; g_treeSize <<= 1); 
    g_treeSize <<= 1;
    g_segTree = (NODE*)calloc(g_treeSize, sizeof(NODE));    

    while(Q--){
        scanf("%d", &t);
        if(t == 3){
            scanf("%d", &x);
            count = query(1, 1, N, x);
            res = inputArr[x];
            for(i = 0; i < 2; i++){
                idx = 0;
                while(count.func[i]){
                    if(count.func[i] & 1) res = g_fnx[i][idx][res];
                    count.func[i] >>= 1;
                    idx++;
                }
            }
            printf("%d\n", res);
        }
        else {  // t == 1 or 2
            scanf("%d %d", &l, &r);
            update(1, 1, N, l, r, t-1);
        }
    }

    // free should be here..
    free(inputArr);
    free(g_segTree);
    for(i = 0; i < LOG_MAX; i++){
        free(g_fnx[0][i]);
        free(g_fnx[1][i]);
    }
    free(g_fnx[0]);
    free(g_fnx[1]);
    return 0;    
}