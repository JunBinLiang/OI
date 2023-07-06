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
#define vec vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}


const int N = 2e5 + 10;
int n, m;
int a[N];

struct Node {
  int l, r;
  int tag = 0;
  int lv, rv;
  int llen,  rlen;
  ll sum;
} tr[N * 4];

void build(int id) {
  int l = tr[id].l, r = tr[id].r;
  if(l == r) {
    if(l == 0) return;
    tr[id].lv = tr[id].rv = a[l];
    tr[id].llen = tr[id].rlen = 1;
    tr[id].sum = 1;
    return;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  tr[left] = {l, mid, 0, 0, 0, 0, 0, 0};
  tr[right] = {mid + 1, r, 0, 0, 0, 0, 0, 0};
  build(left);
  build(right);

  tr[id].lv = tr[left].lv;
  tr[id].rv = tr[right].rv;
  
  tr[id].sum = tr[left].sum + tr[right].sum;
  if(tr[left].rv != tr[right].lv) {
    tr[id].sum += (tr[left].rlen + 0ll) * tr[right].llen;
  }

  tr[id].llen = tr[left].llen;
  if(tr[left].llen == (mid - l + 1) && tr[left].rv != tr[right].lv) {
    tr[id].llen = max(tr[id].llen, tr[left].llen + tr[right].llen);
  }
  
  tr[id].rlen = tr[right].rlen;
  if(tr[right].rlen == (r -(mid + 1) + 1) && tr[left].rv != tr[right].lv) {
    tr[id].rlen = max(tr[id].rlen, tr[right].rlen + tr[left].rlen);
  }
}

void update(int id, int s, int e, int val) { 
  int l = tr[id].l, r = tr[id].r;
  if(l == s && r == e) {
    tr[id].lv ^= 1;
    tr[id].rv ^= 1;
    tr[id].tag ^= 1;
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(tr[id].tag != 0) {
    update(left, tr[left].l, tr[left].r, tr[id].tag);
    update(right, tr[right].l, tr[right].r, tr[id].tag);
    tr[id].tag = 0;
  }

  if(e <= mid) {
    update(left, s, e, val);
  } else if(s >= mid + 1) {
    update(right, s, e, val);
  } else {
    update(left, s, mid, val);
    update(right, mid + 1, e, val);
  }

  tr[id].lv = tr[left].lv;
  tr[id].rv = tr[right].rv;
  
  tr[id].sum = tr[left].sum + tr[right].sum;
  if(tr[left].rv != tr[right].lv) {
    tr[id].sum += (tr[left].rlen + 0ll) * tr[right].llen;
  }

  tr[id].llen = tr[left].llen;
  if(tr[left].llen == (mid - l + 1) && tr[left].rv != tr[right].lv) {
    tr[id].llen = max(tr[id].llen, tr[left].llen + tr[right].llen);
  }
  
  tr[id].rlen = tr[right].rlen;
  if(tr[right].rlen == (r - (mid + 1) + 1) && tr[left].rv != tr[right].lv) {
    tr[id].rlen = max(tr[id].rlen, tr[right].rlen + tr[left].rlen);
  }
}

struct Info {
  int lv, rv, llen, rlen;
  ll sum;
};

Info query(int id, int s, int e) {
  int l = tr[id].l, r = tr[id].r;
  if(l == s && r == e){
    return {tr[id].lv, tr[id].rv, tr[id].llen, tr[id].rlen, tr[id].sum};
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(tr[id].tag != 0) {
    update(left, tr[left].l, tr[left].r, tr[id].tag);
    update(right, tr[right].l, tr[right].r, tr[id].tag);
    tr[id].tag = 0;
  }
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    auto p1 = query(left, s, mid);
    auto p2 = query(right, mid + 1, e);
    
    //cout << l << "  " << r << "  " << p1.sum << " " << p1.lv << " " << p1.rv << "  " << p1.llen << " " << p1.rlen << endl;
   // cout << l << "  " << r << "  " << p2.sum << " " << p2.lv << " " << p2.rv << "  " << p2.llen << " " << p2.rlen << endl;
   //cout << mid << " " << endl;
    
    Info ans = {};
    ans.lv = p1.lv;
    ans.rv = p2.rv;
    ans.sum = p1.sum + p2.sum;
    ans.llen = p1.llen;
    ans.rlen = p2.rlen;

    if(p1.llen == (mid - s + 1) && p1.rv != p2.lv) {
      ans.llen = max(ans.llen, p1.llen + p2.llen);
    }
    if(p2.llen == (e - (mid + 1) + 1) && p1.rv != p2.lv) {
      ans.rlen = max(ans.rlen, p2.rlen + p1.rlen);
    }
    if(p1.rv != p2.lv) {
      ans.sum += (p1.rlen + 0ll) * p2.llen;
    }
    return ans;
  }
}


void solve() {
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  tr[0] = {0, n, 0, 0, 0, 0, 0, 0};
  build(0);
  
  for(int i = 0; i < m; i++) {
    int op, L, R;
    scanf("%d%d%d", &op, &L, &R);
    if(op == 1) {
      update(0, L, R, 1);
    } else {
      auto ans = query(0, L, R);
      printf("%lld\n", ans.sum);
    }
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

