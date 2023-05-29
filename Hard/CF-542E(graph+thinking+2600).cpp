
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

//基数环 => 拆成 odd + even
//偶数环 => 拆成 odd + odd or even + even 
const int N = 1010;
vector<int> g[N];
int n, m, id = 0;
bool isb = true;
int col[N], vis[N], L[N];
void dfs(int u, int c) {
  vis[u] = id;
  col[u] = c;
  for(int nxt : g[u]) {
    if(vis[nxt] != -1) {
      if(col[u] == col[nxt]) {
        isb = false;
      }
    } else {
      dfs(nxt, c ^ 1);
    }
  }
}

int bfs(int s) {
  queue<int> q;
  vector<int> d(n + 1, -1);
  int res = 0;
  d[s] = 0;
  q.push(s);
  while(q.size()) {
    int u = q.front();
    res = max(res, d[u]);
    q.pop();
    for(int v : g[u]) {
      if(d[v] == -1) {
        d[v] = 1 + d[u];
        q.push(v);
      }
    }
  }
  return res;
}

void solve() {
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v;
      g[u].push_back(v);
      g[v].push_back(u);
    }

    memset(col, -1, sizeof col);
    memset(vis, -1, sizeof vis);
    memset(L, 0, sizeof L);

    for(int i = 1; i <= n; i++) {
      if(vis[i] == -1) {
        dfs(i, 0);
        id++;
      }
    }
    
    if(!isb) {
      cout << -1 << endl;
      return;
    }
    
    for(int i = 1; i <= n; i++) {
      int len = bfs(i);
      int which = vis[i];
      L[which] = max(L[which], len);
      //cout << which << " " << len << endl;
    }

    int res = 0;
    for(int i = 0; i < id; i++) {
      res += L[i];
    }
    cout << res << endl;
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
