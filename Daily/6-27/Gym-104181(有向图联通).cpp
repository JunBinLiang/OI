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

const int N = 10010, M = 50010;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, Size[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ timestamp;
    stk[ ++ top] = u, in_stk[u] = true;
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        else if (in_stk[j]) low[u] = min(low[u], dfn[j]);
    }

    if (dfn[u] == low[u])
    {
        ++ scc_cnt;
        int y;
        do {
            y = stk[top -- ];
            in_stk[y] = false;
            id[y] = scc_cnt;
            Size[scc_cnt] ++ ;
        } while (y != u);
    }
}

int n, m;
set<pair<int, int>> s;
vector<int> g[N];

int dfs(int u) {
    int sz = Size[u];
    int best = 0;
    for(int nxt : g[u]) {
        best = max(best, dfs(nxt));
    }
    return sz + best;
}

void solve() {
  memset(h, -1, sizeof h);

  cin >> n >> m;
  for(int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    add(u, v);
  }


  for(int i = 1; i <= n; i++) {
      if(!dfn[i]) {
        tarjan(i);
      }
  }
  
  /*for(int i = 1; i <= n; i++) {
      cout << id[i] << endl;
  }*/

  for(int i = 1; i <= n; i++) {
    for(int j = h[i]; ~j; j = ne[j]) {
      int id1 = id[i], id2 = id[e[j]];
      if(id1 == id2) continue;
      if(s.find({id1, id2}) == s.end()) { //construct a compressed graph
          g[id1].push_back(id2);
          s.insert({id1, id2});
      }
    }
  }
  
  int res = 0;
  for(int i = 1; i <= n; i++) {
      int u = id[i];
      res = max(res, dfs(u));
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
