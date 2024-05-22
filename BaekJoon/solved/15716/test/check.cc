/*
 * Code from : https://blog.naver.com/rdd573/221271008932
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#define sz(x) (int)(x).size()
using namespace std;
typedef long long ll;

vector<int> v;
int n;
ll b, x;
ll rr = 1e18;

ll csum(ll a, ll rotn, ll d) {
	ll sum = 0;
	if (rotn <= 0) return 0;
	if (rotn == 1) return a;
	
	if ((rotn - 1) > rr / d) return -1;
	sum = d * (rotn - 1) + 2 * a;
	
	if (sum / 2 > rr / rotn) return -1;
	return sum * rotn / 2;
}

ll doit(ll mid, int idx) {
	ll bb, temp, sum = 0, cyc = (b * 2 - 2);
	ll a1, a2;
	if (cyc <= mid) {
		bb = b - idx - 1;
		temp = csum(n, bb / n, n);
		if (temp == -1) return -1;

		sum += temp + (bb % n) * (bb / n + 1);
		// 역삼각
		a1 = 2;
		a2 = (a1 - 1) / n * n + 1;
		
		bb = b - a1 + 1;
		if ((a1 - 1) / n > rr / bb) return -1;
		sum += ((a1 - 1) / n) * bb;
			
		bb = b - a2 + 1 - idx;
		if (a1 - a2 - idx > 0) sum -= a1 - a2 - idx;
		
		temp = csum(n, bb / n, n);
		if (temp == -1) return -1;

		sum += temp + (bb % n) * (bb / n + 1);
	}

	if (sum && mid / cyc > rr / sum) return -1;
	sum *= mid / cyc;
	mid %= cyc;

	bb = min(b - 1, mid) - idx;
	if (bb >= 1) {
		temp = csum(n, bb / n, n);
		if (temp == -1) return -1;

		sum += temp + (bb % n) * (bb / n + 1);
	}

	// 역삼각
	if (mid >= b) {
		a1 = cyc - mid + 2;
		a2 = (a1 - 1) / n * n + 1;

		bb = b - a1 + 1;
		if ((a1 - 1) / n > rr / bb) return -1;
		sum += ((a1 - 1) / n) * bb;

		bb = b - a2 + 1 - idx;
		if (bb <= 0) return sum;
		if (a1 - a2 - idx > 0) sum -= a1 - a2 - idx;

		temp = csum(n, bb / n, n);
		if (temp == -1) return -1;

		sum += temp + (bb % n) * (bb / n + 1);
	}

	return sum;
}

int main() {
	char s[11], ts[11];

	scanf("%d %lld", &n, &b);
	scanf("%s %lld", s, &x);
    
	for (int i = 0; i < n; i++) {
		scanf("%s", ts);
		if (strcmp(ts, s) == 0) v.push_back(i);
	}
	
    if(b == 1) {printf("%lld\n", x); return 0;}
	ll l = 1, r = 1e18, mid, sum, temp;
	while (l <= r) {
		mid = (l + r) / 2;
		sum = 0;
		for (int i = 0; i < sz(v); i++) {
			temp = doit(mid, v[i]);
			if (temp == -1 || sum + temp > 1e18) { sum = 5e18; break; };
			sum += temp;
		}

		if (sum >= x) r = mid - 1;
		else l = mid + 1;
	}

	printf("%lld\n", l);
}