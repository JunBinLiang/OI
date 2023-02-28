#include <iostream>
#include <vector>
using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector

const int N = 1e5 + 10, mod = 1e9 + 7;
ll dp[N];
//2: 30
void solve() {
    
    int n, k;
    cin >> n >> k;
    dp[0] = 1;
    for(int i = 1; i < N; i++) {
        dp[i] = dp[i - 1];
        if(i - k >= 0) dp[i] += dp[i - k];
        dp[i] %= mod;
    }

    for(int i = 1; i < N; i++) {
        dp[i] += dp[i - 1];
        dp[i] %= mod;
    }


    for(int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        cout << (dp[r] - dp[l - 1] + mod) % mod << endl;
    }
}

int main() {
    solve();
    return 0;
}
