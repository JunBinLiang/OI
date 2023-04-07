#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector


const int N = 5010, mod = 1e9 + 7;
int n, k;
int a[N], p[N];
vector<int> g[N];
int dp[N][N], C[N][N];
int mx[N];
int f[N];

void init() {
    C[0][0] = 1;
    for(int i = 1;i < N; i++) {
      C[i][0]=1;
      for(int j = 1;j <= i;j++) {
        C[i][j] = ( C[i-1][j] + C[i-1][j-1] ) % mod;
      }
    }
}

int dfs(int i, int len) {
    if(i > n) {
        if(len == 0) {
            return 1;
        } else {
            return 0;
        }
    }
    if(dp[i][len] != -1) {
        return dp[i][len];
    }
    int res = 0;
    res |= dfs(i + 1, len);
    int ith = p[i];
    auto& v = g[a[i]];
    if(ith + k <= v.size() && len > 0) {
        res |= dfs(v[ith + k - 1] + 1, len -1);
    }
    return dp[i][len] = res;
}

int dfs2(int i) {
    if(i > n || mx[i] == 0) {
        return 1;
    }
    
    if(f[i] != -1) {
        return f[i];
    }
    
    int res = 0;
    if(i + 1 <= n && mx[i + 1] == mx[i]) {
        res = dfs2(i + 1);
    }
    
    int cnt = 0;
    for(int j = i; j <= n; j++) {
        if(a[j] == a[i]) {
            cnt++;
            if(cnt >= k && mx[j + 1] + 1 == mx[i]) {
                ll ways = C[cnt - 2][k - 2];
                ll v = dfs2(j + 1);
                ll x = v * ways;
                x %= mod;
                res += x;
                res %= mod;   
            }
        }
    }
    
    return f[i] = res;
}

void solve() {
    scanf("%d%d", &n, &k);
    for(int i = 0; i <= n; i++) {
        g[i].clear();
    }
    
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        g[a[i]].push_back(i);
        p[i] = g[a[i]].size() - 1;
    }

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            dp[i][j] = -1;
        }
    }
    
    int best = 0;
    mx[n + 1] = 0;
    for(int i = 1; i <= n; i++) {
        mx[i] = 0;
        for(int le = 1; le <= n; le++) {
            int v = dfs(i, le);
            if(v) {
                mx[i] = max(mx[i], le);
                best = max(best, le);
            }
        }
    }
    
    if(best == 0 || k == 1) {
        cout << 1 << endl;
        return;
    }
    
    for(int i = 0; i <= n; i++) f[i] = -1;
    
    ll res = dfs2(1);
    cout << res << endl;
}

int main()
{   
  
    init();
    int t = 1;
    cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
