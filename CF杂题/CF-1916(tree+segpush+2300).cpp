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
#include <bitset>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define pb push_back


const int MAX = 3e5 + 10, INF = 1e9;
struct Node {
  int l, r;
  int setTo;
  int max1;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, 0, 0};
  tree[id * 2 + 2] = {mid + 1, r, 0, 0};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int s, int e, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e) {
    tree[id].setTo += val;
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;

  if(tree[id].setTo != 0) {
    update(left, tree[left].l, tree[left].r, tree[id].setTo);
    update(right, tree[right].l, tree[right].r, tree[id].setTo);
    tree[id].setTo = 0;
  }

  if(e <= mid) {
    update(left, s, e, val);
  } else if(s >= mid + 1) {
    update(right, s, e, val);
  } else {
    update(left, s, mid, val);
    update(right, mid + 1, e, val);
  }

  tree[id].max1 = max(tree[left].max1 + tree[left].setTo, tree[right].max1 + tree[right].setTo);
}

int query(int id, int s, int e) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].max1 + tree[id].setTo;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;

  if(tree[id].setTo != 0) {
    update(left, tree[left].l, tree[left].r, tree[id].setTo);
    update(right, tree[right].l, tree[right].r, tree[id].setTo);
    tree[id].setTo = 0;
  }
  
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return max(query(left, s, mid), query(right, mid + 1, e));
  }
}


const int N = 3e5 + 10;
vector<int> g[N], stks[N], clear[N];
int a[N], pre[N], sz[N], ids[N];
int id = 0;
ll res = 0;

void dfs1(int u) {
    if(stks[a[u]].size()) {
        pre[u] = stks[a[u]].back();
    }
    stks[a[u]].push_back(u);
    sz[u] = 1;
    ids[u] = id++;
    for(int nxt : g[u]) {
        dfs1(nxt);
        sz[u] += sz[nxt];
    }
    stks[a[u]].pop_back();
}

void dfs2(int u) {
    
    for(int nxt : g[u]) {
        dfs2(nxt);
    }
    
    for(int v : clear[u]) {
        int ll = ids[v], rr = ll + sz[v] - 1;
        update(0, ll, rr, -1);
    }
    
     
    ll p = 0;
    for(int nxt : g[u]) {
        int l = ids[nxt], r = l + sz[nxt] - 1;
        ll max1 = query(0, l, r);
        res = max(res, max1 + 1);
        res = max(res, (max1 + 1ll) * p);
        p = max(p, max1 + 1);
    }
    
    int l = ids[u], r = l + sz[u] - 1;
    update(0, l, r, 1);

}

void solve() {
    int n;
    cin >> n;

    //reset
    id = 0;
    res = 1;
    tree[0] = {0, n + 1, 0, 0};
    build(0);
    for(int i = 0; i <= n; i++) {
        g[i].clear();
        stks[i].clear();
        clear[i].clear();
        pre[i] = -1;
    }

    for(int i = 2; i <= n; i++) {
        int p;
        scanf("%d", &p);
        g[p].push_back(i);
    }

    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    dfs1(1);
    for(int i = 1; i <= n; i++) {
        if(pre[i] != -1) {
            clear[pre[i]].push_back(i);
        }
    }

    dfs2(1);
    printf("%lld\n", res);
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
