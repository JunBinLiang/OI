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

const int N = 1e5 + 10;
int n, k;
vector<int> g[N];
vector<int> res;
bool vis[N][105], dup[N];

void dfs(priority_queue<int, vector<int>, greater<int>>& pq, int u, int h) {
  if(h > k) {
    return;
  }
  if(vis[u][h]) return;
  
  vis[u][h] = true;
  if(!dup[u]) {
      dup[u] = true;
      pq.push(u);
  }
    
  
  for(int& nxt : g[u]) {
    dfs(pq, nxt, h + 1);
  }
}

void solve() {
  cin >> n >> k;
  FOR(i, 0, n - 1) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }

  memset(vis, false, sizeof vis);
  priority_queue<int, vector<int>, greater<int>> pq;
  
  memset(dup, 0, sizeof dup);
  dfs(pq, 1, 0);
  
  while(pq.size() > 0) {
    int u = pq.top(); pq.pop();
    res.push_back(u);
    dfs(pq, u, 0);
    
  }
  
  for(int& i : res) {
    printf("%d ", i);
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

