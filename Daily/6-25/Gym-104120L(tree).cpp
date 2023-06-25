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



const int N = 1e6 + 10;
vector<int> g[N];
int sz[N];
int p[N];
void dfs(int pa, int u) {
    p[u] = pa;
    sz[u] = 1;
    for(int v : g[u]) {
      if(v != pa) {
        dfs(u, v);
        sz[u] += sz[v];
      }
    }
}

void solve() {
  memset(p, -1, sizeof p);

  int n, X;
  cin >> n >> X;
  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);  
    g[v].push_back(u);
  }

  dfs(-1, 1);
  
  int res = 2 * (n - 1);
  res -= ((sz[X] - 1) * 2);
  
  if(p[X] != -1) {
    for(int nxt : g[p[X]]) {
      if(nxt != X && nxt != p[p[X]]) {
        res -= (sz[nxt] * 2);
      }
    }
  }
  
  while(p[X] != -1) {
    res--;
    X = p[X];
  }

  cout << res << endl;


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

//1 -> 2 - > 3 -> 4 - > 5
