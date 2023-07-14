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
#include <fstream>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
#define JBFOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 


const int N = 3e5 + 10;
int n, m;
char s[N];
int p[N], in[N], ans[N], dis[N];
bool vis[N];
vector<int> g[N];

int find(int u) {
  return p[u] == u ? u : find(p[u]);
}

bool topo() {
  set<int> s;
  for(int i = 0; i < n; i++) {
    s.insert(find(i));
  }

  queue<int> q;
  for(int i = 0; i < n; i++) {
    if(s.find(i) != s.end() && in[i] == 0) {
      q.push(i);
      dis[i] = 0;
    }
  }
  
  int vcnt = 0, mx = 0;
  while(q.size()) {
    int u = q.front(); q.pop();
    vcnt++;
    for(int nxt : g[u]) {
      if(vis[nxt]) return false;
      in[nxt]--;
      dis[nxt] = max(dis[nxt], 1 + dis[u]);
      mx = max(mx, dis[nxt]);
      if(in[nxt] == 0) {
        vis[nxt] = true;
        q.push(nxt);
      }
    }
  }

  if(vcnt != s.size() || mx > m) {
    return false;
  }
  return true;
}

void solve() {
  memset(in, 0, sizeof in);
  memset(vis, 0, sizeof vis);
  memset(dis, 0, sizeof dis);

  cin >> n >> m;
  scanf("%s", s + 1);
  for(int i = 0; i < n; i++) p[i] = i;
  for(int i = 1; i <= n; i++) {
    int r1 = find(i), r2 = find(i - 1);
    if(s[i] == '=') {
      if(r1 != r2) p[r1] = r2; //union find
    }
  }

  for(int i = 1; i <= n; i++) {
    int r1 = find(i - 1), r2 = find(i);
    if(s[i] == '<') {
      g[r1].push_back(r2);
      in[r2]++;
    } else if(s[i] == '>') {
      g[r2].push_back(r1);
      in[r1]++;
    }
  }

  bool ok = topo();
  if(!ok) memset(ans, -1, sizeof ans);
  else {
    for(int i = 0; i < n; i++) {
        int r = find(i);
        ans[i] = dis[r];
    }
  }
  for(int i = 0; i < n; i++) printf("%d ", ans[i]);
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
