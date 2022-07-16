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

int find(ve<int>& nums, int x){
  if(nums[x] == x) return x;
  int root = find(nums, nums[x]);
  nums[x] = root;
  return root;
}

void merge(ve<int>& nums, int r1, int r2) {
  if(r1 != r2) nums[r1] = r2;
}

struct Edge {
  int u, v;
  ll w;
  ll c;
};

bool COMP(Edge& e1, Edge& e2) {
  if(e1.c == e2.c) {
      return e1.w > e2.w;
  }
  return e1.c < e2.c;
}


void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  ve<Edge> edges(m);
  for(int i = 0; i < m; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    edges[i] = {u - 1, v - 1, w, w};
  }

  ll p, h, a, b, c, x;
  scanf("%lld%lld%lld%lld%lld", &p, &h, &a, &b, &c);
  ve<int> query((int)(h));
  for(int i = 0; i < h; i++) {
    if(i >= p) {
      x = (x * a + b) % c;
    } else {
      scanf("%lld", &x);
    }
    int y = x;
    query[i] = y;
  }


  ll res = 0;
  sort(query.begin(), query.end());
  ve<int> changes;
  for(int i = 0; i < m; i++) {
    for(int j = i; j < m; j++) {
      int p1 = (edges[j].w + edges[i].w + 1) / 2 ;
      int p2 = (edges[j].w + edges[i].w - 1) / 2 ;
      changes.pb(p1); changes.pb(p2);
    }
  }
  for(Edge& e : edges) changes.pb(e.w);
  changes.pb(1000000000);changes.pb(0);
  sort(changes.begin(), changes.end());
  
  ve<int> ch;
  for(int i = 0; i < changes.size(); i++) {
      int j = i;
      W(j < changes.size() && changes[j] == changes[i])j++;
      ch.pb(changes[i]);
      i = j - 1;
  }
  changes = ch;
  
  int k = 0;
  
  for(int i = 0; i < changes.size() - 1; i++) {
    ve<int> nums(n);
    for(int j = 0; j < n; j++) {
      nums[j] = j;
    }
    
    for(Edge& e : edges) {
      e.c = abs(e.w - changes[i]);
    }
    sort(edges.begin(), edges.end(), COMP);
    
    ll sum = 0;
    ve<int> We;
    for(Edge& e : edges) {
      int r1 = find(nums, e.u);
      int r2 = find(nums, e.v);
      if(r1 != r2) {
        merge(nums, r1, r2);
        We.pb(e.w);
      }
    }
    
    W(k < (int)(query.size()) && (query[k] >= changes[i]) && (query[k] < changes[i + 1])) {
      ll x = query[k];
      ll cost = 0;
      for(int y : We) cost += abs(y - x);
      res ^= cost;
      k++;
    }
  }

  cout << res << endl;
}

int main() {
  int t = 1;
  while(t--) {
    solve();
  }
}
