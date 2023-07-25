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
#include <fstream>
#include <iomanip>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}
 


const int N = 1e5 + 10;
//const int N = 1000;
vector<int> g[N];
int f[N][18], d[N], sz[N], dp[N];
int n, s, t;
ll res = 0;

int LCA(int x,int y) {
  if(d[x] < d[y]){
    return LCA(y,x);
  }

  for(int i = 17; i>=0; i--) {
    if(f[x][i] != -1 && d[f[x][i]] >= d[y]) {
      x = f[x][i];
    }
  }

  if(x == y) return x;

  for(int i = 17; i>=0; i--) {
    if(f[x][i] != f[y][i]) {                    
      x = f[x][i];
      y = f[y][i];
    }
  }
  return f[x][0];
}

void dfs(int pa, int u, int h) {
  f[u][0] = pa;
  d[u] = h;
  sz[u] = 1;
  for(int& nxt : g[u]) {
    if(nxt != pa) {
      dfs(u, nxt, h + 1);
      sz[u] += sz[nxt];
    }
  }
}

void dfs1(int pa, int u) {
    int lca = LCA(u, t);
    res += dp[lca];
    for(int nxt : g[u]) {
      if(nxt == pa || nxt == t) continue;
      dfs1(u, nxt);
    }
}

void solve() {
    res = 0;

    cin >> n >> s >> t;
    for(int i = 0; i <= n; i++) g[i].clear();
    for(int i = 0; i < n - 1; i++) {
      int u, v;
      cin >> u >> v;
      g[u].push_back(v);
      g[v].push_back(u);
    }
    
    if(s == t) {
        cout << 0 << endl;
        return;
    }
    
    for(int i = 0; i <= n; i++) for(int j = 0; j < 18; j++) f[i][j] = -1;
    dfs(-1, s, 0);
    
    for(int i = 1; i < 18; i++) {
        for(int j = 1; j <= n; j++) {
            if(f[j][i - 1] != -1) {
                f[j][i] = f[f[j][i - 1]][i - 1];
            }
        }
    }
    
    int u = t;
    while(u != s) {
      dp[f[u][0]] = sz[u];
      u = f[u][0];
    }

    dfs1(-1, s);
    cout << res << endl;
    
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

