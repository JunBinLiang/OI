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


const int N = 1e5 + 10, mod = 1e9 + 7;
int n, m, k;
int b[20];
ll dp[N][15][16];

int shift(int v) {
    //0110 => 1100
    return (v << 1) & ((1 << m) - 1); 
}

void solve() {
    cin >> n >> k >> m;

    for(int i = 0; i < 20; i++) {
        b[i] = 0;
        for(int j = 0; j < 5; j++) {
            if(i & (1 << j)) b[i]++;
        }
    }

    memset(dp, 0, sizeof dp);
    dp[0][0][0] = 1;
    for(int i = 1; i <= n; i++) {
        dp[i][0][0] = 1;
        for(int j = 1; j <= k; j++) {
            for(int st = 0; st < (1 << m); st++) {
                int bcnt = b[st];
                //not take
                int s = shift(st);
                dp[i][j][s] += dp[i - 1][j][st];
                dp[i][j][s] %= mod;
                //take
                dp[i][j][s + 1] += (dp[i - 1][j - 1][st] * (bcnt + 1));
                dp[i][j][s + 1] %= mod;
            }
        }
    }
    

    ll res = 0;
    for(int i = 0; i < (1 << m); i++) res += dp[n][k][i], res %= mod;
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
