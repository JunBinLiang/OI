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


int n, m;
const int N = 1e6 + 10;
const int INF = 1e9;
int op, x;
int res = 0;
ve<int> g[N];
int mins[N];
void dfs(int pa, int root, int mn) {
  mins[root] = min(root, mn);
  for(int& nxt : g[root]) {
    if(nxt == pa) continue;
    dfs(root, nxt, mins[root]);
  }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n - 1; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      g[u].pb(v);
      g[v].pb(u);
    }
    
    scanf("%d%d", &op, &x);
    x = x % n + 1;
    dfs(-1, x, INF);
    int k = x;
    for(int i = 0; i < m - 1; i++) {
      scanf("%d%d", &op, &x);
      x = (x + res) % n + 1;
      if(op == 1) {
        k = min(k, mins[x]);
      } else {
        res = min(k, mins[x]);
        printf("%d\n", res);
      }
    }
    return 0;
}   
