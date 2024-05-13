n, x, y, l, *a[100001], s[100001], b[100001];
f(int *q, int *w) { return b[*q] - b[*w]; }
g(int d, int e) {
	if (b[d] != ++l)
		exit(!puts("0"));
	for (int i = 0; i < s[d]; i++)
		if (a[d][i] != e)
			g(a[d][i], d);
}
main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &x, &y);
		a[x] = realloc(a[x], 4 * s[x] + 4);
		a[x][s[x]++] = y;
		a[y] = realloc(a[y], 4 * s[y] + 4);
		a[y][s[y]++] = x;
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		b[x] = i;
	}
	for (int i = 1; i <= n; i++)
		qsort(a[i], s[i], 4, f);
	g(1, 0);
	puts("1");
}