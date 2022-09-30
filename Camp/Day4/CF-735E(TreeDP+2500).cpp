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

int n, k;
const int N = 110, mod = 1e9 + 7;
vector<int> g[N];
ll dp[N][50];

void dfs(int pa, int root) {
    dp[root][0] = 1;
    dp[root][k + 1] = 1;
    for(int nxt : g[root]) {
        if(nxt == pa) continue;
        dfs(root, nxt);
        ll f[101];
        memset(f, 0, sizeof f);
        for(int i = 0; i <= 2 * k; i++) {
            for(int j = 0; j <= 2 * k; j++) {
                if(i + j <= 2 * k) {
                    int mn = min(i, j + 1);
                    f[mn] += dp[root][i] * dp[nxt][j];
                    f[mn] %= mod;
                } else {
                    int mx = max(i, j + 1);
                    f[mx] += dp[root][i] * dp[nxt][j];
                    f[mx] %= mod;
                }
            }
        }
        for(int i = 0; i <= 2 * k; i++) dp[root][i] = f[i];
    }
}

void solve() {
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v); g[v].push_back(u);
    }
    
    memset(dp, 0, sizeof dp);
    dfs(0, 1);
    ll res = 0;
    for(int i = 0; i <= k; i++) {
        res += dp[1][i];
        res %= mod;
    }
    cout << res << endl;
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
