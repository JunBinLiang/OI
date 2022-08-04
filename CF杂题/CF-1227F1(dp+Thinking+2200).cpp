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

//1 : 05 - 1 : 30
int n; ll k;
int mod = 998244353;
const int N = 2050; 
int a[N];
int b[N];
ll dp[N][N][2];
ll dfs(int i, int m, int state) {
  if(i >= n) {
    if(state == 0) {
      if(m > 0) return 1;
      else return 0;
    } else {
      return 0;
    }
  }
  if(dp[i][m][state] != -1) {
    return dp[i][m][state];
  }
  ll res = 0;
  if(a[i] == b[i]) {
    res += k * dfs(i + 1, m, state);
    res %= mod;
  } else {
    if(state == 0) { // b has more
      //put b
      res += dfs(i + 1, m + 1, state);
      res %= mod;
      //put a
      if(m > 0) {
        res += dfs(i + 1, m - 1, state);
        res %= mod;
      } else {
        res += dfs(i + 1, 1, 1);
        res %= mod;
      }

    } else { // a has more
      //put a
      res += dfs(i + 1, m + 1, state);
      res %= mod;
      //put b
      if(m > 0) {
        res += dfs(i + 1, m - 1, state);
        res %= mod;
      } else {
        res += dfs(i + 1, 1, 0);
        res %= mod;
      }
    }
    res += dfs(i + 1, m, state) * (k - 2);
    res %= mod;
  }
  return dp[i][m][state] = res;
}

void solve() {
  scanf("%d%d", &n, &k);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    b[(i + 1) % n] = (a[i]);
    
  }
  
  memset(dp, -1, sizeof(dp));
  ll res = dfs(0, 0, 0);
  cout << res << endl;
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
}
