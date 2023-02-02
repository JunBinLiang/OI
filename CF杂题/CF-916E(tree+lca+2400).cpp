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
#include<fstream>
 

using namespace std;  
using ll = long long;
#define pb push_back

//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");

const int N = 1e5 + 10;
int n, m;
vector<int> g[N];
int a[N], newa[N], sz[N], ids[N], d[N];
int fa[N][18];
int root = 0, cnt = 0;

struct Node {
  int l, r;
  ll add, sum;
} tr[N * 4];

void build(int id) {
  int l = tr[id].l, r = tr[id].r;
  if(l == r) {
    tr[id].sum = newa[l];
    return;
  }
  int mid = l + (r - l) / 2;
  tr[id * 2 + 1] = {l, mid, 0, 0};
  tr[id * 2 + 2] = {mid + 1, r, 0, 0};
  build(id * 2 + 1);
  build(id * 2 + 2);
  tr[id].sum = tr[id * 2 + 1].sum + tr[id * 2 + 2].sum;
}

void update(int id, int s, int e, ll add) { 
  int l = tr[id].l, r = tr[id].r;
  if(l == s && r == e) {
    tr[id].add += add;
    tr[id].sum += (add * (r - l + 1));
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;

  if(tr[id].add != 0) {
    update(left, tr[left].l, tr[left].r, tr[id].add);
    update(right, tr[right].l, tr[right].r, tr[id].add);
    tr[id].add = 0;
  }

  if(e <= mid) {
    update(left, s, e, add);
  } else if(s >= mid + 1) {
    update(right, s, e, add);
  } else {
    update(left, s, mid, add);
    update(right, mid + 1, e, add);
  }
  tr[id].sum = tr[left].sum + tr[right].sum;
}

ll query(int id, int s, int e) {
  int l = tr[id].l, r = tr[id].r;
  if(l == s && r == e){
    return tr[id].sum;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(tr[id].add != 0) {
    update(left, tr[left].l, tr[left].r, tr[id].add);
    update(right, tr[right].l, tr[right].r, tr[id].add);
    tr[id].add = 0;
  }
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return query(left, s, mid) + query(right, mid + 1, e);
  }
}




void dfs(int pa, int root, int h) {
    sz[root] = 1;
    ids[root] = cnt;
    newa[cnt] = a[root];
    d[root] = h;
    fa[root][0] = pa;
    cnt++;
    for(int &nxt : g[root]) {
        if(nxt == pa) continue;
        dfs(root, nxt, h + 1);
        sz[root] += sz[nxt];
    }
}

int LCA(int x,int y) {
  if(d[x] < d[y]){
    return LCA(y,x);
  }

  for(int i = 17; i >= 0; i--) {
    if(fa[x][i] != -1 && d[fa[x][i]] >= d[y]) {
      x = fa[x][i];
    }
  }

  if(x == y) return x;

  for(int i = 17; i >= 0; i--) {
    if(fa[x][i] != fa[y][i]) {                    
      x = fa[x][i];
      y = fa[y][i];
    }
  }
  return fa[x][0];
}

int jump(int u, int k) {
    for(int i = 17; i >= 0; i--) {
        if(k & (1 << i)) {
            u = fa[u][i]; 
        }
    }
    return u;
}

void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for(int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(-1, 0, 0);
    for(int i = 1; i < 18; i++) {
        for(int j = 0; j < n; j++) {
            if(fa[j][i - 1] != -1) {
                fa[j][i] = fa[fa[j][i - 1]][i - 1];
            }
        }
    }
    
    tr[0] = {0, n - 1, 0, 0};
    build(0);
    
    int cnt = 0;
    for(int i = 0; i < m; i++) {
        int op;
        int u, v, k;
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d", &u);
            u--;
            root = u;
        } else if(op == 2) {
            scanf("%d%d%d", &u, &v, &k);
            u--; v--;

            int lca = LCA(u, v);
            int lca1 = LCA(u, root);
            int lca2 = LCA(v, root);
            if(lca1 == root && lca2 == root) { 
                if(lca == root) {
                    update(0, 0, n - 1, k);
                    continue;
                }
                update(0, ids[lca], ids[lca] + sz[lca] - 1, k);
                continue;
            } 

            if(lca1 == root || lca2 == root) { //update the whole tree
                update(0, 0, n - 1, k);
                continue;
            }

            if(d[lca] > d[root] || jump(root, d[root] - d[lca]) != lca) {
                update(0, ids[lca], ids[lca] + sz[lca] - 1, k);
            } else {
                int realRoot = -1;
                if(d[lca1] > d[lca2]) {
                    realRoot = lca1;
                } else {
                    realRoot = lca2;
                }
                update(0, 0, n - 1, k);
                int to = jump(root, d[root] - d[realRoot] - 1);
                update(0, ids[to], ids[to] + sz[to] - 1, -k);
            }


        } else {
            cnt++;
            scanf("%d", &u);
            u--;
            
            int lca = LCA(u, root);
            if(lca == root) {
                if(u == root) {
                    u = 0;
                }
                ll res = query(0, ids[u], ids[u] + sz[u] - 1);
                printf("%lld\n", res);
                continue;
            }
            
            if(u == lca) {
                ll res = tr[0].sum;
                int to = jump(root, d[root] - d[lca] - 1);
                ll t = query(0, ids[to], ids[to] + sz[to] - 1);
                res -= t;
                printf("%lld\n", res);
            } else {
                ll res = query(0, ids[u], ids[u] + sz[u] - 1);
                printf("%lld\n", res);
            }
            
        }
    }
} 


int main() {
	// your code goes here
	int t = 1;
	//cin >> t;
	while(t--) {
	    solve();
	}
	return 0;
}  
