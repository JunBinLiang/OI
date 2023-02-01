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
vector<int> g[N];
int a[N], newa[N], sz[N], dep[N], fa[N], son[N], top[N];
int ids[N];
int n, m, cnt = 0;

struct Node {
  int l, r;
  ll add, sum;
} tree[N * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].sum = newa[l];
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, 0, 0};
  tree[id * 2 + 2] = {mid + 1, r, 0, 0};
  build(id * 2 + 1);
  build(id * 2 + 2);
  tree[id].sum = tree[id * 2 + 1].sum + tree[id * 2 + 2].sum;
}

void update(int id, int s, int e, ll add) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e) {
    tree[id].add += add;
    tree[id].sum += (add * (r - l + 1));
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;

  if(tree[id].add != 0) {
    update(left, tree[left].l, tree[left].r, tree[id].add);
    update(right, tree[right].l, tree[right].r, tree[id].add);
    tree[id].add = 0;
  }

  if(e <= mid) {
    update(left, s, e, add);
  } else if(s >= mid + 1) {
    update(right, s, e, add);
  } else {
    update(left, s, mid, add);
    update(right, mid + 1, e, add);
  }
  tree[id].sum = tree[left].sum + tree[right].sum;
}

ll query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].sum;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(tree[id].add != 0) {
    update(left, tree[left].l, tree[left].r, tree[id].add);
    update(right, tree[right].l, tree[right].r, tree[id].add);
    tree[id].add = 0;
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
    fa[root] = pa;
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
    newa[cnt] = a[root];
    cnt++;
    if(son[root] == -1) return;
    dfs1(root, son[root], line);
    for(int& nxt : g[root]) {
        if(nxt == pa || nxt == son[root]) continue;
        dfs1(root, nxt, nxt); //a new heavy line
    }
}

void update_path(int u, int v, int k) {
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        update(0, ids[top[u]], ids[u], k);
        u = fa[top[u]];
    }
    //same heave-line
    if(dep[u] < dep[v]) swap(u, v);
    update(0, ids[v], ids[u], k);
}

ll query_path(int u, int v) {
    ll res = 0;
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        res += query(0, ids[top[u]], ids[u]);
        u = fa[top[u]];
    }
    if(dep[u] < dep[v]) swap(u, v);
    res += query(0, ids[v], ids[u]);
    return res;
}

void solve() {
    memset(son, -1, sizeof son);

    scanf("%d", &n);
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
    dfs1(-1, 0, 0);
    tree[0] = {0, n - 1, 0, 0};
    build(0);


    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);
        if(op == 1) {
            int u, v, k;
            scanf("%d%d%d", &u, &v, &k);
            u--; v--;
            update_path(u, v, k);
        } else if(op == 2) {
            int u, k;
            scanf("%d%d", &u, &k);
            u--;
            update(0, ids[u], ids[u] + sz[u] - 1, k);
        } else if(op == 3) {
            int u, v;
            scanf("%d%d", &u, &v);
            u--; v--;
            ll sum = query_path(u, v);
            printf("%lld\n", sum);
        } else {
            int u;
            scanf("%d", &u);
            u--;
            ll sum = query(0, ids[u], ids[u] + sz[u] - 1);
            printf("%lld\n", sum);
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
