#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>


using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector
typedef pair<int, int> PII;

//virtual tree tutorial: https://cmwqf.github.io/2020/04/17/%E6%B5%85%E8%B0%88%E8%99%9A%E6%A0%91/
//oi wiki: https://oi-wiki.org/graph/virtual-tree/#%E4%BD%BF%E7%94%A8%E5%8D%95%E8%B0%83%E6%A0%88%E7%9A%84%E6%9E%84%E9%80%A0%E6%96%B9%E6%B3%95
int n, m;
const int N = 1e5 + 10, M = N * 2;
vector<int> g[N];
int dfn[N], stk[N];
int d[N], dp[N];
bool is[N];
bool bad = false;
int h[N], e[M], ne[M], idx, top;
int res = 0, id = 0;

vector<int> v;
vector<pair<int, int>> ed;

void add(int a, int b)  // 添加一条边a->b
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
    v.push_back(a);
    ed.push_back({a, b});
}
void reset() //clear the graph
{
    for(int& i : v) {
        h[i] = -1;
    }
    idx = 0;
    v.clear();
    
    for(auto& p: ed) {
        is[p.first] = is[p.second] = false;
        dp[p.first] = dp[p.second] = 0;
    }
    ed.clear();
}

bool comp(int x, int y) {
    return dfn[x] < dfn[y];
}

int f[N][20];
int LCA(int x,int y) {
  if(d[x] < d[y]){
    return LCA(y,x);
  }
  
  for(int i = 19; i>=0; i--) {
    if(f[x][i] != -1 && d[f[x][i]] >= d[y]) {
      x = f[x][i];
    }
  }

  if(x == y) return x;

  for(int i = 19; i >= 0; i--) {
    if(f[x][i] != f[y][i]) {                    
      x = f[x][i];
      y = f[y][i];
    }
  }
  return f[x][0];
}


void dfs(int pa, int root, int dep) {
    d[root] = dep;
    dfn[root] = id++;
    f[root][0] = pa;     
    for(int& nxt : g[root]) {
        if(nxt != pa) {
            dfs(root, nxt, dep + 1);
        }
    }
}

void dfs1(int root) {
    if(bad) {
        return;
    }

    if(is[root]) {
        dp[root] = 1;
    }

    int cnt = 0;

    for(int i = h[root]; ~i; i = ne[i]) {
        int nxt = e[i];
        if(is[nxt] && is[root] && f[nxt][0] == root) {
            bad = true;
            return;
        }
        dfs1(nxt);
        cnt += dp[nxt];
    }

    if(is[root]) {
        res += cnt;
    } else {
        if(cnt > 1) {
            res++;
        } else {
            dp[root] = cnt;
        }
    }
}

void solve() {
    scanf("%d", &n);
    memset(is, false, sizeof is);
    memset(dp, 0, sizeof dp);
    memset(h, -1, sizeof h);
    memset(f, -1, sizeof f);
    
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(-1, 1, 0);

    for(int i = 1; i < 20; i++) {
        for(int j = 1; j <= n; j++) {
            if(f[j][i - 1] != -1) {
                f[j][i] = f[f[j][i - 1]][i - 1];
            }
        }
    }
    
    scanf("%d", &m);
    for(int i = 0; i < m; i++ ) {
        int t;
        scanf("%d", &t);
        vector<int> a(t);
        reset();
        for(int j = 0; j < t; j++) {
            scanf("%d", &a[j]);
            is[a[j]] = true;
        }

        //construct virtual tree
        sort(a.begin(), a.end(), comp);
        stk[ top = 1 ] = 1;
        for(int j = 0; j < a.size(); j++) {
            int x = a[j];
            if(x == 1) continue;
            int l = LCA(x, stk[top]);
            
            //cout << "lca  " << x << " " << stk[top] << " " << l << endl;
            
            if(l != stk[top]) {
                while(dfn[l] < dfn[stk[top - 1] ]) {
                    add(stk[top - 1], stk[top]);
                    top --;
                }
                if(dfn[l] > dfn[stk[top - 1] ]) add(l, stk[top]), stk[top] = l;
                else add(l, stk[top]), top --;
            }
            stk[++ top] = x;
        }
        while(top > 1) {
            add(stk[top - 1], stk[top]);
            top--;
        }
        /////////////////////////////////////////////

        bad = false;
        res = 0;
        dfs1(1);

        if(bad) {
            printf("%d\n", -1);
        } else {
            printf("%d\n", res);
        }
    }
    
    
}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}



