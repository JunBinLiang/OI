#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cstring>
using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector


int mod = 998244353;
const int N = 2010;
ll dp[N][N];
//3:21 - 3:28
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    memset(dp, 0, sizeof dp);
    dp[0][0] = m;
    for(int i = 1; i < n; i++) {
        for(int j = 0; j <= k; j++) {
            dp[i][j] = dp[i - 1][j];
            dp[i][j] += dp[i - 1][j - 1] * (m - 1);
            dp[i][j] %= mod;
        }
    }
    
    
    /*for(int i = 0; i < n; i++) {
        for(int j = 0; j <= k; j++) {
            cout << dp[i][j] << " ";
        } cout << endl;
    }*/
    
    cout << dp[n - 1][k] << endl;

}

int main() {
    solve();
    return 0;
}
