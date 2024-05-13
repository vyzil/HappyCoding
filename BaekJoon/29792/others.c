#include <stdio.h>

int main(void) {
	long p[13];
	long d[49];
	long du[13];
	int q[13];
	int n, m, k, i, j, ti, jj, x;
	long t, mv, timeSum, moneySum, maxSum, ans;
	
	scanf("%d %d %d", &n, &m, &k);
	
	for (i = 0; i < n; i++) {
		scanf("%ld", &d[i]);
	}
	
	for (i = 0; i < n - 1; i++) {
		ti = i;
		mv = d[i];
		for (j = i + 1; j < n; j++) {
			if (d[j] > mv) {
				ti = j;
				mv = d[j];
			}
		}
		t = d[i];
		d[i] = mv;
		d[ti] = t;
	}
	for (i = 0; i < k; i++) {
		scanf("%ld %d", &p[i], &q[i]);
	}
	ans = 0;
	for (i = 0; i < m; i++) {
		for (j = 0; j < k; j++) {
			du[j] = p[j] / d[i];
			if (p[j] % d[i]) {
				du[j]++;
			}
		}
		maxSum = 0;
		for (j = 1; j < (1 << k); j++) {
			jj = j;
			x = 0;
			timeSum = 0;
			moneySum = 0;
			while (jj) {
				if (jj & 1) {
					moneySum += q[x];
					timeSum += du[x];
				}
				if (timeSum > 900) {
					break;
				}
				x++;
				jj >>= 1;
			}
			if (timeSum <= 900) {
				if (moneySum > maxSum) {
					maxSum = moneySum;
				}
			}
		}
		ans += maxSum;
	}
	printf("%ld\n", ans);
	
	return 0;
}