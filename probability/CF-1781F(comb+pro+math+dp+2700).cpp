#include <iostream>
#include <vector>
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
#include<fstream>
 

using namespace std;  
using ll = long long;
#define pb push_back

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

const int M = 1e4 + 10, mod = 998244353;
const int N = 505;
int n;
ll q, p;
ll inv[M];
ll dp[N][N], C[N][N], f[N][N];

void solve() {
    cin >> n >> q;

    for(int i = 1; i < M; i++) {
        inv[i] = modInverse(i, mod);
    }

    p = (q * inv[10000]) % mod; //success
    q = (1 - p) + mod; //fail

    //success : p
    //fail : ((1 - p) + mod)

    //()    +1    -1
    //)(    -1    +1

    //n = 2
    //(3/5) * (3/5) * (3/3) = 9/25
    //(3/5) * (2/3) * (1/3) = 2/25

    //(... x,         x + 1, x ...)
    //(... x,         x - 1, x ...)

    C[0][0] = 1;
    for(int i = 1;i < N; i++) {
        C[i][0]=1;
        for(int j = 1; j <= i;j++) {
            C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
        }
    }


    //f(n, x) = p * f(i, x) * f(n - 1 - i - j, x) * f(j, x + 1) + 
    //          (1 - p) * f(i, x) * f(n - 1 - i - j, x) * f(j, x - 1) 

    // *** group that part
    //[(p * f(i, x + 1) + (1 - p) * f(i, x - 1)) ]  * [f(n - 1 - i - j, x) * f(j, x) ]
    //[f(n - 1 - i - j, x) * f(j, x) ]    set (n - 1 - i) as k
    
    memset(dp, 0, sizeof dp);
    memset(f, 0, sizeof f);

    //base case
    for(int x = 0; x < N; x++) {
        dp[0][x] = f[0][x] = 1;
    }

    for(int i = 1; i <= n; i++) { //how many operation
        for(int x = 0; x <= n - i; x++) {
            for(int j = 0; j <= i - 1; j++) {
                ll v1 =  ((p * dp[j][x + 1] + q * (x > 0 ? dp[j][x - 1] : 0)) % mod);
                v1 *= C[i - 1][j];
                v1 %= mod;
                ll v2 = (f[i - 1 - j][x]) % mod;
                dp[i][x] += (v1 * v2);
                dp[i][x] %= mod;
            }

            for(int k = 0; k <= i; k++) { //f[k][j]
                f[i][x] += (dp[k][x] * dp[i - k][x]) % mod * C[i][k];
                f[i][x] %= mod;
            }
        }
    }
    
    ll res = dp[n][0];
    for(int i = 1; i <= 2 * n ; i += 2) {
        res *= inv[i];
        res %= mod;
    }
    cout << res << endl;
} 


int main() {
	// your code goes here
	int t = 1;
	//cin >> t;
	while(t--) {
	    solve();
	}
	return 0;
}  

//aabba
