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


int mod = 998244353;
const int N = 2e5 + 10;
ll fact[N];
ll fpow(ll x, int y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % mod;
		x = (x * x) %mod;
		y >>= 1;
	}
	return res;
} 

ll C(int n,int m) {
  return fact[n] * fpow(fact[n - m], mod - 2) % mod * fpow (fact[m], mod - 2) % mod;
}


void solve() {
  int n;
  cin >> n;
  int w = 0, b = 0, x = 0;
  int ww = 0, bb = 0, xx = 0;
  set<char> s1, s2;
  for(int i = 0; i < n; i++) {
    string t;
    cin >> t;
    for(int j = 0; j < 2; j++) {
      w += (t[j] == 'W');
      b += (t[j] == 'B');
      x += (t[j] == '?');
      if(j == 0) {
        if(t[j] != '?') {
          s1.insert(t[j]);
        }
      } else {
        if(t[j] != '?') {
          s2.insert(t[j]);
        }
      }
    }
    if(t == "WW") ww++;
    if(t == "BB") bb++;
    if(t == "??") xx++;
    
  }

  if(w > n || b > n) {
    cout << 0 << endl;
    return;
  }

  fact[0] = fact[1] = 1;
  for(int i = 2; i < N; i++) fact[i] = (fact[i - 1] * i) % mod;



  int cnt = n * 2 - w - b;
  ll ways = C(cnt, n - b);

  if(ww > 0 || bb > 0) {
    cout << ways << endl;
    return;
  }

  //only same type
  ll total = fpow(2, xx);
  ll res = (ways - total + mod) % mod;

  if(xx == n) {
    res += 2; res %= mod;
  } else {
    if(s1.size() < 2 && s2.size() < 2) {
      res ++;
      res %= mod;
    }
  }
  cout << res << endl;

}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
}
