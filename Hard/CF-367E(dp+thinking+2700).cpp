#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstring>
#include <algorithm>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector

const int mod = 1e9 + 7;
const int N = 350;
ll f[N];

ll dp[2][N][N];

void solve() {
    int n, m, x;
    cin >> n >> m >> x;

    if(n > m) {
        cout << 0 << endl;
        return;
    }

    

    f[0] = 1;
    for(int i = 1; i < N; i++) {
        f[i] = f[i - 1] * i;
        f[i] %= mod;
    }

    memset(dp, 0, sizeof dp);
    dp[1][1][0] = 1;
    dp[1][1][1] = 1;
    if(x != 1) dp[1][0][0] = 1;
    
    for(int le = 2; le <= m; le++) {
        
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= n; j++) {
                dp[0][i][j] = dp[1][i][j];
            }
        }
        
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= i; j++) {
                dp[1][i][j] = 0;
                if(i - 1 >= 0 && i - 1 >= j) {
                    dp[1][i][j] += dp[0][i - 1][j];
                }

                if(j - 1 >= 0 && le != x) {
                    dp[1][i][j] += dp[0][i][j - 1];
                }
                
                if(i - 1 >= 0 && j - 1 >= 0) {
                    dp[1][i][j] += dp[0][i - 1][j - 1];
                }
                
                //can skip
                if(le != x) {
                    dp[1][i][j] += dp[0][i][j];
                }
                dp[1][i][j] %= mod;
            }
        }
    }

    ll res = dp[1][n][n];
    res = (res * f[n]) % mod;
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
