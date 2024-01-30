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
#define P pair
#define V vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define FFOR(i, a, b) for (int i = a; i <= b; ++i)

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

const int MOD = 1e9 + 7, M = 65;

ll fpow(ll x, int y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
}  

void solve() {
  int n;
  cin >> n;
  vector<ll> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  sort(a.begin(), a.end());
  vector<ll> offs;
  for(int x = 0; x < n - 1; x++) {
    while(a.size() > M) a.pop_back();
    ll l = a[0] + a[1], r = a[a.size() - 2] + a.back();
    ll p = -1;
    while(l <= r) {
      ll mid = l + (r - l) / 2;
      int cnt = 0;
      int L = 0, R = a.size() - 1;
      while(L < R) {
        if(a[L] + a[R] > mid) {
          R--;
        } else {
          cnt += (R - L);
          L++;
        }
      }
      
      if(cnt >= a.size() - 1) {
        p = mid;
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    
    vector<ll> b;
    int L = 0, R = a.size() - 1;
    while(L < R) {
      if(a[L] + a[R] > p - 1) {
        R--;
      } else {
        for(int i = L + 1; i <= R; i++) b.push_back(a[L] + a[i]);
        L++;
      }
    }
    
    while(b.size() != a.size() - 1) b.push_back(p);
    while(b.size() < M) b.push_back(p);
    sort(b.begin(), b.end());
    offs.push_back(b[0]);
    for(int i = 0; i < b.size(); i++) b[i] -= offs.back();
    a = b;
  }


  ll res = a[0] % MOD;
  for(int i = 0; i < offs.size(); i++) {
    ll v = (offs[i] * fpow(2, n - i - 2)) % MOD;
    res += v;
    res %= MOD;
  }

  cout << res << endl;
}

    

int main()
{
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
