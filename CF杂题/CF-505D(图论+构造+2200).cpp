
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

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector
#define PII pair<long long, int>


template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}



int n, m;
const int N = 2e5 + 10, M = 2e5 + 10;
int h[N], e[M], ne[M], idx;

int dfn[N], low[N], timestamp = 0;
int stk[N], top;
bool in_stk[N];

int id[N], scc_cnt, Size[N];

vector<int> g[N];
bool vis[N];
bool cyc = false;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ timestamp;
    stk[ ++ top] = u, in_stk[u] = true;
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        else if (in_stk[j]) low[u] = min(low[u], dfn[j]);
    }

    if (dfn[u] == low[u])
    {
        ++ scc_cnt;
        int y;
        do {
            y = stk[top -- ];
            in_stk[y] = false;
            id[y] = scc_cnt;
            Size[scc_cnt] ++ ;
        } while (y != u);
    }
}

int dfs(int u) {
    int res = Size[u];
    vis[u] = true;
    if(Size[u] > 1) {
        cyc = true;
    }
    for(int nxt : g[u]) {
        if(vis[nxt]) continue;
        res += dfs(nxt);
    }
    return res;
}

void solve() {
    memset(h, -1, sizeof h);
    memset(dfn, 0, sizeof dfn);
    
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
    }
    
    for(int i = 1; i <= n; i++) {
        if(!dfn[i]) {
            tarjan(i);
        }
    }
    
    int res = 0;
    
    /*cout << res << endl;
    for(int i = 1; i <= n; i++) {
        cout << id[i] << " "; 
    } cout << endl;*/
    
    memset(vis, 0, sizeof vis);
    for(int u = 1; u <= n; u++) {
        for(int i = h[u]; i != -1; i = ne[i]) {
            int v = e[i];
            if(id[u] != id[v]) {
                int v1 = id[u], v2 = id[v];
                g[v1].push_back(v2);
                g[v2].push_back(v1);
            }
        }
    }
    
    
    for(int i = 1; i <= scc_cnt; i++) {
        if(!vis[i]) {
            cyc = false;
            int v = dfs(i);
            if(cyc) res += v;
            else res += (v - 1);
        }
    }
    
    cout << res << endl;
}   


int main()
{   
    int t = 1;
    //cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}

