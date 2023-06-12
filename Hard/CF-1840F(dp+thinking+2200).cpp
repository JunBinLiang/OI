
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
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int N = 1e4 + 10;
void solve() {
  int n, m, R;
  scanf("%d%d%d", &n, &m, &R);
  bool bad[n + 1][m + 1][R + 5];
  bool dp[n + 1][m + 1][R + 5];
  memset(bad, false, sizeof bad);
  memset(dp, false, sizeof dp);

  for(int i = 0; i < R; i++) {
    int t, d, coord;
    scanf("%d%d%d", &t, &d, &coord);
    if(d == 1) { //row
      int r = coord;
      for(int c = 0; c <= m; c++) {
        int T = t - r - c;
        if(T >= 0 && T <= R) {
          bad[r][c][T] = true;
        }
      }      
    } else {
      int c = coord;
      for(int r = 0; r <= n; r++) {
        int T = t - r - c;
        if(T >= 0 && T <= R) {
          bad[r][c][T] = true;
        }
      }
    }
  }

  
  for(int i = 0; i <= R; i++) {
    if(!bad[0][0][i]) {
        dp[0][0][i] = true;
    } else {
        break;
    }
  }

  for(int i = 0; i <= n; i++) {
    for(int j = 0; j <= m; j++) {
      for(int k = 0; k <= R; k++) {
        if(i - 1 >= 0) {
          if(!bad[i - 1][j][k] && !bad[i][j][k]) {
            dp[i][j][k] |= dp[i - 1][j][k]; 
          }
        }
        if(j - 1 >= 0) {
          if(!bad[i][j - 1][k] && !bad[i][j][k]) {
            dp[i][j][k] |= dp[i][j - 1][k]; 
          }
        }
        
        if(k - 1 >= 0 && !bad[i][j][k - 1]) {
            dp[i][j][k] |= dp[i][j][k - 1]; 
        }
      }
    }
  }

  int ans = -1;
  for(int i = 0; i <= R + 1; i++) {
    if(dp[n][m][i]) {
      ans = n + m + i;
      break;
    }
  }
  printf("%d\n", ans);

}

int main()
{   
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
