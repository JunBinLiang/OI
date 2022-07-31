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
ostream &operator<<(ostream &out, const vector<T> &a)
{
  out << "[";
  bool first = true;
  for (auto v : a)
  {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}

const int N = 100010, M = 2000010;
int n, m, mod;
int h[N], hs[N], e[M], ne[M], idx;
int h1[N];
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, scc_size[N];

int in[N], dis[N];
set<int> g[N];
int dp[N];

void add(int h[], int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ timestamp;
    stk[ ++ top] = u, in_stk[u] = true;

    for (int i = h[u]; ~i; i = ne[i])
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
            scc_size[scc_cnt] ++ ;
        } while (y != u);
    }
}

int dfs(int u) {
    if(dp[u] != -1) return dp[u];
    dp[u] = 0;
    for(auto nxt : g[u]) {
        dp[u] += dfs(nxt); dp[u] %= mod;
    }
    if(dp[u] == 0) dp[u] = 1;
    return dp[u];
}


int main() {
    
    scanf("%d%d%d", &n, &m, &mod);
    memset(h, -1, sizeof h);
    memset(h1, -1, sizeof h1);
    memset(dp, -1, sizeof dp);
    memset(in, 0, sizeof in);
    
    for(int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(h, a, b);
    }
    
    for(int i = 1; i <= n; i++) {
        if(!dfn[i]) tarjan(i);
    }
    
    for(int i = 1; i <= n; i++) {
        for(int j = h[i]; j != -1; j = ne[j]) {
            int id1 = id[i], id2 = id[e[j]];
            if(id1 != id2) {
               in[id2]++; 
               add(h1, id1, id2);
            }
        }
    }
    
    queue<int> q;
    int sum = 0, res = 0;
    for(int i = 1; i <= scc_cnt; i++) {
        if(!in[i]) {
            q.push(i);
            dis[i] = scc_size[i];
            sum = max(sum, dis[i]);
        }
    }
    
    
    while(q.size() > 0) {
        int top = q.front(); q.pop();
        for(int j = h1[top]; j != -1; j = ne[j]) {
            int nxt = e[j];
            in[nxt]--;
            if(!in[nxt]) {
                q.push(nxt);
            }
            
            int x = dis[top] + scc_size[nxt];
            if(x >= dis[nxt]) {
                if(x == dis[nxt]) {
                    
                } else {
                    dis[nxt] = x;
                    g[nxt].clear();
                }
                g[nxt].insert(top);
            }
            sum = max(sum, dis[nxt]);
        }
    }
    

    for(int i = 1; i <= scc_cnt; i++) {
        if(dis[i] == sum) {
            res += dfs(i);
            res %= mod;
        }
    }
    
    cout << sum << endl;
    cout << res << endl;
    
    return 0;
}
