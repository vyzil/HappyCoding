#include <stdio.h>
int N;//전구의 수
int K;//색의 수
int A[201];
int D[201][201];//i~j사이의 같은 색으로 바꾼 최소 횟수
int Dynamic(void){
	int len, i, j, k;
	for (len = 1; len < N; len++){
		for (i = 1; i <= N - len; i++){
			j = i + len;
			if (A[i] == A[j]) D[i][j] = D[i][j - 1];
			else D[i][j] = D[i][j - 1] + 1;
			for (k = i; k < j; k++){
				if (D[i][j] > D[i][k] + D[k + 1][j]) D[i][j] = D[i][k] + D[k + 1][j];
			}
		}
	}
	return D[1][N] - 1;
}
int main(void){
	int i, j, ans;
	int d;
	scanf("%d %d", &N, &K);
	for (i = 1, j = 0; i <= N; i++){
		scanf("%d", &d);
		if (A[j] != d){
			A[++j] = d;
			D[j][j] = 1;
		}
	}
	N = j;
	ans = Dynamic();
	printf("%d\n", ans);
	return 0;
}