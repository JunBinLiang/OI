
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

const int N = 3e5 + 10, INF = 1e9;
int n, m;
int a[N], roots[N], counts[N];

const int MAX = N * 2;
struct Node {
  int l, r;
  int lid, rid;
  int cnt = 0;
} tree[MAX * 16];


int idx = 0;
void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  int idx1 = idx;
  int idx2 = idx + 1;
  idx += 2;
  tree[id].lid = idx1;
  tree[id].rid = idx2;
  tree[idx1] = {l, mid, -1, -1, 0};
  tree[idx2] = {mid + 1, r,-1, -1, 0};
  build(idx1);
  build(idx2);
}

void update(int preId, int curId, int index, int val) {
  int l = tree[curId].l, r = tree[curId].r;
  if(l == r) {
    tree[curId].cnt = counts[l];
    return;
  }
  int mid = l + (r - l) / 2;
  if (index <= mid) {//update left
    tree[curId].rid = tree[preId].rid;
    tree[idx] = {tree[tree[preId].lid].l, tree[tree[preId].lid].r, -1, -1, 0};
    tree[curId].lid = idx;
    idx++;
    update(tree[preId].lid, tree[curId].lid, index, val);
  } else {//update right
    tree[curId].lid = tree[preId].lid;    
    tree[idx] = {tree[tree[preId].rid].l, tree[tree[preId].rid].r, -1, -1, 0};
    tree[curId].rid = idx;
    idx++;
    update(tree[preId].rid, tree[curId].rid, index, val);
  }
  tree[curId].cnt = tree[tree[curId].lid].cnt + tree[tree[curId].rid].cnt;
  //cout << "gg " << l<< " " << r <<" " << index << "   |" << tree[curId].cnt << endl;
}

int query(int preId, int curId, int v) {
  int l = tree[curId].l, r = tree[curId].r;
  if(l == r) {
    if(tree[curId].cnt - tree[preId].cnt >= v) {
      return l;
    }
    return INF;
  }

  int ans = INF;
  int c1 = tree[tree[curId].lid].cnt - tree[tree[preId].lid].cnt;
  int c2 = tree[tree[curId].rid].cnt - tree[tree[preId].rid].cnt;
  
  if(c1 >= v) {
    ans = min(ans, query(tree[preId].lid, tree[curId].lid, v));
  }
  if(c2 >= v) {
    ans = min(ans, query(tree[preId].rid, tree[curId].rid, v));
  }
  return ans;
  
}







void solve() {
  memset(counts, 0, sizeof counts);
  cin >> n >> m;

  roots[0] = 0;
  tree[0] = {0, n, -1, -1, 0};
  idx++;
  build(0);

  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    counts[a[i]]++;
    roots[i] = idx;
    tree[idx] = {0, n, -1, -1, 0};
    idx++;
    update(roots[i - 1], roots[i], a[i], 1);
  }

  for(int i = 0; i < m; i++) {
    int l, r, k;
    scanf("%d%d%d", &l, &r, &k);
    int v = (r - l + 1) / k + 1;
    int ans = query(roots[l - 1], roots[r], v);
    if(ans == INF) cout << -1 << endl;
    else cout << ans << endl;
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
