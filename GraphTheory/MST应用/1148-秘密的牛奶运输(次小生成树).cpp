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
typedef pair<double, double> PDD;


const int N = 550, M = 1e4 + 10, INF = 2e9;
vector<pair<int, int>> g[N];
bool st[M];
int p[N], d[N];
int f[N][12];
int dp1[N][12], dp2[N][10]; //维护最大值和严格次大值
ll sum = 0;
int n, m;

struct Edge
{
    int u, v, w;
    bool operator< (const Edge &t)const
    {
        return w < t.w;
    }
} e[M];

int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int LCA(int x,int y) {
  if(d[x] < d[y]){
    return LCA(y,x);
  }
  
  for(int i = 11; i>=0; i--) {
    if(f[x][i] != -1 && d[f[x][i]] >= d[y]) {
      x = f[x][i];
    }
  }

  if(x == y) return x;

  for(int i = 11; i >= 0; i--) {
    if(f[x][i] != f[y][i]) {                    
      x = f[x][i];
      y = f[y][i];
    }
  }
  return f[x][0];
}

void dfs(int pa, int root, int l) {
    d[root] = l;
    f[root][0] = pa;
    for(auto& p: g[root]) {
        int nxt = p.first, w = p.second;
        if(nxt != pa) {
            dp1[nxt][0] = w;
            //dp2[nxt][0] = w;
            dfs(root, nxt, l + 1);
        }
    }
}

int go(int u, int k) {
    int res = 0;
    for(int i = 11; i >= 0; i--) {
        if(k & (1 << i)) {
            res = max(res, dp1[u][i]);
            u = f[u][i];
        }
    }
    return res;
}

int go1(int u, int k) {
    int res = 0;
    for(int i = 11; i >= 0; i--) {
        if(k & (1 << i)) {
            res = max(res, dp2[u][i]);
            u = f[u][i];
        }
    }
    return res;
}

void solve() {
    memset(st, false, sizeof st);
    memset(f, -1, sizeof f);
    memset(dp1, -1, sizeof dp1);
    memset(dp2, -1, sizeof dp2);
    
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        e[i] = {u, v, w};
    }
    
    sort(e, e + m);
    for(int i = 0; i < N; i++) p[i] = i;
    
    for(int i = 0; i < m; i++) {
        int r1 = find(e[i].u), r2 = find(e[i].v);
        if(r1 != r2) { //minimum spanning tree
            sum += e[i].w;
            p[r1] = r2;
            g[e[i].u].pb({e[i].v, e[i].w});
            g[e[i].v].pb({e[i].u, e[i].w});
            st[i] = true;
        }
    }
    
    dfs(-1, 1, 0);
    
    for(int i = 1; i < 12; i++) {
        for(int j = 1; j <= n; j++) {
            if(f[j][i - 1] != -1) {
                f[j][i] = f[f[j][i - 1]][i - 1];
                dp1[j][i] = max(dp1[j][i - 1], dp1[f[j][i - 1]][i - 1]);
            }
        }
    }
    
    //维护次大  
    for(int i = 1; i < 12; i++) {
        for(int j = 1; j <= n; j++) {
            if(f[j][i - 1] != -1) {
                if(dp1[f[j][i - 1]][i - 1] < dp1[j][i - 1]) {
                    dp2[j][i] = max(dp2[j][i - 1], dp1[f[j][i - 1]][i - 1]);
                } else {
                    dp2[j][i] = max(dp1[j][i - 1], dp2[f[j][i - 1]][i - 1]);
                }
            }
        }
    }
    
    
    vector<ll> a;
    a.push_back(sum);
    
    for(int i = 0; i < m; i++) {
        if(st[i]) continue;
        int u = e[i].u, v = e[i].v, w = e[i].w;
        int lc = LCA(u, v);
        int s1 = go(u, d[u] - d[lc]);
        int s2 = go(v, d[v] - d[lc]);
        int s3 = go1(u, d[u] - d[lc]);
        int s4 = go1(v, d[v] - d[lc]);
        a.push_back(sum - max(s1, s2) + w);
        a.push_back(sum - max(s3, s4) + w);
    }
    
    sort(a.begin(), a.end());
    for(int i = 1; i < a.size(); i++) {
        if(a[i] != a[i - 1]) {
            cout << a[i] << endl;
            break;
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



