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


namespace Fenwick {
  const int SIZE = 200000 + 100;
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
      i -= ( i & -i);
    }
    return sum;
  }
  ll query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
}

struct Edge {
  int v, w1, w2;  
};

const int N = 2e5 + 10;
ve<Edge> g[N];
int ans[N];

void dfs(int pa, int u, ll sum, int cnt) {
    if(u != 1) {
        int l = 0, r = cnt - 1;
        ans[u] = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            ll t = Fenwick::query(0, mid);
            if(t <= sum) {
                ans[u] = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }
    
    for(Edge& e : g[u]) {
        if(e.v == pa) continue;
        Fenwick :: update(cnt, e.w2);
        dfs(u, e.v, sum + e.w1, cnt + 1);
        Fenwick :: update(cnt, -e.w2);
    }
}

void solve() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i <= n; i++) {
        g[i].clear();
        ll old = Fenwick :: query(i, i);
        Fenwick :: update(i, (int)(-old));
    }
    
    for(int i = 2; i <= n; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        g[i].pb({a, b, c});
        g[a].pb({i, b, c});
    }
    
    dfs(-1, 1, 0, 0);
    for(int i = 2; i <= n; i++) {
        printf("%d ", ans[i] + 1);
    }
    printf("\n");
}

int main() {
    Fenwick :: init();
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
}

