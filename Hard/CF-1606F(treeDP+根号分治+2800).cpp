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


const int N = 2e5 + 5, M = 453;
vector<int> g[N];
vector<pair<int, int>> ask[N];
pair<int, int> q[N];
int res[N], sums[M], sz[N];
int dp[M][N];
int pre[M];
int n, m;

void dfs1(int pa, int root) { //remove k vertex
    sz[root] = 1;

    for(int& nxt : g[root]) {
        if(nxt == pa) continue;
        dfs1(root, nxt);

        for(int i = 0; i < M; i++) {
            pre[i] = dp[i][root];
        }

        for(int i = 0; i < M && i <= sz[nxt]; i++) {
            pre[i] = max(pre[i], dp[i][nxt]);
        }
            
        //There are up to M tree with size M 
        for(int i = 0; i < M && i <= sz[root]; i++) {
            for(int j = 0; j < M && j <= sz[nxt] && i + j < M; j++) {
                if(dp[i][root] != -1 && dp[j][nxt] != -1) {
                    pre[i + j] = max(pre[i + j], dp[i][root] + dp[j][nxt]);
                }
                
            }
        }
        for(int i = 0; i < M; i++) {
            dp[i][root] = pre[i];
        }
        sz[root] += sz[nxt];
    }

    for(auto& it : ask[root]) {
        int idx = it.first, k = it.second;
        for(int c = 0; c < M; c++) {
            if(dp[c][root] != -1) {
                res[idx] = max(res[idx], dp[c][root] - c * k);
            }
        }
    }

    for(int i = M - 1; i >= 1; i--) {
        dp[i][root] = dp[i - 1][root];
    }
    dp[0][root] = 1;
}

void dfs2(int pa, int root) { //cut 1 vertex, cost is k
    for(int& nxt : g[root]) {
        if(nxt == pa) continue;
        dfs2(root, nxt);
    }
    
    memset(sums, 0, sizeof sums);
    for(int& nxt : g[root]) {
        if(nxt == pa) continue;
        for(int k = 0; k < M; k++) {
            sums[k] += dp[k][nxt];
        }
    }

    for(auto& p : ask[root]) {
        int idx = p.first;
        res[idx] = max(res[idx], sums[p.second]);
    }

    for(int k = 0; k < M; k++) {
        dp[k][root] = max(1, sums[k] - k);
    }
}


void solve() {
    memset(res, 0, sizeof res);
    memset(dp, -1, sizeof dp);

    scanf("%d", &n);
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        int u, k;
        scanf("%d%d", &u, &k);
        q[i] = {u, k};
        if(k >= M) {
            ask[u].push_back({i, k});
        }
    }
 
    dfs1(-1, 1);

    for(int i = 0; i <= n; i++) {
        ask[i].clear();
    }

    for(int i = 0; i < m; i++) {
        if(q[i].second < M) {
            ask[q[i].first].push_back({i, q[i].second});
        }
    }

    dfs2(-1, 1);
    for(int i = 0; i < m; i++) {
        printf("%d\n", res[i]);
    }

}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
