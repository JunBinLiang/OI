
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

const int N = 1010;

void build(int n, int m) {
  vector<pair<int, int>> e;
  if(m == 2) {
    for(int i = 0; i < n; i++) {
      for(int j = i + 1; j < n; j++) {
        e.push_back({i, j});
      }
    }

  } else {
    for(int i = 0; i < m; i++) {
      e.push_back({i, (i + 1) % m});
    }

    for(int i = m; i < n; i++) {
      e.push_back({i, (i + 1) % m});
      e.push_back({i, (m + i - 1) % m});
    }
  }

  cout << e.size() << endl;
  for(auto& p : e) {
    cout << p.first << " " << p.second << endl;
  }
}

bool dp[N][N];

void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> a(m);
  for(int i = 0; i < m; i++) {
    cin >> a[i];
    //cout << a[i] << endl;
  }

  
  for(int i = 0; i <= m; i++) {
      for(int j = 0; j <= n; j++) {
          dp[i][j] = false;
      }
  }
  
  dp[0][0] = true;
  for(int i = 0; i < m; i++) {
    for(int j = 0; j <= n; j++) {
      if(dp[i][j]) {
        dp[i + 1][j] = true;
        if(j + a[i] <= n) {
          dp[i + 1][j + a[i]] = true;
        }
      }
    }
  }

  int p = -1;
  for(int i = 1; i <= n; i++) {
    if(dp[m][i] == false) {
      p = i;
      break;
    }
  }

  if(p == -1) {
    cout << "SI" << endl;
    return;
  }

  if(n >= 2 * p) {
    cout << "NO" << endl;
    build(n, p * 2);
    return;
  }

  cout << "SI" << endl;
}

int main() {
  ios::sync_with_stdio(false);
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
