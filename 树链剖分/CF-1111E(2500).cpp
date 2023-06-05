#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;
using ll = long long;

const int N = 1e5 + 10, M = 19, mod = 1e9 + 7;
ll dp[2][310];
int sz[N], dep[N], fa[N], son[N], top[N];
int L[N];
int f[N][M];
int ids[N];
vector<int> g[N];
int n, m; int cnt = 0;

namespace Fenwick {
  const int SIZE = 200000 + 100;
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

/*
void update_path(int u, int v, int k) {
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        update(0, ids[top[u]], ids[u], k);
        u = fa[top[u]];
    }
    //same heave-line
    if(dep[u] < dep[v]) swap(u, v);
    update(0, ids[v], ids[u], k);
}*/

ll query_path(int u, int v) {
    ll res = 0;
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        res += Fenwick :: query(ids[top[u]], ids[u]);
        u = fa[top[u]];
    }
    if(dep[u] < dep[v]) swap(u, v);
    res += Fenwick :: query(ids[v], ids[u]);
    return res;
}


int LCA(int x,int y) {
  if(dep[x] < dep[y]){
    return LCA(y,x);
  }

  for(int i = 18; i>=0; i--) {
    if(f[x][i] != -1 && dep[f[x][i]] >= dep[y]) {
      x = f[x][i];
    }
  }

  if(x == y) return x;

  for(int i= 18; i>=0; i--) {
    if(f[x][i] != f[y][i]) {
      x = f[x][i];
      y = f[y][i];
    }
  }
  return f[x][0];
}

void dfs(int pa, int root, int h) {
    fa[root] = pa;
    f[root][0] = pa;
    sz[root] = 1;
    dep[root] = h;
    for(int& nxt : g[root]) {
        if(nxt == pa) continue;
        dfs(root, nxt, h + 1);
        sz[root] += sz[nxt];
        if(son[root] == -1) {
            son[root] = nxt;
        } else {
            if(sz[nxt] > sz[son[root]]) {
                son[root] = nxt;
            }
        }
    }
}

void dfs1(int pa, int root, int line) {
    top[root] = line;
    ids[root] = cnt;
    cnt++;
    if(son[root] == -1) return;
    dfs1(root, son[root], line);
    for(int& nxt : g[root]) {
        if(nxt == pa || nxt == son[root]) continue;
        dfs1(root, nxt, nxt); //a new heavy line
    }

}

bool comp(int u, int v) {
    return L[u] < L[v];
}

void solve() {
    memset(son, -1, sizeof son);

    cin >> n >> m;
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    Fenwick :: init();
    memset(f, -1, sizeof f);
    dfs(-1, 0, 0);
    dfs1(-1, 0, 0);
    //init sparse table
    for(int i = 1; i < M; i++) {
        for(int j = 0; j < n; j++) {
            if(f[j][i - 1] != -1) {
                f[j][i] = f[f[j][i - 1]][i - 1];
            }
        }
    }

    while(m--) {
       int k, m, r;
       scanf("%d%d%d",&k, &m, &r);
       r--;
       vector<int> a;
       for(int i = 0; i < k; i++) {
           int x;
           scanf("%d", &x);
           x--;
           a.push_back(x);
       }


       for(int u : a) {
            int ith = ids[u];
            Fenwick :: update(ith, 1);
       }

       for(int i = 0; i < a.size(); i++) {
            int u = a[i], v = r;
            if(dep[u] < dep[v]) {
                swap(u, v);
            }
            int lca = LCA(u, v);
            int dup = 0;
            if(lca == v) {
                dup += query_path(u, v);
            } else {
                dup += query_path(u, lca);
                dup += query_path(v, lca);
                dup -= Fenwick :: query(ids[lca], ids[lca]);
            }
            L[a[i]] = dup;
       }

       sort(a.begin(), a.end(), comp);

       memset(dp, 0, sizeof dp);
       dp[0][0] = 1;
       for(int i = 1; i <= a.size(); i++) {
           int u = a[i - 1], v = r;
           /*if(dep[u] < dep[v]) {
                swap(u, v);
           }
           int lca = LCA(u, v);
           int dup = 0;
           if(lca == v) {
                dup += query_path(u, v);
           } else {
                dup += query_path(u, lca);
                dup += query_path(v, lca);
                dup -= Fenwick :: query(ids[lca], ids[lca]);
           }*/
           int dup = L[u] - 1;

           //cout << u << "  " << dup <<"  " << L[u] << endl;
           dp[1][0] = 0;
           for(int j = 1; j <= m; j++) {
                dp[1][j] = dp[0][j - 1];
                dp[1][j] += (dp[0][j] * max(0, j - dup));
                dp[1][j] %= mod;
           }
           swap(dp[0], dp[1]);
       }

       for(int u : a) { //reset Fenwick Tree for next query
            int ith = ids[u];
            Fenwick :: update(ith, -1);
       }

       ll res = 0;
       for(int j = 1; j <= m; j++) {
            res += dp[0][j];
            res %= mod;
       }
       cout << res << endl;
    }
}



int main() {
    solve();
    return 0;
}

/*
7 1
5 4
2 6
5 3
1 2
7 5
4 6
3 3 2 7 4 3


*/
