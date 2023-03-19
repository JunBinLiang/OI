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
#include <iostream>
   
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

//5 : 50
const int N = 20;
vector<int> g[N];
bool a[N][N];
int res[N];
bool dp[2][N][1 << N];
int p[N][1 << N];
int st[N];
int root = 0;

int n, m, tot;
bool dfs(int state, int u) {
    if(dp[1][u][state]) {
        return dp[0][u][state];
    }
    
    bool res = false;
    if(u != root && a[u][root]) { //can connect to the beginning
        int v = 0;
        for(int i = 0; i < n; i++) {
            if(state & (1 << i)) {
                v |= st[i];
            }
        }
        if(v == tot) {
            res = true;
            p[u][state] = root;
        }
    }

    for(int& nxt : g[u]) {
        if(state & (1 << nxt)) continue;
        bool b = dfs(state | (1 << nxt), nxt);
        if(b) {
            res = true;
            p[u][state] = nxt;
        }
    }
    dp[0][u][state] = res;
    dp[1][u][state] = true;
    return res;
}

void solve() {
    memset(a, false, sizeof a);
    memset(st, 0, sizeof st);

    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
        a[u][v] = a[v][u] = true;
        st[u] |= (1 << v);
        st[v] |= (1 << u);
    }

    tot = (1 << n) - 1;

    for(int i = 0; i < n; i++) {
        memset(dp[0], false, sizeof dp[0]);
        root = i;
        bool v = dfs(1 << i, i);
        if(v) {
            int u = i;
            int state = (1 << i);
            
            while(true) {
                int nxt = p[u][state];
                res[u] = nxt;
                if(nxt == root) {
                    break;
                }
                res[u] = nxt;
                state |= (1 << nxt);
                u = nxt;
            }

            for(int j = 0; j < n; j++) {
                if(state & (1 << j)) continue;
                for(int k = 0; k < n; k++) {
                    if(a[k][j] && (state & (1 << k))) {
                        res[j] = k;
                        break;
                    }
                }
            }

            cout << "YES" << endl;
            for(int j = 0; j < n; j++) {
                cout << res[j] + 1 << " ";
            }
            cout << endl;
            return;
        }
    }

    cout << "NO" << endl;
}

int main() {
    int t = 1;
    while(t--) {
        solve();    
    }
    return 0;
}
