  


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

bool res = true;
const int N = 200000 + 10;

bool is[N];
pair<int, int> a[N];
map<int, ve<int>> g;
bool fil[2][N];

void dfs(int s, int idx) {
  if(!res) return;
  is[idx] = true;
  pair<int, int>& p = a[idx];
  if(fil[s][p.first]) {
    res = false;
  }
  fil[s][p.first] = true;
  if(fil[s][p.second]) {
    res = false;
  }
  fil[s][p.second] = true;

  for(int i : g[p.first]) {
    if(!is[i]) {
      dfs((s + 1) % 2, i);
    }
  }
  for(int i : g[p.second]) {
    if(!is[i]) {
      dfs((s + 1) % 2, i);
    }
  }
}

void solve() {
  int n;
  scanf("%d", &n);
  unordered_map<int, int> f;
  g.clear();
  res = true;
  for(int i = 0; i < n; i++) {
    scanf("%d%d", &a[i].first, &a[i].second);
    is[i] = false;
    f[a[i].first]++;
    if(f[a[i].first] > 2) {
      res = false;
    }
    f[a[i].second]++;
    if(f[a[i].second] > 2) {
      res = false;
    }
    g[a[i].first].pb(i);
    g[a[i].second].pb(i);
  }

  for(int i = 0; i <= n; i++) {
    fil[0][i] = fil[1][i] = false;
  }

  for(int i = 0; i < n; i++) {
    if(is[i]) continue;
    dfs(0, i);
  }

  if(res) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }
}

int main() {
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
}
