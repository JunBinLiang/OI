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

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}



const int N = 1e5 + 10;
ve<int> g[N], f[N];
int ans[N];
int cnt[N];
int id[N];
int idx = 0;

const int MAX = N;
struct Node {
  int l, r;
  int setTo = 0, sum = 0;
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
    if(tree[id].setTo) {
        tree[id].sum = r - l + 1;
    } else {
        if(l == r) {
            tree[id].sum = 0;
        } else {
            tree[id].sum = tree[id * 2 + 1].sum + tree[id * 2 + 2].sum;
        }
    }
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;

  /*if(tree[id].setTo != 0) {
    update(left, tree[left].l, tree[left].r, tree[id].setTo);
    update(right, tree[right].l, tree[right].r, tree[id].setTo);
    tree[id].setTo = 0;
  }*/

  if(e <= mid) {
    update(left, s, e, val);
  } else if(s >= mid + 1) {
    update(right, s, e, val);
  } else {
    update(left, s, mid, val);
    update(right, mid + 1, e, val);
  }

  tree[id].sum = tree[left].sum + tree[right].sum;
  if(tree[id].setTo) {
    tree[id].sum = r - l + 1;
  }

}

void dfs1(int pa, int root) {
  cnt[root] = 1;
  for(int nxt : g[root]) {
    if(nxt == pa) continue;
    dfs1(root, nxt);
    cnt[root] += cnt[nxt];
  }
  id[root] = idx++;
}

void dfs2(int pa, int root ) {
  for(int x : f[root]) {
    int r = id[x];
    int l = id[x] - cnt[x] + 1;
    update(0, l, r, 1);
  }
  ans[root] = (tree[0].sum) - 1;
  for(int nxt : g[root]) {
    if(nxt == pa) continue;
    dfs2(root, nxt);
  }

  
  for(int x : f[root]) {
    int r = id[x];
    int l = id[x] - cnt[x] + 1;
    update(0, l, r, -1);
  }
}

void solve() { 
  int n, m;
  scanf("%d%d", &n, &m);
  memset(ans, 0, sizeof(ans));
  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    g[u].pb(v);
    g[v].pb(u);
  }

  dfs1(-1, 0);
  for(int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    f[u].pb(v);
    f[u].pb(u);
    
    f[v].pb(u);
    f[v].pb(v);
  }

  tree[0] = {0, n - 1, 0, 0};
  build(0);
  dfs2(-1, 0);

  for(int i = 0; i < n; i++) {
    printf("%d ", max(0, ans[i]));
  }
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
}
  
  
