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


int n, m, p;
const int N = 2e5 + 100;
ll D[N];
ll S[N];
ll q[N];
ll dp[105][N];
ll res = 1000000000000000000ll;
int hh, tt;
/**
to take a cat : s + d[i] >= t 
s >= t - d[i]
a[i] = t - d[i] and sort a[i]

To take a[j + 1 to i]
Time : (a[i] * (i - j)) - (S[i] - S[j])

//dp[j] from last level
dp[i] = dp[j] + (a[i] * (i - j)) - (S[i] - S[j])
dp[i] = dp[j] + a[i] * i - a[i] * j - S[i] + S[j]

dp[j] = dp[i] - a[i] * i + a[i] * j + S[i] - S[j]
=>
dp[j] + S[j] = (a[i] * j) + dp[i] - a[i] * i + S[i]

(dp[j] + S[j], j) => minimize dp[i]
**/

ll up(int i, int x1, int x2) {
  return (dp[i][x1] + S[x1]) - (dp[i][x2] + S[x2]);
}
ll down(int x1, int x2) {
  return x1 - x2;
}

int main() {
  scanf("%d%d%d", &n, &m, &p);
  D[0] = D[1] = 0;
  for(int i = 2; i <= n; i++) {
    int d;
    scanf("%d", &d);
    D[i] = d + D[i - 1];
  }
   
  
  S[0] = 0;
  memset(dp, 0, sizeof(dp));
  
  vector<ll> a(m + 1);
  for(int i = 1; i <= m; i++) {
    int h, t;
    scanf("%d%d", &h, &t);
    a[i] = t - D[h];
  }
  
  sort(a.begin() + 1, a.end());
  for(int i = 1; i <= m; i++) {
      S[i] = S[i - 1] + a[i];
  }
  
  for(int i = 1; i <= m; i++) {
    dp[1][i] = (a[i] * i) - S[i];
  }
  
  for(int i = 2; i <= p; i++) {
    hh = 0, tt = 1;
    q[0] = 0;
    for(int j = 1; j <= m; j++) {
      while(tt - hh > 1 && up(i - 1, q[hh + 1], q[hh]) <= (a[j]) * down(q[hh + 1], q[hh]) ) {
        hh++;
      }
      //dp[i] = dp[j] + a[i] * i - a[i] * j - S[i] + S[j]
      int k = q[hh];
      dp[i][j] = dp[i - 1][k] + a[j] * j - a[j] * k - S[j] + S[k];
      while(tt - hh > 1 && up(i - 1, j, q[tt - 1]) * down(q[tt - 1], q[tt - 2]) <= up(i - 1, q[tt-1], q[tt-2])* down(j, q[tt - 1])) {
        tt--;
      }
      q[tt++] = j;
    }
  }

  cout << dp[p][m] << endl;
  
}
