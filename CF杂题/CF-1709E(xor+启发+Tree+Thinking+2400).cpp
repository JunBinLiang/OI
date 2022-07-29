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


const int N = 2e5 + 10;
int a[N];
ve<int> graph[N];
set<int> s[N];
int res = 0;

void dfs(int pa, int u, int h) {
  s[u].insert(h);
  bool flag = false;
  for(int &nxt : graph[u]) {
    if(nxt == pa) continue;
    dfs(u, nxt, h ^ a[nxt]);
    if(s[nxt].size() > s[u].size()) {
      swap(s[nxt], s[u]);
    }

    for(auto x : s[nxt]) {
      int p = x ^ a[u];
      if(s[u].find(p) != s[u].end()) flag = true; 
    }

    for(auto x : s[nxt]) {
      s[u].insert(x);
    }

  }

  if(flag) {
    res++;
    s[u].clear();
  }
}

void solve() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }

    for(int i = 0; i < n - 1; i ++) {
      int u, v;
      scanf("%d%d", &u, &v);
      u--; v--;
      graph[u].pb(v); graph[v].pb(u);
    }

    dfs(-1, 0, a[0]);
    printf("%d \n", res);
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
}
