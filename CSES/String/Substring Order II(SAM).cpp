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
 

const int N = 2e5 + 10;
char s[N];
ll dp[N][26];
ll f[N], ff[N];
vector<int> g[N];
int last = 1, tot = 1;
struct Node
{
    int len, fa;
    int ch[26];
}node[N];

void extend(int c) {
  int p = last, np = last = ++ tot;
  f[tot] = 1;
  node[np].len = node[p].len + 1;
  for (; p && !node[p].ch[c]; p = node[p].fa) node[p].ch[c] = np;
  if (!p) node[np].fa = 1;
  else {
    int q = node[p].ch[c];
    if (node[q].len == node[p].len + 1) node[np].fa = q;
    else {
      int nq = ++ tot;
      node[nq] = node[q], node[nq].len = node[p].len + 1;
      node[q].fa = node[np].fa = nq;
      for (; p && node[p].ch[c] == q; p = node[p].fa) node[p].ch[c] = nq;
    }
  }
}

void dfs1(int u) {
  for (int nxt : g[u]) {
    dfs1(nxt);
    f[u] += f[nxt];
  }
}


ll dfs(int u) {
  if(ff[u] != -1) return ff[u];
  ll sum = f[u];
  for(int i = 0; i < 26; i++) {
    if(node[u].ch[i] == 0) continue;
    dp[u][i] = dfs(node[u].ch[i]);
    sum += dp[u][i];
  }
  return ff[u] = sum;
}


void build(string& res, int u, ll k) {
  if(k <= 0) return;
  for(int i = 0; i < 26; i++) {
    if(node[u].ch[i] == 0) continue;
    int nxt = node[u].ch[i];
    if(k > dp[u][i] ) {
      k -= dp[u][i];
    } else {
      res += (char)(i + 'a');
      build(res, node[u].ch[i], k - f[nxt]);
      break;
    }
  }
} 

ll k;
void solve() {
  memset(ff, -1, sizeof ff);
    
  scanf("%s", s);
  scanf("%lld", &k);
  int n = strlen(s);
  for(int i = 0; i < n; i++) extend(s[i] - 'a');
  for(int i = 2; i <= tot; i++) g[node[i].fa].push_back(i);
  dfs1(1);
  dfs(1);
  string res = "";
  build(res, 1, k);
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
