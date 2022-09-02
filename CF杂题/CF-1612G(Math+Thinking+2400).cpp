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

   
using namespace std;  

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define f first
#define se second
#define W while
#define um unordered_map
#define us unordered_set
#define be begin
#define en end

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const unordered_map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

int mod = 1000000007;
const int N = 1e6 + 10;
ll fact[N];
unordered_map<int, int> f;
unordered_map<int, int> g;
void solve() { 
  int n;
  scanf("%d", &n);
  ll res = 0, ways = 1;

  fact[0] = fact[1] = 1;
  for(int i = 2; i < N; i++) {
    fact[i] = fact[i - 1] * i;
    fact[i] %= mod;
  }

  ll sum = 0;
  for(int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    sum += x;
    x--;
    if(x % 2 == 0) {
        f[x]++;
        f[-(x) - 1]--;
    } else {
        g[x]++;
        g[- (x) - 1]--;
    }
  }
  
  ll odd = 0;
  ll even = 0;
  for(ll i = N; i >= -N && sum > 0; i--) {
    even += f[i];
    odd += g[i];
    if(even < 0) even += mod;
    if(odd < 0) odd += mod;
    even %= mod;
    odd %= mod;
    
    if(abs(i) % 2 == 0 && even == 0) continue;
    if(abs(i) % 2 == 1 && odd == 0) continue;

    ll r = sum;
    if(abs(i) % 2 == 0) {
      ll l = r - even + 1;
      sum -= even;
      if(l <= r) {
        ll sz = r - l + 1;
        ll t = (l + r) * (sz) / 2;
        t %= mod;
        t *= i; t %= mod;
        if(t < 0) t += mod;
        res += (t);
        res %= mod;
      }
      ways *= fact[even];
      ways %= mod;
    } else {
      ll l = r - odd + 1;
      sum -= odd;
      if(l <= r) {
        ll sz = r - l + 1;
        ll t = (l + r) * (sz) / 2;
        t %= mod;
        t *= i; t %= mod;
        if(t < 0) t += mod;
        res += (t);
        res %= mod;
      }
      ways *= fact[odd];
      ways %= mod;
    }
    res %= mod;
  }
  if(res < 0) res += mod;
  cout << res << " " << ways << endl;


}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
}
  
  
