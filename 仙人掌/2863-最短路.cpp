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


const int N = 20000, M = N * 3;
int h1[N], h2[N], e[M], w[M], ne[M], idx;
int dfn[N], low[N], cnt;
int fa[N][14], depth[N], d[N];
int fu[N], fe[N], fw[N];
int n, m, q;
int new_n;
int prefix[N], sums[N];
int X, Y;


void add(int h[], int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void build(int x, int y, int z) {
  int sum = z;
  for(int k = y; k != x; k = fu[k]) {
    prefix[k] = sum;
    sum += fw[k];
  }
  prefix[x] = sums[x] = sum;
  new_n++;
  add(h2, x, new_n, 0);
  for(int k = y; k != x; k = fu[k]) {
    sums[k] = sum;
    add(h2, new_n, k, min(prefix[k], sum - prefix[k]));
  }

}

void tarjan(int u, int from)
{
    dfn[u] = low[u] = ++ cnt;
    for (int i = h1[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            fu[j] = u, fw[j] = w[i], fe[j] = i;  // fe[j]存储j由哪条边下来，这样可以处理重边问题。
            tarjan(j, i);
            low[u] = min(low[u], low[j]);
            if (dfn[u] < low[j]) add(h2, u, j, w[i]); //bridge
        }
        else if (i != (from ^ 1)) {
          low[u] = min(low[u], dfn[j]);
        }
    }
    
    for (int i = h1[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (dfn[u] < dfn[j] && fe[j] != i) {
              build(u, j, w[i]);
        }
    }
}

int LCA(int x,int y) {
  if(depth[x] < depth[y]){
    swap(x, y);
  }

  for(int i = 13; i>=0; i--) {
    if(fa[x][i] != 0 && depth[fa[x][i]] >= depth[y]) {
      x = fa[x][i];
    }
  }
  if(x == y) return x;
  
  for(int i= 13; i>=0; i--) {
    if(fa[x][i] != fa[y][i]) {                    
      x = fa[x][i];
      y = fa[y][i];
    }
  }
  X = x, Y = y;
  return fa[x][0];
}


void init() {
  for(int i = 1; i < 14; i++){//construc sparse table
    for(int j = 0; j < N; j++){
      int parent = fa[j][i-1];
      if(parent == -1) continue;
      fa[j][i] = fa[parent][i-1];
    }
  }
}

void dfs_lca(int u, int father)
{
    depth[u] = depth[father] + 1;
    fa[u][0] = father;
    /*for (int k = 1; k <= 13; k ++ )
        fa[u][k] = fa[fa[u][k - 1]][k - 1];*/
    for (int i = h2[u]; ~i; i = ne[i])
    {
        int j = e[i];
        d[j] = d[u] + w[i];
        dfs_lca(j, u);
    }
}


void solve() {
  scanf("%d%d%d", &n, &m, &q);
  new_n = n;
  idx = 0;
  memset(h1, -1, sizeof h1);
  memset(h2, -1, sizeof h2);
  memset(fa, -1, sizeof(fa));
  for(int i = 0; i < m; i++) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    add(h1, a, b, c), add(h1, b, a, c);
  }

  cnt = 0;
  tarjan(1, -1);
  dfs_lca(1, 0);
  init();

  W(q--) {
    int a, b;
    scanf("%d%d", &a, &b);
    int p = LCA(a, b);
    if (p <= n) {
      printf("%d\n", d[a] + d[b] - d[p] * 2); 
    }
    else {
      int da = d[a] - d[X], db = d[b] - d[Y];
      int l = abs(prefix[X] - prefix[Y]);
      int res = da + db + min(l, sums[X] - l);
      printf("%d\n", res);
    }
  }
}



int main()
{
  int t = 1;
  //cin >> t;
  while (t--)
  {
    solve();
  }
  return 0;
}
