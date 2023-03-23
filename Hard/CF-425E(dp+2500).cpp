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
   
using ll = long long;
using namespace std;  

const int mod = 1e9 + 7, N = 505;
int n, k;
ll dp[N][N];
int p[N * N];
void solve() {
    cin >> n >> k;
    p[0] = 1;
    for(int i = 1; i < N * N; i++) p[i] = (p[i - 1] * 2) % mod;

    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= k; j++) {
            for(int pre = i - 1; pre >= 0; pre--) {
                int cnt = i - pre;
                ll x = (dp[pre][j - 1] * (p[cnt] - 1));
                x %= mod;
                x *= p[(n - i) * cnt];
                x %= mod;
                dp[i][j] += x;
                dp[i][j] %= mod;
            }
        }
    }

    if(k == 0) {
        cout << 1 << endl;
        return;
    }

    ll res = 0;
    for(int i = 1; i <= n; i++) {
        res += dp[i][k];
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
