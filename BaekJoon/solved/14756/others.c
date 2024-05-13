#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> &a, bool inv) {
  int n = a.size();
  for (int i=1, j=0; i<n; i++) {
    int bit = n>>1;
    while(!((j^=bit) & bit)) bit >>= 1;
    if(i<j) swap(a[i],a[j]);
  }
  for (int i=1; i<n; i<<=1) {
    double x = inv? M_PI/i : -M_PI/i;
    cd w(cos(x),sin(x));
    for (int j=0; j<n; j+=i<<1) {
      cd p(1,0);
      for (int k=0;k<i;++k) {
        cd tmp = a[i+j+k] * p;
        a[i+j+k] = a[j+k] - tmp, a[j+k] += tmp, p *= w;
      }
    }
  }
  if(inv) for (int i=0; i<n; ++i) a[i] /= n;
}

vector<ll> multiply(const vector<ll> &a, const vector<ll> &b) {
  vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  int n = 1;
  while (n < a.size() + b.size()) 
    n <<= 1;
  fa.resize(n);
  fb.resize(n);

  fft(fa, false);
  fft(fb, false);
  for (int i = 0; i < n; i++)
    fa[i] *= fb[i];
  fft(fa, true);

  vector<ll> result(n);
  for (int i = 0; i < n; i++)
    result[i] = ll(round(fa[i].real()));
  return result;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);cout.tie(0);
  ll n,l,m,W,ret=0; cin>>n>>l>>m>>W;
  vector<vector<ll>> u(m,vector<ll>(n)), w(m,vector<ll>(l));
  for (int i=0; i<m; i++)
    for (int j=0; j<n; j++)
      cin>>u[i][j];
  for (int i=0; i<m; i++) {
    for (int j=0; j<l; j++)
      cin>>w[i][j];
    reverse(w[i].begin(),w[i].end());
  }
  vector<vector<ll>> v(m);
  for (int i=0; i<m; i++)
    v[i]=multiply(u[i],w[i]);
  for (int i=l-1; i<n; i++) {
    ll cur=0;
    for (int j=0; j<m; j++)
      cur+=v[j][i];
    if(cur>W) ret++;
  }
  cout<<ret<<"\n";
  return 0;
}