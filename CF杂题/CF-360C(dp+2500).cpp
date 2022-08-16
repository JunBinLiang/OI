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
string s;
int mod = 1e9 + 7;
const int N = 2020;
ll dp[N][N];
ll sum[N];
void solve() { 
  cin >> n >> k;
  cin >> s;
  if(n == 1) {
    if(k > 1) {
      cout << 0 << endl;
      return;
    }
    if(k == 0) {
      cout << s[0] - 'a' + 1 << endl;
    } else if(k == 1) {
      cout << 26 - (s[0] - 'a' + 1) << endl;
    }
    return;
  }
  //0 1 2 3 4 5 6 7
  memset(dp, 0, sizeof(dp));
  memset(sum, 0, sizeof(sum));
  dp[0][0] = s[0] - 'a';
  dp[0][n] = 26 - (s[0] - 'a' + 1);
  sum[n] = dp[0][n];
  sum[0] = s[0] - 'a' + 1;
  
  ll res = 0;
  for(int i = 1; i < n; i++) {
    int len = n - i;
    int d = s[i] - 'a' + 1;
    for(int j = 0; j <= k; j++) {
      for(int l = i - 1; l >= 0 && j - len * (i - l) >= 0; l--) {
        dp[i][j] += dp[l][j - len * (i - l) ] * (26 - d);
        dp[i][j] %= mod;
      }
      
      if(j - len * (i + 1) == 0) {
        dp[i][j] += (26 - d);
        dp[i][j] %= mod;
      }
      
      if(i == n - 1 && j == k) {
          res += dp[i][j];
          res %= mod;
          res += (sum[j] * (d));
          res %= mod;
      }
      
      ll old = dp[i][j];
      dp[i][j] += (sum[j] * (d - 1)) ;
      dp[i][j] %= mod;
      sum[j] = sum[j] * (d) + old;
      sum[j] %= mod;
      
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

  
