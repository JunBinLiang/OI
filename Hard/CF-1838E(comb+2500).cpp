#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;
using ll = long long;

const int N = 2e5 + 10, MOD = 1e9 + 7;
int a[N];

ll modInverse(ll a, ll m) {
    ll m0 = m;
    ll y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
          // q is quotient
        ll q = a / m;
        ll t = m;
        // m is remainder now, process
        // same as Euclid's algo
        m = a % m;
        a = t;
        t = y;
        // Update x and y
        y = x - q * y;
        x = t;
    }
    // Make x positive
    if (x < 0)
        x += m0;
    return x;
}

ll fpow(ll x, int y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
}  

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    if(k == 1) {
        cout << 1 << endl;        
        return;
    }
    
    //dp[i][j] = dp[i - 1][j] * (k - 1) + dp[i - 1][j - 1] when j < n
    //dp[i][j] = dp[i - 1][j] * (k) + dp[i - 1][j - 1] when j == n
    //convert to => how many arrays contains at least n 1
    
    ll res = fpow(k, m);
    ll ways = 1;
    ll f = 1;
    for(int i = 1; i < n; i++) {
        ways *= (m - (i - 1));
        ways %= MOD;
        if(i > 0) f *= i;
        f %= MOD;
        ll v = modInverse(f, MOD);
        ll w = (ways * v) % MOD;
        ll comb = fpow(k - 1, m - i);
        ll x = w * comb; x %= MOD;
        res -= x;
        if(res < 0) res += MOD;
    }
    
    ll t = fpow(k - 1, m);
    res -= t;
    if(res < 0) res += MOD;
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
