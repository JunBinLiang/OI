
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int MAX = 2e5 + 10;
struct Node {
  int l, r;
  int cnt = 0;
  ll sum = 0;
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

void update(int id, int index, int val, int add) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    if(add == 1) {
        tree[id].sum += val;
        tree[id].cnt += add;
    } else {
        tree[id].sum -= val;
        tree[id].cnt += add;
    }
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(left, index, val, add);
  } else {
    update(right, index, val, add);
  }
  tree[id].sum = (tree[left].sum + tree[right].sum);
  tree[id].cnt = (tree[left].cnt + tree[right].cnt);
}

ll query(int id, int s, int e) { // query sum from [0 : l]
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].sum;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return query(left, s, mid) + query(right, mid + 1, e);
  }
}

ll query1(int id, int s, int e) { // query sum from [0 : l]
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].cnt;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query1(left, s, e);
  } else if(s >= mid + 1) {
      return query1(right, s, e);
  } else {
    return query1(left, s, mid) + query1(right, mid + 1, e);
  }
}


int dfs(int id, int tot) {
  if(tree[id].l == tree[id].r) {
    return tree[id].l;
  }
  //cout <<"dfs " << tree[id].l << " " << tree[id].r << "  " << tree[id].cnt << "  |" << tot << endl;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(tree[left].cnt >= tot) {
    return dfs(left, tot);   
  } else {
    return dfs(right, tot - tree[left].cnt);
  }
}

const int N = 2e5 + 10;
const ll INF = 1000000000000000000ll;
int a[N], b[N], c[N];
int cnt[N];
ll p1[N], p2[N];
vector<int> v1, v2, v3, v4;

ll get(ll p[], int l, int r) {
  if(l > r) return 0;
  if(l == 0) return p[r];
  return p[r] - p[l - 1];
}


void solve() {
  ll res = INF;
  memset(cnt, 0, sizeof cnt);
  int n, m, k;
  cin >> n >> m >> k;
  
  vector<int> d;
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    d.push_back(a[i]);
  }

  sort(d.begin(), d.end());
  map<int, int> f, g;
  int id = 0;
  for(int i = 0; i < d.size(); i++) {
    int j = i;
    while(j < d.size() && d[i] == d[j]) {
      j++;
    }
    f[d[i]] = id;
    g[id] = d[i];
    id++;
    i = j - 1;
  }

  int m1, m2;
  cin >> m1;
  for(int i = 0; i < m1; i++) {
    scanf("%d", &b[i]);
    cnt[b[i]]++;
  }
  cin >> m2;
  for(int i = 0; i < m2; i++) {
    scanf("%d", &c[i]);
    cnt[c[i]]++;
  }

  for(int i = 1; i <= n; i++) {
    if(cnt[i] == 0) {
      v1.push_back(a[i]);
    } else if(cnt[i] == 1) {

    } else if(cnt[i] == 2) {
      v4.push_back(a[i]);
    }
  }

  for(int i = 0; i < m1; i++) {
    if(cnt[b[i]] == 1) {
      v2.push_back(a[b[i]]);
    }
  }

  for(int i = 0; i < m2; i++) {
    if(cnt[c[i]] == 1) {
      v3.push_back(a[c[i]]);
    }
  }
  
  tree[0] = {0, id + 1, 0};
  build(0);

  sort(v1.begin(), v1.end());
  sort(v2.begin(), v2.end());
  sort(v3.begin(), v3.end());
  sort(v4.begin(), v4.end());
  vector<int> vv2(v2.begin(), v2.end());
  vector<int> vv3(v3.begin(), v3.end());

  for(int i = 0; i < v2.size(); i++) {
    p1[i] = v2[i];
    if(i) p1[i] += p1[i - 1];
  }
  for(int i = 0; i < v3.size(); i++) {
    p2[i] = v3[i];
    if(i) p2[i] += p2[i - 1];
  }

  for(int i = 0; i < v1.size(); i++) {
    int ith = f[v1[i]];
    update(0, ith, v1[i], 1);
  }
  
  for(int i = 0; i < v4.size(); i++) {
      int ith = f[v4[i]];
      update(0, ith, v4[i], 1);
  }
  
  if(vv2.size() >= k && vv3.size() >= k) {
    ll x = get(p1, 0, k - 1) + get(p2, 0, k - 1);
    int more = m - k - k;
    if(more >= 0) {
      if(more == 0) res = min(res, x);
      else if(query1(0, 0, id) >= more) {
        int idx = dfs(0, more);
        ll c = query1(0, 0, idx);
        res = min(res, x + 0 + query(0, 0, idx) - (c - more) * g[idx]);
      }
    }
  }
 // cout << v1 << endl;
  //cout << v2 << endl;
  //cout << v3 << endl;
  //cout << v4 << endl;

  ll sum = 0;
  for(int i = 0; i < min(k, (int)(v4.size())); i++) {
    int ith = f[v4[i]];
    update(0, ith, v4[i], -1); 
    
    sum += v4[i];
    int need = k - (i + 1);
    
    while(v2.size() > need) {
      int v = v2.back(); v2.pop_back();
      update(0, f[v], v, 1);
    }
    while(v3.size() > need) {
      int v = v3.back(); v3.pop_back();
      update(0, f[v], v, 1);
    }
    
    if(v2.size() >= need && v3.size() >= need) {
      ll x = get(p1, 0, need - 1) + get(p2, 0, need - 1);
      int more = m - (i + 1) - need * 2;
      if(more >= 0) {
        if(more == 0) res = min(res, x + sum);
        else if(query1(0, 0, id) >= more) {
          int idx = dfs(0, more);
          ll c = query1(0, 0, idx);
          res = min(res, x + sum + query(0, 0, idx) - (c - more) * g[idx]);
          //cout <<"gg " <<i << "  " << idx << "  " << c <<" " << more << endl;
          //cout << sum << " " << x << "  " <<  query(0, 0, idx) << endl;
        }
      }
    }
  }

  if(res == INF) cout << -1 << endl;
  else cout << res << endl;
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
