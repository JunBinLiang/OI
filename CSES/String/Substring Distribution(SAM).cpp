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
ll line[N];
vector<int> g[N];
int last = 1, tot = 1;
struct Node
{
    int len, fa;
    int ch[26];
}node[N];

void extend(int c) {
  int p = last, np = last = ++ tot;
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



void dfs(int u) {
  //res += (node[u].len - node[node[u].fa].len);
  line[node[node[u].fa].len + 1]++; 
  line[node[u].len + 1]--;
  for(int v : g[u]) {
    dfs(v);
  }
}

void solve() {
    memset(line, 0, sizeof line);

    scanf("%s", s);
    int n = strlen(s);
    for(int i = 0; i < n; i++) extend(s[i] - 'a');
    
    for (int i = 2; i <= tot; i ++ ) {
        g[node[i].fa].push_back(i);
    }
    dfs(1);

    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += line[i];
        printf("%lld ", sum);
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
