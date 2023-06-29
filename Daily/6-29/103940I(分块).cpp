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

namespace Fenwick {
  const int SIZE = 100000 + 100;
  int tree[SIZE];
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

  int pre(int i) {
    int sum = 0;
    while(i>0){
      sum += tree[i];
      i -= ( i & -i);
    }
    return sum;
  }
  int query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
}


const int N = 1e5 + 10;
const int BLOCK = 180;
vector<int> g[N];
int f[557][N];
int a[N], ids[N], cnt[N], bigId[N];
bool isBig[N];
vector<int> big;
int n, m, k;
ll res = 0;  

void update(int id1, int id2) {
  if(g[id1].size() == 0 || g[id2].size() == 0) {
    return; //nothing to do
  }

  ll tot = (g[id1].size() + 0ll) * (g[id2].size());
  if(isBig[id1]) {
    ll x = f[bigId[id1]][id2];
    res -= (tot - x);
    res += x;
    return;
  }

  if(isBig[id2]) {
    ll x = f[bigId[id2]][id1];
    res -= x;
    res += (tot - x);
    return;
  }

  auto& v1 = g[id1], v2 = g[id2];
  int i = 0, j = 0;
  while(i < v1.size() && j < v2.size()) {
    if(v1[i] < v2[j]) {
      res += (v2.size() - j);
      i++;
    } else {
      res -= (v1.size() - i);
      j++;
    }
  }
}

void solve() {
  memset(isBig, false, sizeof isBig);
  memset(cnt, 0, sizeof cnt);
  memset(f, 0, sizeof f);
  Fenwick :: init();

  scanf("%d%d%d", &n, &k, &m);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    g[a[i]].push_back(i);
    res += Fenwick :: query(a[i] + 1, k + 1);
    Fenwick :: update(a[i], 1);
  }
  

  for(int i = 0; i <= k; i++) {
    ids[i] = i;
    if(g[i].size() >= BLOCK) {
      isBig[i] = true;
      bigId[i] = big.size();
      big.push_back(i);
    }
  }

  for(int i = 0; i < n; i++) {
    int v = a[i];
    for(int& b : big) {
      /*if(b > v) { //b -> v inversion pairs
        f[b][v] += cnt[b];
      } else if(b < v) { //v -> b inversion pairs
        f[b][v] += (g[b].size() - cnt[b]);
      }*/

      f[bigId[b]][v] += cnt[b]; // b -> v inversion pairs
    }
    cnt[v]++;
  }

  while(m--) {
    int x;
    scanf("%d", &x);
    update(ids[x], ids[x + 1]);
    swap(ids[x], ids[x + 1]);
    printf("%lld\n", res);
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
