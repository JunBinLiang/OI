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


const int N = 2e5 + 10;
int a[N];
ll pre[N];
ll dp[N];
ve<pair<int, int>> g[N];
int n, m;

const int MAX = 2e5 + 10;
struct Node {
  int l, r;
  ll setTo, mx;
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

void update(int id, int s, int e, ll val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e) {
    tree[id].setTo += val;
    tree[id].mx += val;
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
  tree[id].mx = max(tree[left].mx, tree[right].mx);
}

ll query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mx;
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


ll get(int l, int r) {
  if(l > r) return 0;
  if(l == 0) return pre[r];
  return pre[r] - pre[l - 1];
}

void solve() {
  ll res = 0;
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  pre[0] = 0;
  for(int i = 1; i <= n; i++) {
    pre[i] = pre[i - 1] + a[i];
  }
  

  for(int i = 0; i < m; i++) {
    int l, r, w;
    scanf("%d%d%d", &l, &r, &w);
    g[r].pb({l, w});
  }

  tree[0] = {0, n, 0, 0};
  build(0);
  update(0, 0, 0, -get(1, n));
  ll dp[N];
  dp[0] = 0;
  for(int i = 1; i <= n; i++) {
    ll post = get(i + 1, n);
    ll extra = get(i + 1, n);
    for(pair<int, int>& p : g[i]) {
      int l = p.first, w = p.second;
      update(0, 0, l - 1, w);
    }

    ll best = query(0, 0, i - 1) + extra;
    best = max(best, 0ll);
    best = max(best, dp[i - 1]);
    dp[i] = best;
    res = max(res, best);
    update(0, i, i, best - post);
    
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

