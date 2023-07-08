#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
#include <vector>

using namespace std;

const int N = 3010;
pair<int, int> a[N];
vector<int> g[N];
int dp[N];
int n;
int x, y;

void dfs(int u) {
  if(dp[u] != -1) {
    return;
  }
  dp[u] = 1;
  int mx = 0;
  for(int nxt : g[u]) {
    dfs(nxt);
    mx = max(mx, dp[nxt]);
  }
  dp[u] += mx;
}

void add(int u, int v, int x1, int y1, int x2, int y2) {
  int t = (y2 - y1) - 1;
  int xdif = abs(x1 - x2) - 1;
  //cout << "check " << u << " " << v << "    |" << xdif << " " << t << endl;
  if(xdif <= t) {
    g[u].push_back(v);
    //cout << "add " << u << " " << v << "    |" << xdif << " " << t << "      |" << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
  }
}

set<pair<int, int>> s;
void solve() {
  memset(dp, -1, sizeof dp);
  s.clear();
  cin >> x >> y >> n;
  
  for(int i = 1; i <= n; i++) {
    scanf("%d%d", &a[i].first, &a[i].second);
    s.insert({a[i].first, a[i].second});
  }
  
  for(int i = 0; i <= 2 * n + 10; i++) g[i].clear();

  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= n; j++) {
      if(i == j) continue;
      //add(i, j, a[i].first, a[i].second, a[j].first, a[j].second);
      add(i, j + n, a[i].first, a[i].second, a[j].first, a[j].second - 1);
      add(i + n, j, a[i].first, a[i].second - 1, a[j].first, a[j].second);
      //add(i + n, j, a[i].first, a[i].second - 1, a[j].first, a[j].second - 1);
    }
  }


  for(int i = 1; i <= n; i++) {
    add(0, i, x, y, a[i].first, a[i].second);
    add(0, i + n, x, y, a[i].first, a[i].second - 1);
  }

  dfs(0);
  int res = dp[0];
  //if(s.find({x, y}) != s.end()) res++;
  while(true) {
    if(s.find({x, y - 1}) != s.end()) {
      res++;
      y--;
    } else {
      break;
    }
  }
  cout << res - 1 << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
      solve();
    }
    return 0;
}

