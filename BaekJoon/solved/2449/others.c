#include <stdio.h>
#include <memory.h>
#pragma warning(disable:4996)
#define min(x, y) ((x) > (y) ? (y) : (x))

int n, k;
int a[201], dp[201][201]; // i ~ j를 i색으로 통일

int DP(int l, int r) {
	if (l == r) return 0;
	if (dp[l][r] != -1) return dp[l][r];
	
	dp[l][r] = 2e9;
	for (int i = l; i < r; ++i) {
		dp[l][r] = min(dp[l][r], DP(l, i) + DP(i + 1, r) + (a[l] != a[i + 1]));
	}
	return dp[l][r];
}

int main(void) {
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
	
	memset(dp, -1, sizeof(dp));
	printf("%d\n", DP(0, n - 1));
	return 0;
}
