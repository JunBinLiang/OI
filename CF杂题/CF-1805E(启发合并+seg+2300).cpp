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
#define P pair
#define V vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define FFOR(i, a, b) for (int i = a; i <= b; ++i)

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}


template <typename T>
ostream &operator<<(ostream &out, const unordered_set<T> &a)
{
  out << "[";
  bool first = true;
  for (auto v : a)
  {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

//3:30 - 4: 02

const int MAX = 200000 + 100;

struct Node {
  int l, r;
  int mx;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, 0};
  tree[id * 2 + 2] = {mid + 1, r, 0};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int index, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mx = max(tree[id].mx, val);  
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(left, index, val);
  } else {
    update(right, index, val);
  }
  tree[id].mx = max(tree[left].mx, tree[right].mx);
}

int query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mx;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return max(query(left, s, mid), query(right, mid + 1, e));
  }
}


const int N = 2e5 + 10;
int a[N], b[N];
vector<pair<int, int>> g[N];
int sz[N], ids[N], ans[N], nodeMax[N];
int L[N], R[N], to[N];
pair<int, int> q[N];
unordered_set<int> s[N];
int id = 0;

void dfs(int p, int u) { //assign
  sz[u] = 1;
  ids[u] = id++;
  b[ids[u]] = a[u];
  for(auto& pa : g[u]) {
    int nxt = pa.first;
    if(nxt == p) continue;
    dfs(u, nxt);
    sz[u] += sz[nxt];
  }
}

void dfs1(int p, int u) {
  for(auto& pa : g[u]) {
    int nxt = pa.first, j = pa.second;
    if(nxt == p) continue;
    int l = ids[nxt], r = ids[nxt] + sz[nxt] - 1; 
    q[l] = {r, j};
    dfs1(u, nxt);
  }
}

void dfsMerge(int p, int u, int i) {
  s[u].insert(a[u]);
  for(auto& pa : g[u]) {
    int nxt = pa.first, j = pa.second;
    if(nxt == p) continue;
    dfsMerge(u, nxt, j);
    if(s[u].size() < s[nxt].size()) swap(s[u], s[nxt]);
    nodeMax[u] = max(nodeMax[u], nodeMax[nxt]);
    for(auto v : s[nxt]) {
      if(s[u].find(v) != s[u].end()) {
        nodeMax[u] = max(nodeMax[u], v);
      } else {
        s[u].insert(v);
      }
    }
  }
  if(p != -1) {
    ans[i] = nodeMax[u];
  }
}

void solve() {
  int n;
  scanf("%d", &n);
  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back({v, i});
    g[v].push_back({u, i});
  }
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  memset(sz, 0, sizeof sz);
  memset(nodeMax, 0, sizeof nodeMax);
  memset(to, -1, sizeof to);
  for(int i = 0; i <= n; i++) q[i] = {-1, -1};

  dfs(-1, 1);
  dfs1(-1, 1);
  dfsMerge(-1, 1, -1);

  
  unordered_map<int, int> p;
  for(int i = n - 1; i >= 0; i--) {
    if(p.find(b[i]) == p.end()) {
      p[b[i]] = i;
    }
    to[i] = p[b[i]];
  }


  unordered_map<int, int> f;
  int curMax = 0;
  for(int i = n - 1; i >= 0; i--) {
    f[b[i]]++;
    if(f[b[i]] > 1) curMax = max(curMax, b[i]);
    R[i] = curMax;
  }

  f.clear();
  curMax = 0;
  tree[0] = {0, n + 1, 0};
  build(0);
  for(int i = 0; i < n; i++) {
    f[b[i]]++;
    if(f[b[i]] > 1) curMax = max(curMax, b[i]);
    L[i] = curMax;
  
    if(q[i].first != -1) {
      int r = q[i].first, j = q[i].second;
      if(i - 1 >= 0) ans[j] = max(ans[j], L[i - 1]);
      if(r + 1 < n) ans[j] = max(ans[j], R[r + 1]);
      ans[j] = max(ans[j], query(0, r + 1, n));
    }
    
    if(to[i] != -1) {
      update(0, to[i], b[i]);
    }
  }


  for(int i = 0; i < n - 1; i++) {
    printf("%d\n", ans[i]);
  }
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
