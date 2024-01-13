#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <list>
#include<fstream>
#include <bitset>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}




const int MOD = 998244353, N = 5010;
ll fact[N * 2], ifact[N * 2];

void init() {
  fact[0] = 1;
  for(int i = 1; i < N * 2; i++) {
    fact[i] = fact[i - 1] * i;
    fact[i] %= MOD;
  }
  
  ifact[0] = ifact[1] = 1;
  for (int i = 2; i < N * 2; i++) {
      ifact[i] = MOD - MOD / i * ifact[MOD % i] % MOD;
  }
  for (int i = 2; i < N * 2; i++) {
      ifact[i] = ifact[i - 1] * ifact[i] % MOD;
  }
}

ll fpow(ll x, int y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
}  

inline ll ncr(int n, int r) {
    if (r < 0 || n < r) {
        return 0;
    }
    return fact[n] * ifact[r] % MOD * ifact[n - r] % MOD;
}

ll ways(int n, int m) { //m balls on n box
  if(n < 0 || m < 0) {
    return 0;
  }
  return ncr(n + m - 1, m);
}

void solve() {
    int n;
    scanf("%d", &n);
    n++;
    vector<int> a(n * 2 + 1);
    int mn = n, mx = n;
    for(int i = 0; i < n - 1; i++) {
        int x;
        scanf("%d", &x);
        a[x + n]++;
        mn = min(mn, x + n);
        mx = max(mx, x + n);
    }
    a[n]++;

    for(int i = mn; i <= mx; i++) {
      if(!a[i]) {
        cout << 0 << endl;
        return;
      }
    }

    if(mn == mx) { //all 0, impossible
      cout << 0 << endl;
      return;
    }
    
    vector<int> d(mx + 1, 0); //already fill
    ll res = 0;
    for(int x = mx; x >= mn; x--) {
      d[mx - 1] = a[mx] + (mx > n) - (x == mx);
      for(int i = mx - 2; i >= mn - 1; i--) {
        d[i] = (a[i + 1] - d[i + 1]) + (i >= x) + (i >= n);
      }

      if(d[mn - 1] != 0) { //no ways to fill
        continue;
      }

      ll ans = 1;
      for(int i = mx - 1; i >= mn; i--) {
        ans *= ways(d[i], a[i] - d[i]);
        ans %= MOD;
      }
      res += ans;
      res %= MOD;
    }
    printf("%lld\n", res);
}
    

int main()
{
    init();
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
