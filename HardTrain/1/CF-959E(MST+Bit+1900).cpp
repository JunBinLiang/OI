
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector

ll dp[60];

ll dfs(ll n) {
    if(n <= 1) {
        return 0;
    }
    int b = -1;
    for(int i = 0; i < 50; i++) {
        if(n & (1ll << i)) {
            b = i;
        }
    }
    
    ll res = dp[b];
    if(n - (1ll << b) > 0) {
        res += (1ll << b);
    }
    res += dfs(n - (1ll << b));
    return res;
}

void solve() {
    ll n;
    cin >> n;

    memset(dp, 0, sizeof dp);
    for(int i = 1; i < 50; i++) {
        ll v = (1ll << i);
        ll c = 1;
        while(v > 1) {
            dp[i] += (v / 2) * c;
            c *= 2;
            v /= 2;
        }
    }


    cout << dfs(n) << endl;
}   


int main()
{   

    int t = 1;
    //cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
