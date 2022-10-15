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
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int N = 1e4 + 100, INF = 1e9;
vector<int> g[N];
vector<int> v[N];
int a[N], cnt[N];
int bits[N];
bool p[N][(1 << 6) + 5];
bool visit[N];
int res = 0;
vector<int> all;
int n, m, k;

void init() {
    for(int i = 0; i < N; i++) {
        bits[i] = 0;
        for(int j = 0; j < 20; j++) {
            if(i & (1 << j)) bits[i] ++;
        }
    }
}


vector<int> bfs(int s) {
    vector<int> d(n + 1, INF);
    queue<int> q;
    d[s] = 0;
    q.push(s);
    p[s][0] = true;
    while(q.size()) {
        int root = q.front(); q.pop();
        for(int& nxt : g[root]) {
            if(d[root] + 1 < d[nxt]) {
                d[nxt] = 1 + d[root];
                q.push(nxt);
            }
            
            if(d[root] + 1 == d[nxt]) {
                int s = 0;
                if(v[nxt].size() > 0) {
                    for(int nxt : v[nxt]) s|= (1 << nxt);
                }
                for(int i = 0; i < (1 << 6); i++) {
                    if(p[root][i]) {
                        p[nxt][i | s] = true;
                        p[nxt][i] = true;
                    }
                }
            }
        }
    }
    return d;
}

void dfs1(vector<int>&d, int pa, int root) {
    if(cnt[root]) {
        vector<int> m;
        for(int i = 0; i < (1 << 6); i++) {
            if(p[root][i]) {
                m.push_back(i);
            }
        }
        int k = cnt[root];
        k = min(k, 6);
        bool dp[k + 1][(1 << 6) + 1];
        memset(dp, false, sizeof dp);
        for(int mask : m) {
            dp[0][0] = true;
            for(int t = 0; t < k; t++) {
                for(int i = 0; i < (1 << 6); i++) {
                    if(dp[t][i]) {
                        dp[t + 1][i] = true;
                        dp[t + 1][i | mask] = true;
                    }
                }
            }
        }
        bool se[N];
        memset(se, 0, sizeof se);
        for(int i = 0; i < (1 << 6); i++) {
            if(dp[k][i]) {
                for(int& x : all) {
                    int y = x | i;
                    res = max(res, bits[y]);
                    se[y] = true;
                }
            }
        }
        
        all.clear();
        for(int i = 0; i < N; i++) {
            if(se[i]) all.push_back(i);
        }
    }
    
    for(int& nxt : g[root]) {
        if(pa == nxt || d[nxt] != d[root] + 1) continue;
        if(!visit[nxt]) {
            visit[nxt] = true;
            dfs1(d, root, nxt);
        }
        
    }
}

void solve() {
    scanf("%d%d", &n, &m);
    res = 0;
    for(int i = 0; i <= n; i++) {
        cnt[i] = 0;
        visit[i] = false;
        g[i].clear();
        v[i].clear();
    }
    
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j < (1 << 6); j++) {
            p[i][j] = false;
        }
    }

    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    

    scanf("%d", &k);
    for(int i = 0; i < k; i++) {
        scanf("%d", &a[i]);
        cnt[a[i]] ++;
    }

    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        int idx;
        scanf("%d", &idx);
        idx--;
        int val = a[idx];
        cnt[val] --;
        v[val].push_back(i);
    } 

    vector<int> d = bfs(1);
    all.clear();
    all.push_back(0);
    dfs1(d, -1, 1);
    printf("%d\n", m - res);
} 

int main() {
    init();
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
