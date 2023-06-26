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
using ull = unsigned long long;
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


const int MAX = 5e5 + 100;
const int N = 5e5 + 10;
int a[N], maxs[N], cnts[N];
ll sums[N], accu[N];
int n, m;

struct Node {
  int l, r;
  int mx;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mx = a[l];
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, -1};
  tree[id * 2 + 2] = {mid + 1, r, -1};
  build(id * 2 + 1);
  build(id * 2 + 2);
  tree[id].mx = max(tree[id * 2 + 1].mx, tree[id * 2 + 2].mx);
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

void solve() {
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  tree[0] = {0, n, -1};
  build(0);

  memset(maxs, 0, sizeof maxs);
  memset(sums, 0, sizeof sums);
  memset(cnts, 0, sizeof cnts);

  scanf("%d", &m);
  for(int y = 0; y < m; y++) {
    int k;
    scanf("%d", &k);
    vector<int> v;
    while(k--) {
      int x;
      scanf("%d", &x);
      v.push_back(x);
    }

    ll res = 0;
    vector<int> stk;
    for(int i = 0; i < v.size(); i++) {
      int idx = v[i];
      if(stk.size() == 0) {
        stk.push_back(idx);
        cnts[idx] = 1;
        sums[idx] = a[idx];
        accu[idx] = a[idx];
        maxs[idx] = a[idx];
        res += accu[idx];
      } else {
        sums[idx] = a[idx];
        cnts[idx] = 1;
        int mx = query(0, stk.back() + 1, idx);
        while(stk.size() > 0) {
          int j = stk.back();
          int mmax = query(0, j + 1, idx);
          if(mmax >= maxs[j]) {
            cnts[idx] += cnts[j];
            sums[idx] += (cnts[j] + 0ll) * (mmax);
            stk.pop_back();
            mx = max(mx, mmax);
          } else {
            sums[idx] += max(mmax, a[j]) - a[j];
            break;
          }
        }
        
        accu[idx] = sums[idx];
        maxs[idx] = mx;
        if(stk.size()) {
            accu[idx] += accu[stk.back()];
        }
                res += accu[idx];
        stk.push_back(idx);
      }
    }
    printf("%lld\n", res);
    
    //reset informations
    for(int idx : v) {
      sums[idx] = accu[idx] = 0;
      cnts[idx] = maxs[idx] = 0;
    }
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

