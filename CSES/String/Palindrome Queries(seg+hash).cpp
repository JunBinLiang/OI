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

void yes() {
  printf("YES\n");
}

void no() {
  printf("NO\n");
}

const int N = 2e5 + 10;
int base = 131;
ull p[N];
char s[N];
int n, m;


struct Node {
  int l, r;
  ull v;
} tr1[N * 4], tr2[N * 4];

void build(int id) {
  int l = tr1[id].l, r = tr1[id].r;
  if(l == r) {
    if(l == 0) return;
    tr1[id].v = tr2[id].v = (s[l] - 'a' + 1);
    return;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  tr1[left] = {l, mid, 0};
  tr1[right] = {mid + 1, r, 0};
  tr2[left] = {l, mid, 0};
  tr2[right] = {mid + 1, r, 0};
  build(id * 2 + 1);
  build(id * 2 + 2);
  int lsz = mid - l + 1;
  int rsz = r - (mid + 1) + 1;
  tr1[id].v = tr1[left].v * p[rsz] + tr1[right].v;
  tr2[id].v = tr2[right].v * p[lsz] + tr2[left].v;
}

void update(int id, int index) { 
  int l = tr1[id].l, r = tr1[id].r;
  if(l == r) {
    tr1[id].v = tr2[id].v = s[index] - 'a' + 1;
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(left, index);
  } else {
    update(right, index);
  }
  int lsz = mid - l + 1;
  int rsz = r - (mid + 1) + 1;
  tr1[id].v = tr1[left].v * p[rsz] + tr1[right].v;
  tr2[id].v = tr2[right].v * p[lsz] + tr2[left].v;
}

ull query(int id, int s, int e, int op) {
  int l = tr1[id].l, r = tr1[id].r;
  if(l == s && r == e){
    if(op == 0) return tr1[id].v;
    else return tr2[id].v;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(left, s, e, op);
  } else if(s >= mid + 1) {
      return query(right, s, e, op);
  } else {
    ull v1 = query(left, s, mid, op);
    ull v2 = query(right, mid + 1, e, op);
    int lsz = mid - s + 1;
    int rsz = e - (mid + 1) + 1;
    if(op == 0) { //forward
      return v1 * p[rsz] + v2;
    } else { //reverse
      return v2 * p[lsz] + v1;
    }
  }
}

void init() {
  p[0] = 1;
  for(int i = 1; i < N; i++) p[i] = p[i - 1] * base;
  tr1[0] = {0, n + 1, 0};
  tr2[0] = {0, n + 1, 0};
  build(0);
}

void solve() {
  scanf("%d%d", &n, &m);
  scanf("%s", s + 1);
  init();

  for(int i = 0; i < m; i++) {
    int op;
    scanf("%d", &op);
    if(op == 1) {
      int idx;
      char c[2];
      scanf("%d", &idx);
      scanf("%s", c);
      s[idx] = c[0];
      update(0, idx);
    } else {
      int l, r;
      scanf("%d%d", &l, &r);
      int sz = r - l + 1;
      if(sz % 2 == 0) {
        int k = sz / 2;
        ull x = query(0, l, l + k - 1, 0);
        ull y = query(0, l + k, r, 1);
        //cout << l << " " << l + k - 1 << endl;
        //cout << l + k << "  " << r << endl;
        //cout << x << "  |" << y << endl;
        if(x == y) yes();
        else no();
      } else {
        if(sz == 1) {
          yes();
        } else {
          int k = sz / 2;
          ull x = query(0, l, l + k - 1, 0);
          ull y = query(0, l + k + 1, r, 1);
          if(x == y) yes();
          else no();
        }
      }
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
