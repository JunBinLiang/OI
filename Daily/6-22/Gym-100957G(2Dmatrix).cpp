
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

const int N = 1000 + 50, M = 1e5 + 10;
int a[N][N], dp[N][N];

struct Q {
  int r1, c1, r2, c2, w;
} q[M];

void solve() {
  memset(dp, 0, sizeof dp);

  int t;
  cin >> t;
  for(int i = 0; i < t; i++) {
    cin >> q[i].r1 >> q[i].c1 >> q[i].r2 >> q[i].c2 >> q[i].w;
  }

  int n, m;
  cin >> n >> m;
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      cin >> a[i][j];
    }
  }

  for(int i = 0; i < t; i++) {
    int r1 = q[i].r1, c1 = q[i].c1, r2 = q[i].r2, c2 = q[i].c2, w = q[i].w;
    dp[r2][c2] += w;
    dp[r1 - 1][c2] -= w;
    dp[r2][c1 - 1] -= w;
    dp[r1 - 1][c1 - 1] += w;
  }

  /*for(int i = 0; i <= n; i++) {
      for(int j = 0; j <= m; j++) {
          cout << dp[i][j] << " ";
      } cout << endl;
  }
  cout << endl;*/

  for(int i = n; i >= 0; i--) {
    for(int j = m; j >= 0; j--) {
      dp[i][j] += (dp[i + 1][j] + dp[i][j + 1]) - dp[i + 1][j + 1];
    }
  }


  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      cout << a[i][j] + dp[i][j] << " ";
    }
    cout << endl;
  }
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


