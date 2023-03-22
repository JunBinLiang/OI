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
#include <iostream>
   
using ll = long long;
using namespace std;  


namespace Fenwick {
  const int SIZE = 4e5 + 100;
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


const int N = 2e5 + 10, M = 5e5 + 10;
int idx = 0, tail = -1;
int tr[N][26];
int q[N], ne[N], ids[N];
vector<int> g[N], all[N];
vector<pair<int, int>> ri[N], le[N];
ll res[M];
char str[N];


void insert(int id)
{
    int p = 0;
    for (int i = 0; str[i]; i ++ )
    {
        int t = str[i] - 'a';
        if (!tr[p][t]) tr[p][t] = ++ idx;
        p = tr[p][t];
        all[id].push_back(p);
    }
    ids[id] = p;
}

void build()
{
    int hh = 0, tt = -1;
    for (int i = 0; i < 26; i ++ )
        if (tr[0][i])
            q[ ++ tt] = tr[0][i];
    
    tail = tt;
    while (hh <= tt)
    {
        int t = q[hh ++ ];
        for (int i = 0; i < 26; i ++ )
        {
            int p = tr[t][i];
            if (!p) tr[t][i] = tr[ne[t]][i];
            else  
            {
                ne[p] = tr[ne[t]][i];
                q[ ++ tt] = p;
                tail = tt;
            }
        }
    }
}

//////////////////////////////////////////////////////////
struct Node {
  int l, r;
  ll add, sum;
} tree[N * 4];

void build(int id) {
    int l = tree[id].l, r = tree[id].r;
    if(l == r) {
        tree[id].sum = 0;
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

int fa[N], sz[N], dep[N], son[N], top[N], idss[N];
int cnt = 0;
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
    idss[root] = cnt;
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
        update(0, idss[top[u]], idss[u], k);
        u = fa[top[u]];
    }
    //same heave-line
    if(dep[u] < dep[v]) swap(u, v);
    update(0, idss[v], idss[u], k);
}

ll query_path(int u, int v) {
    ll res = 0;
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        res += query(0, idss[top[u]], idss[u]);
        u = fa[top[u]];
    }
    if(dep[u] < dep[v]) swap(u, v);
    res += query(0, idss[v], idss[u]);
    return res;
}

void solve() {
    int n, m;
    scanf("%d%d", &n, &m);

    for(int i = 1; i <= n; i++) {
        scanf("%s", str);
        insert(i);
    }

    build();
    for(int i = tail; i >= 0; i--) {
        int node = q[i];
        g[ne[node]].push_back(node);
        
        //cout <<"graph :" << ne[node] << " " << node << endl;
    }
    
    memset(son, -1, sizeof son);
    dfs(-1, 0, 0);
    dfs1(-1, 0, 0);
    
    //树链更新整条路
    tree[0] = {0, tail + 1, 0, 0};
    build(0);


    for(int i = 0; i < m; i++) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        le[l - 1].push_back({k, i});
        ri[r].push_back({k, i});
    }

    for(int i = 1; i <= n; i++) {
        for(int node : all[i]) {
            update_path(0, node, 1);
            //cout << "update  " << node << endl;
        }

        for(auto& p : le[i]) {
            int node = ids[p.first], ith = p.second;
            res[ith] -= query_path(node, node);
        }
        
        for(auto& p : ri[i]) {
            int node = ids[p.first], ith = p.second;
            res[ith] += query_path(node, node);
        }
    }

    for(int i = 0; i < m; i++) {
        printf("%lld\n", res[i]);
    }

}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
