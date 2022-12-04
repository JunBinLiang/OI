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

const int MAX = 3e5 + 100;

struct Node {
  int l, r;
  ll mn;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, 9000000000000000000ll};
  tree[id * 2 + 2] = {mid + 1, r, 9000000000000000000ll};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int index, ll val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mn = min(tree[id].mn, val);  
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(left, index, val);
  } else {
    update(right, index, val);
  }
  tree[id].mn = min(tree[left].mn, tree[right].mn);
}

ll query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mn;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return min(query(left, s, mid), query(right, mid + 1, e));
  }
}

const int N = 3e5 + 10;
const ll INF = 9000000000000000000ll;
int n, m;
pair<int, int> a[N];
vector<pair<int, int>> q1[N], q2[N];
ll res[N];
void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i <= m; i++) res[i] = INF;
    tree[0] = {0, n, INF};
    build(0);

    for(int i = 1; i <= n; i++) {
        int x, w;
        scanf("%d%d", &x, &w);
        a[i] = {x, w};
    }

    
    for(int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        q1[r].push_back({l, i});
        q2[l].push_back({r, i});
    }


    vector<int> stk;
    for(int i = 1; i <= n; i++) {
        while(stk.size() > 0 && a[i].second <= a[stk.back()].second) {
            int idx = stk.back();
            ll val = abs(a[i].first - a[idx].first + 0ll) * (a[i].second + a[idx].second + 0ll);
            update(0, idx, val);
            stk.pop_back();
        }
        if(stk.size() > 0) {
            int idx = stk.back();
            ll val = abs(a[i].first - a[idx].first + 0ll) * (a[i].second + a[idx].second + 0ll);
            update(0, idx, val);
        }
        stk.push_back(i);
        for(pair<int, int>& p : q1[i]) {
            int l = p.first, idx = p.second;
            res[idx] = min(res[idx], query(0, l, i));
        }

    }

    tree[0] = {0, n, INF};
    build(0);
    stk.clear();

    for(int i = n; i >= 1; i--) {
        while(stk.size() > 0 && a[i].second <= a[stk.back()].second) {
            int idx = stk.back();
            ll val = abs(a[i].first - a[idx].first + 0ll) * (a[i].second + a[idx].second + 0ll);
            update(0, idx, val);
            stk.pop_back();
        }
        if(stk.size() > 0) {
            int idx = stk.back();
            ll val = abs(a[i].first - a[idx].first + 0ll) * (a[i].second + a[idx].second + 0ll);
            update(0, idx, val);
        }
        stk.push_back(i);
        for(pair<int, int>& p : q2[i]) {
            int r = p.first, idx = p.second;
            res[idx] = min(res[idx], query(0, i, r));
        }

    }


    for(int i = 0; i < m; i++) {
        printf("%lld\n", res[i]);
    }

}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
