
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

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector


template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

namespace Fenwick {
  const int SIZE = 100000 + 100;
  ll tree[2][SIZE];
  void init() {
    memset(tree, 0, sizeof tree);
  }

  void update(int which, int i, int val) {
    i++;
    while(i < SIZE){
      tree[which][i] += val;
      i += (i & -i);
    }
  }

  ll pre(int which, int i) {
    ll sum = 0;
    while(i > 0){
      sum += tree[which][i];
      i -= ( i & -i);
    }
    return sum;
  }
  ll query(int which, int i, int j) {
      return pre(which, j + 1) - pre(which, i);
  }
}

const int N = 1e5 + 10;
vector<int> g[N];
int fa[N], ids1[N], ids2[N], dep[N], r[N], to[N];
int id = 0;
int dfs(int pa, int u, int h) {
    fa[u] = pa;
    ids1[u] = id++;
    dep[u] = h;
    to[u] = 0;
    for(int nxt : g[u]) {
        if(nxt != pa) {
            to[u] = dfs(u, nxt, h + 1) + 1;
        }
    }
    return to[u];
}

void solve() {
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n - 1; i ++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    
    dfs(-1, 1, 0);
    
    queue<int> q;
    q.push(1);
    id = 0;
    int level = 0;
    while(q.size()) {
        int sz = q.size();
        for(int i = 0; i < sz; i++) {
            int u = q.front(); q.pop();
            ids2[u] = id++;
            for(int nxt : g[u]) {
                if(nxt != fa[u]) {
                    q.push(nxt);
                }
            }
        }
        r[level] = id - 1;
        level++;
    }
    
    //cout << r[0] << "  " << r[1] << endl;
    //cout << to[1] << "  " << to[2] << " " << to[3] << endl;
    
    
    //level : 0
    //line : 1
    Fenwick :: init();
    
    for(int i = 0; i < m; i++) {
        int op;
        cin >> op;
        if(op == 0) {
            int u, x, d;
            cin >> u >> x >> d;
            
            if(u == 1) {
                Fenwick :: update(0, 0, x);
                Fenwick :: update(0, r[min(level - 1, d)] + 1, -x);
                continue;
            }
            
            if(dep[u] > d) {
                Fenwick :: update(1, ids1[u] - d, x);
                Fenwick :: update(1, ids1[u] + min(to[u], d) + 1, -x);
                
            } else {
                int more = d - dep[u];
                
                Fenwick :: update(0, 0, x);
                Fenwick :: update(0, r[min(level - 1, more)] + 1, -x);
                
                int first = ids1[u] - dep[u] + 1;
                //update whole line
                Fenwick :: update(1, first , x);
                Fenwick :: update(1, ids1[u] + min(to[u], d) + 1, -x);
                if(more > 0) {
                    Fenwick :: update(1, first , -x);
                    Fenwick :: update(1, min(first + more - 1, ids1[u] + min(to[u], d)) + 1, x);
                }
            }
            
        } else {
            int u;
            cin >> u;
            cout << Fenwick :: query(0, 0, ids2[u]) + Fenwick :: query(1, 0, ids1[u]) << endl;
        }
    }
    
}


int main()
{   

    int t = 1;
    //cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
