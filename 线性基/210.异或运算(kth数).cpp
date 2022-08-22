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

const int N = 1e4 + 10;
ll a[N];
int n, m;
int c = 0;
void solve() { 
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    scanf("%lld", &a[i]);
  }
  
  int k = 0;
  for(int i = 62; i >= 0; i--) {
      for(int j = k; j < n; j++) {
          if(a[j] & (1ll << i)) {
              swap(a[j], a[k]);
              break;
          }
      }
      if((a[k] & (1ll << i)) == 0) continue;
      for(int j = 0; j < n; j++) {
          if(j != k && a[j] & (1ll << i)) {
              a[j] ^= a[k];
          }
      }
      k++;
      if(k == n) break;
  }
  
  //k == n:线性无关
  //k < n : 线性相关
  
  ve<ll> base;
  for(int i = 0; i < k; i++) base.pb(a[i]);
  reverse(base.begin(), base.end());
  
  scanf("%d", &m);
  printf("Case #%d:\n", c);
  for(int i = 0; i < m; i++) {
      ll x;
      scanf("%lld", &x);
      if(k < n) { //0 能表示
          x--;
      }
      if(x >= (1ll << k)) {
          printf("-1 \n");
          continue;
      }
      ll res = 0;
      for(int j = 0; j < k; j++) {
          if(x & (1ll << j)) {
              res ^= base[j];
          }
      }
      printf("%lld\n", res);
  }
}

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        c++;
        solve();
    }
}
  
