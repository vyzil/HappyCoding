// https://www.acmicpc.net/source/18330473

#include <string.h>
#include <stdio.h>
#define MAX 1000001
char str[MAX];
char pass[MAX];
int pi[MAX];
int res[MAX];
int rCnt;
void getPi() {
	int n = strlen(pass);
	for (int i = 1, mat = 0; i < n; ++i) {
		if (pass[i] == pass[mat]) {
			pi[i] = ++mat;
		}
		else if (mat != 0) {
			--i;
			mat = pi[mat - 1];
		}
	}
}
void kmp() {
	int n = strlen(str), m = strlen(pass);
	for (int i = 0, mat = 0; i < n; ++i) {
		if (str[i] == pass[mat]) {
			if (++mat == m) {
				res[rCnt++] = i - m + 1;
			}
		}
		else if (mat != 0) {
			--i;
			mat = pi[mat - 1];
		}
	}
}
int main() {
	char in[1 << 15], out[1 << 18];
	setvbuf(stdin, in, _IOFBF, sizeof(in));
	setvbuf(stdout, out, _IOFBF, sizeof(out));
	gets(str);
	gets(pass);
	//scanf("%[^\n]", str);
	//scanf("%[^\n]", pass);
	getPi();
	kmp();
	printf("%d\n", rCnt);
	for (int i = 0; i < rCnt; ++i) {
		printf("%d ", res[i] + 1);
	}
	return 0;
}
