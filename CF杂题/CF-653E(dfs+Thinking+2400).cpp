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

void yes() {
  cout << "possible" << endl;
}
void no() {
  cout << "impossible" << endl;
}

int n, m, k;
const int N = 3e5 + 10;
set<int> g[N];
set<int> all;
bool seen[N];

void dfs(int root) {
  int id = 0;
  while(true) {
    auto it = all.lower_bound(id);
    if(it == all.end()) {
      break;
    } else {
      id = *it;
      if(g[root].find(id) == g[root].end()) {
        all.erase(id);
        seen[id] = true;
        dfs(id);
      }
    }
    id++;
  }
}

void solve() { 
  scanf("%d%d%d", &n, &m, &k);
  int cnt = 0;
  for(int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].insert(v);
    g[v].insert(u);
    if(u == 1 || v == 1) {
      cnt++;
    }
  }
  if(n - 1 - cnt < k) {
    no();
    return;
  }

  memset(seen, false, sizeof(seen));
  seen[1] = true;
  for(int i = 2; i <= n; i++) {
    all.insert(i);
  }

  
  for(int i = 2; i <= n; i++) {
    if(g[i].size() == n - 2 && g[i].find(1) == g[i].end()) {
      all.erase(i);
      seen[i] = true;
      k--;
    }
  }

  int com = 0;

  for(int i = 2; i <= n; i++) {
    if(!seen[i] && g[i].find(1) == g[i].end()) {
      com++;
      seen[i] = true;
      all.erase(i);
      dfs(i);
    }
  }

  if(com <= k && all.size() == 0) {
    yes();
  } else {
    no();
  }
  

}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
}
  
