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


const int N = 1e5 + 10;
int mod = 1e9 + 7;
int n, m;
int a[N]; ll res[N];
ve<pair<int, int>> g[N];

ll fpow(ll x, int y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % mod;
		x = (x * x) %mod;
		y >>= 1;
	}
	return res;
}  

void solve() { 
  scanf("%d%d", &n, &m);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  for(int i = 0; i < m; i++) {
    int l, x;
    scanf("%d%d", &l, &x);
    g[l - 1].pb({x, i});
  }

  int k = 0;
  int b[30];
  memset(b, 0, sizeof(b));
  for(int i = 0; i < n; i++) {
    if(a[i] != 0) {
      for(int j = 24; j >= 0; j--) {
        if(a[i] & (1 << j)) {
          if(b[j]) a[i] ^= b[j];
          else {
            b[j] = a[i];
            k++;
            break;
          }
        }
      }
    }

    for(pair<int, int>&p : g[i]) {
      int x = p.first, idx = p.second;
      bool good = true;
      for(int j = 24; j >= 0; j--) {
        if(x & (1 << j)) {
          if(!b[j]) {
              good = false; break;
          }
          x ^= b[j];
        }
      }
      if(good) res[idx] = fpow(2, i + 1 - k);
      else res[idx] = 0;
    }
  }
  


  for(int i = 0; i < m; i++) {
    printf("%lld\n", res[i]);
  }

  
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
}
  
  
