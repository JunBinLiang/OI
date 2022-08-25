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



int n, k;
const int N = 2e5 + 10;
const int M = 890;
const int mod = 998244353;
int sts[N];
int dp[N];
int cur[N];
int res[N];


void solve() { 
  scanf("%d%d", &n, &k);
  memset(sts, 0, sizeof(sts));
  memset(dp, 0, sizeof(dp));
  memset(res, 0, sizeof(res));
  ve<bool> is(n + 1);
  
  for(int i = k; i <= n; i += k) {
    sts[i] = k + 1;
    dp[i] = 1;
    res[i] = 1;
  }
  

  for(int st = k + 1; st <= n; st++) {
    int sz = (st - k - 1);
    int start = ((k + k + sz - 1) * sz) / 2;
    
    if(start > n) break;
    
    for(int i = start; i <= n; i++) {
        is[i] = false;
    }
    
    for(int i = start; i <= n; i++) {
      if(sts[i] != st) continue;
      if(is[i]) continue;
      is[i] = true;
      ll sum = dp[i];
      for(int j = i + st; j <= n; j += st) {
        is[j] = true;
        cur[j] += sum; cur[j] %= mod;
        sum += dp[j];  sum %= mod;
        sts[j] = st + 1;
      }
    }

    for(int i = start; i <= n; i++) {
      dp[i] = cur[i]; 
      res[i] += cur[i];
      res[i] %= mod;
      cur[i] = 0;
    } 
  }
  for(int i = 1; i <= n; i++) {
    cout << res[i] << " ";
  }
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
}
  
  
