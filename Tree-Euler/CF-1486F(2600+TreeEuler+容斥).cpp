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

const int N = 3e5 + 10;
ve<int> g[N];
int d[N];
int f[N][21];
int in[N], out[N];
int id = 0;

namespace Fenwick {
  const int SIZE = N * 2 + 10;
  int tree[SIZE];
  void init() {
    memset(tree, 0, sizeof(tree));
  }

  void update(int i, int val) {
    i++;
    while(i < SIZE){
      tree[i] += val;
      i += (i & -i);
    }
  }

  int pre(int i) {
    int sum = 0;
    while(i>0){
      sum += tree[i];
      i -= ( i & -i);
    }
    return sum;
  }
  int query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
}

struct Edge {
  int u, v, x, y, lca, d;
};

bool COMP1(Edge& e1, Edge& e2) {
  if(e1.lca == e2.lca) {
    return e1.x < e2.x;
  }
  return e1.lca < e2.lca;
}

bool COMP2(Edge& e1, Edge& e2) {
  if(e1.d == e2.d) {
    return e1.lca < e2.lca;
  }
  return e1.d > e2.d;
}

void dfs(int pa, int root) {
  if(pa != -1) d[root] = d[pa] + 1;
  f[root][0] = pa;
  in[root] = id++;
  for(int& nxt : g[root]) {
    if(nxt == pa) continue;
    dfs(root, nxt);
  }
  out[root] = id++;
}

int LCA(int x,int y) {
  if(d[x] < d[y]){
    return LCA(y,x);
  }

  for(int i = 20; i>=0; i--) {
    if(f[x][i] != -1 && d[f[x][i]] >= d[y]) {
      x = f[x][i];
    }
  }

  if(x == y) return x;

  for(int i = 20; i>=0; i--) {
    if(f[x][i] != f[y][i]) {                    
      x = f[x][i];
      y = f[y][i];
    }
  }
  return f[x][0];
}

int jump(int u, int k) {
  if(k < 0) return -1;
  for(int i = 20; i >= 0; i--) {
    if(k & (1 << i)) u = f[u][i];
  }
  return u;
}

void solve() {
  int n, m;
  ll res = 0;
  scanf("%d", &n);
  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    g[u].pb(v); g[v].pb(u);
  }
  
  d[0] = 0;
  dfs(-1, 0);
  
  
  for(int i = 1; i < 21; i++) {
    for(int j = 0; j < n; j++) {
      if(f[j][i - 1] == -1) continue;
      f[j][i] = f[f[j][i - 1]][i - 1];
    }
  }


  scanf("%d", &m);
  ve<Edge> a;
  for(int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    int lca = LCA(u, v);
    int d1 = jump(u, d[u] - d[lca] - 1);
    int d2 = jump(v, d[v] - d[lca] - 1);
    //cout << u << " " << v << " " << lca << endl;
    a.pb({u, v, min(d1, d2), max(d1, d2) , lca, d[lca]});
  }

  sort(a.begin(), a.end(), COMP1);
  Fenwick :: init();

  for(int i = 0; i < a.size(); i++) {
    int j = i;
    while(j < a.size() && a[j].lca == a[i].lca) { //same lca
      j++;
    }
    ll sum = 0;
    map<int, int> ma;
    ll cnt = 0;
    for(int k = i; k < j; k++) {
      int idx = k;
      while(idx < j && a[idx].x == a[k].x) {
        int x = a[idx].x, y = a[idx].y;
        if(x == -1 && y == -1) { //single point
          cnt++;
        } else {
          res += sum;
          if(x == -1) {
              sum++;
              res -= ma[y];
              ma[y]++;
          } else {
              res -= ma[y];
              res -= ma[x];
          }
        }
        idx++;
      }
      
      idx = k;
      while(idx < j && a[idx].x == a[k].x) {
        int x = a[idx].x, y = a[idx].y;
        if(x == -1 && y == -1) {
          idx++;
          continue;
        } else {
          if(x != -1 && y != -1) {
              sum++;
              ma[x]++; ma[y]++;
          }
        }
        idx++;
      }
      
      
      k = idx - 1;
    }
    ll total = j - i;
    res += ((total - cnt) * cnt);
    res += (cnt * (cnt - 1) / 2);
    i = j - 1;
  }

  
  sort(a.begin(), a.end(), COMP2);
  for(int i = 0; i < a.size(); i++) {
    int j = i;
    int lca = a[i].lca;
    while(j < a.size() && a[j].lca == a[i].lca) {
      int in1 = in[lca];
      int u = a[j].u, v = a[j].v;
      if(u != lca) {
          int in2 = in[u];
          res += Fenwick::query(in1, in2);
      }
      if(v != lca) {
          int in2 = in[v];
          res += Fenwick::query(in1, in2);
      }
      j++;
    }
    
    

    j = i;
    while(j < a.size() && a[j].lca == a[i].lca) {
      int u = a[j].u, v = a[j].v, x = a[j].x, y = a[j].y;
      Fenwick :: update(in[lca], 1);
      Fenwick :: update(out[lca], -1);
      
      if(x != -1) {
        Fenwick :: update(in[x], -1);
        Fenwick :: update(out[x], 1);
      }
      if(y != -1) {
        Fenwick :: update(in[y], -1);
        Fenwick :: update(out[y], 1);
      }
      j++;
    }
    i = j - 1;
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

