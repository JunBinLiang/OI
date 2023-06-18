
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


const int N = 5e4 + 10, M = 256;
vector<int> g[N];
int a[N], b[N], c[N], fa[N], h[N];
int to[N];
int blo[N][M];

int id = 1, root = 0, mx = 0;
int tr[17 * N][2];
int best[34 * N];

void clear(int u) {
  if(tr[u][0] != -1) {
    int nxt = tr[u][0];
    tr[u][0] = -1;
    clear(nxt);
  }

  if(tr[u][1] != -1) {
    int nxt = tr[u][1];
    tr[u][1] = -1;
    clear(nxt);
  }
}

void add(int idx, int fakeIdx, int x) {
  int u = root;
  for(int i = 15; i >= 0; i--) {
    if(x & (1 << i)) {
      if(tr[u][1] == -1) {
        tr[u][1] = id++;
      }
      u = tr[u][1];
    } else {
      if(tr[u][0] == -1) {
        tr[u][0] = id++;
      }
      u = tr[u][0];
    }
  }

  if((b[idx] ^ fakeIdx) > best[u]) {
    best[u] = b[idx] ^ fakeIdx;
  }
}

int find(int& x) {
  int u = root;
  int val = 0;
  for(int i = 15; i >= 0; i--) {
    if(x & (1 << i)) { // 1
      if(tr[u][0] != -1) {
        u = tr[u][0];
      } else {
        u = tr[u][1];
        val += (1 << i);
      }
    } else { // 0
      if(tr[u][1] != -1) {
        u = tr[u][1];
        val += (1 << i);
      } else {
        u = tr[u][0];
      }
    }
  }
  return (val ^ x) | best[u];
}

void dfs(int pa, int u, int dep) {
  fa[u] = pa;
  h[u] = dep;
  mx = max(mx, dep);
  for(int& nxt : g[u]) {
    if(nxt == pa) continue;
    dfs(u, nxt, dep + 1);
  }
}

string tobin(int x) {
    string s = "";
    for(int i = 20; i >= 0; i--) {
        if(x & (1 << i)) s += "1";
        else s += "0";
    }
    return s;
}

void solve() {
  memset(fa, 0, sizeof fa);
  memset(to, 0, sizeof to);
  memset(tr, -1, sizeof tr);
  memset(best, -1, sizeof best);

  int n, m;
  scanf("%d%d", &n, &m);
  int m1 = 255, m2 = (255 << 8);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    b[i] = m1 & a[i]; //first half
    c[i] = m2 & a[i]; //second half
  }

  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(0, 1, 0);

  for(int i = 1; i <= n; i++) {
    int u = i;
    int d = 0;
    while(u != 0 && d < M) {
      add(u, d, c[u]); //add the second half
      to[i] = u;
      d++;
      u = fa[u];
    }
    
    for(int k = 0; k < (mx - h[i]) / M + 1; k++) {
      int v = k * M;
      blo[i][k] = find(v);
    }

    //reset the trie
    for(int j = 0; j < id; j++) {
        best[j] = -1;
        tr[j][0] = tr[j][1] = -1;
    }
    id = 1;

  }

  for(int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    int d = h[v] - h[u];
    int res = 0;
    int node = v;
    int j = 0;
    
    while(true) {
      if(d >= M) {
        res = max(res, blo[node][j]);
        d -= M;
        node = to[node];
        node = fa[node];
      } else {
        for(int k = 0; k <= d; k++) {
          int x = (j * M + k) ^ a[node];
          res = max(res, x);
          node = fa[node];
        }
        break;
      }
      j++;
    }
    printf("%d\n", res);
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
