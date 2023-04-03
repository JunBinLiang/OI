#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector



ll n;
int k, mod, all;
int dp[105][40];
int dfs(int i, int sum) {
    if(i >= n) {
       if(sum == all) return 1;
       else return 0;
    }
    if(dp[i][sum] != -1) {
        return dp[i][sum];
    }

    int res = 0;
    for(int x = 0; x < k; x++) {
        int v = all - x;
        if(v < 0) v += k;
        if(v != x) {
            res += dfs(i + 1, (sum + x) % k);
            res %= mod;
        }
    }

    return dp[i][sum] = res;
}
//1:50
void solve() {
    cin >> n >> k >> mod;
    ll tot = 1;
    for(int i = 0; i < n; i++) {
        tot *= k;
        tot %= mod;
    }
    
    int res = 0;
    for(int i = 0; i < k; i++) {
        memset(dp, -1, sizeof dp);
        all = i;
        res += dfs(0, 0);
        res %= mod;
    }
    
    tot -= res;
    if(tot < 0) tot += mod;
    cout << tot << endl;
}

int main()
{
    solve();
    return 0;
}
