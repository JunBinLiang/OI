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



//2:01 
const int N = 1e6 + 10, mod = 998244353;
const int M = 1e7 + 10;
int n;
int a[N];
int dp[M], p[M];
ll ans[M];

int get(int l, int r) {
    if(l > r) return 0;
    if(l == 0) return p[r];
    return p[r] - p[l - 1];
}

void solve() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    ll res = 0;
    for(int i = 0; i <= a[n - 1]; i++) {
        p[i] = 0;
        ans[i] = 0;
        dp[i] = -1;
    }

    for(int i = 0; i < n; i++) {
        p[a[i]] = 1;
    }

    for(int i = 1; i <= a[n - 1]; i++) {
        p[i] += p[i - 1];
    }

    int s = a[n - 1];
    for(int i = 0; i < n; i++) {
        int g = __gcd(a[i], a[n - 1]);
        for(int j = 1; j * j <= g; j++) {
            if(g % j == 0) {
                int x = j;
                int y = g / j;
                ans[y]++;
                if(x != y) {
                    ans[x]++;
                }
            }
        }
    }
    
    for(int i = 1; i <= a[n - 1]; i++) {
        if(a[n - 1] % i == 0) {
            res += (ans[i] * (a[n - 1] / i));
            res %= mod;
            continue;
        }

        int k = a[n - 1] / i;

        if(dp[k] != -1) {
            res += (dp[k] + 0ll) * i;
            res %= mod;
            continue;
        }

        dp[k] = 0;
        for(int j = 0; j * k <= s; j++) {
            int l = j * k, r = min(a[n - 1], l + min(k - 1, j));
            dp[k] += get(l, r);
        }
        res += (dp[k] + 0ll) * i;
        res %= mod;
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
