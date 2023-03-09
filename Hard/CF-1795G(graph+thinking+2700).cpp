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


const int N = 1e5 + 10;
int a[N], d[N];
bool is[N];
vector<int> g[N];

void solve() {
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    for(int i = 0; i < n; i++) {
        g[i].clear();
        is[i] = false;
        d[i] = 0;
    }

    for(int i = 0; i < m; i++ ){
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
        d[u]++; d[v]++;
    }

    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(a[i] == d[i]) {
            q.push(i);
        }
    }

    vector<pair<int, int>> ord;

    while(q.size() > 0) {
        int u = q.front(); q.pop();
        is[u] = true;
        for(int& nxt : g[u]) {
            if(!is[nxt]) {
                d[nxt]--;
                ord.push_back({u, nxt});
                if(d[nxt] == a[nxt]) {
                    q.push(nxt);
                }
            }
        }
    }


    reverse(ord.begin(), ord.end());
    ll res = (n + 0ll) * (n + 1) / 2;

    for(int l = 0; l < n; l += 62) {
        int r = min(n - 1, l + 61);
        vector<ll> dp(n);
        
        for(int i = l; i <= r; i++) {
            dp[i] = (1ll << (i - l));
        }

        for(pair<int, int>& p : ord) {
            int& u = p.first, v = p.second;

            if(u >= l && u <= r) {
                dp[u] |= (1ll << (u - l));
            }
            if(v >= l && v <= r) {
                dp[u] |= (1ll << (v - l));
            }
            dp[u] |= dp[v];
        }

        for(int i = 0; i < n; i++) {
            res -= (__builtin_popcountll(dp[i]));
        }
    }

    cout << res << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
