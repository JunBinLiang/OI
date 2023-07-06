#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int N = 21;
int n, k;
int a[N];
int dp[(1 << 21) + 10][N];

void solve() {
  cin >> n >> k;
  for(int i = 0; i < n; i++) cin >> a[i];
  for(int i = 0; i < (1 << n); i++) {
      for(int j = 0; j <= n; j++) {
          dp[i][j] = k + 1;
      }
  }
  

  dp[0][0] = 0;
  for(int st = 1; st < (1 << n); st++) {
    for(int i = 0; i < n; i++) {
      if(st & (1 << i)) {
        int v = a[i];
        for(int j = 1; j <= n; j++) {
            if(dp[st ^ (1 << i)][j - 1] <= k) {
                dp[st][j] = min(dp[st][j], v);
            }
            
            if(dp[st ^ (1 << i)][j] + v <= k) {
                dp[st][j] = min(dp[st][j], dp[st ^ (1 << i)][j] + v);
            }
            //cout << st << " "  << i << " "  << j << "  |" << dp[i][j] << endl;
        }
      }
    }
  }
  
  int res = n;
  int full = (1 << n) - 1;
  for(int i = 1; i <= n; i++) {
      if(dp[full][i] <= k) {
          res = i;
          break;
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
    return 0;
}

