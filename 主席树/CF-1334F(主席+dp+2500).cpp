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


int n, m;
const int N = 5e5 + 10;
int a[N], b[N], p[N];
int ma[N];
ll dp[N];
int ids[N];
ll vals[N];
const ll INF = 1000000000000000000ll;

namespace Fenwick {
  const int SIZE = 500000 + 100;
  ll tree[SIZE];
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

  ll pre(int i) {
    ll sum = 0;
    while(i>0){
      sum += tree[i];
      i -= (i & -i);
    }
    return sum;
  }
  ll query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
}



struct Node {
  int lid, rid;
  ll tot;
} tree[N * 22];

int idx = 0;
void build(int id, int l, int r) {
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  int idx1 = idx;
  int idx2 = idx + 1;
  idx += 2;
  tree[id].lid = idx1;
  tree[id].rid = idx2;
  tree[idx1] = {-1, -1, 0};
  tree[idx2] = {-1, -1, 0};
  build(idx1, l, mid);
  build(idx2, mid + 1, r);
}

void update(int preId, int curId, int index, int val, int l, int r) {
  if(l == r) {
    vals[l] += val;
    tree[curId].tot = vals[l];
    return;
  }
  int mid = l + (r - l) / 2;
  if (index <= mid) {//update left
    tree[curId].rid = tree[preId].rid;
    tree[idx] = {-1, -1, 0};
    tree[curId].lid = idx;
    idx++;
    update(tree[preId].lid, tree[curId].lid, index, val, l, mid);
  } else {//update right
    tree[curId].lid = tree[preId].lid;    
    tree[idx] = {-1, -1, 0};
    tree[curId].rid = idx;
    idx++;
    update(tree[preId].rid, tree[curId].rid, index, val, mid + 1, r);
  }
  tree[curId].tot = tree[tree[curId].lid].tot + tree[tree[curId].rid].tot;
}

ll query(int id, int s, int e, int l, int r) {
  if(l == s && r == e){
    return tree[id].tot;
  }
  int mid = l + (r - l) / 2;
  int left = tree[id].lid, right = tree[id].rid;
  if(e <= mid){
      return query(left, s, e, l, mid);
  } else if(s >= mid + 1) {
      return query(right, s, e, mid + 1, r);
  } else {
    return query(left, s, mid, l, mid) + query(right, mid + 1, e, mid + 1, r);
  }
}

void solve() {
    scanf("%d", &n);
    int mx = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        mx = max(mx, a[i]);
    }
    for(int i = 0; i < n; i++) scanf("%d", &p[i]);
    scanf("%d", &m);
    memset(ma, -1, sizeof ma);
    memset(vals, 0, sizeof vals);
    for(int i = 0; i < m; i++) {
        scanf("%d", &b[i]);
        ma[b[i]] = i;
    }
    for(int i = 0; i < m; i++) dp[i] = INF;
    tree[0] = {-1, -1, 0};
    ids[n] = idx;
    idx++;
    build(0, 0, mx + 1);
    for(int i = n - 1; i >= 0; i--) {
        ids[i] = idx; 
        tree[idx] = {-1, -1, 0};
        idx++;
        update(ids[i + 1], ids[i], a[i], p[i], 0, mx + 1);
    }
    
    Fenwick :: init();
    for(int i = n - 1; i >= 0; i--) {
        if(p[i] < 0) {
            Fenwick :: update(a[i], p[i]);
        }
    }
    
    if(m == 1) {
        ll sum = 0, res = INF;
        for(int i = 0; i < n; i++) 
        {
            if(p[i] < 0) Fenwick :: update(a[i], -p[i]);
            if(a[i] == b[0]) {
                res = min(res, sum + query(ids[i + 1], b[0] + 1, mx + 1, 0, mx + 1) + Fenwick :: query(0, b[0]));
                
            }
            sum += p[i];
        }
        
        if(res == INF) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
            cout << res << endl;
        }
        return;
    }
    
    
    
    ll sum = 0;
    for(int i = 0; i < n; i++) {
        if(p[i] < 0) Fenwick :: update(a[i], -p[i]);
        if(ma[a[i]] == -1) {
            sum += p[i];
            continue;
        } else {
            int idx1 = ma[a[i]];
            if(idx1 == 0) {
                dp[0] = min(dp[0], sum + query(ids[i + 1], b[0] + 1, mx + 1, 0, mx + 1) + Fenwick :: query(0, b[idx1]));
            } else {
                dp[idx1] = min(dp[idx1], dp[idx1 - 1] - query(ids[i], b[idx1 - 1] + 1, mx, 0, mx + 1) - Fenwick :: query(0, b[idx1 - 1]) + query(ids[i + 1], b[idx1] + 1, mx + 1, 0, mx + 1) + Fenwick :: query(0, b[idx1]));
                
            }
            sum += p[i];
        }
        
    }

    if(dp[m - 1] >= 10000000000000000ll) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        cout << dp[m - 1] << endl;
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
