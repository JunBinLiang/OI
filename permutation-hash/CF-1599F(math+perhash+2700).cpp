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

//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");

const int N = 2e5 + 10, M = 30;
const int mod = 1e9 + 7;
int a[N];
int n, m;
ll p[N];
ll C[M][M];
ll h1[N], h2[N];
int k1 = 11, k2 = 23;

ll t1[M][N], t2[M][N];

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
		if(y & 1) res = (res * x) % mod;
		x = (x * x) %mod;
		y >>= 1;
	}
	return res;
}  

void init() {
    C[0][0] = 1;
    for(int i = 1;i < M; i++) {
      C[i][0]=1;
      for(int j = 1;j <= i;j++) {
        C[i][j] = ( C[i-1][j] + C[i-1][j-1] ) % mod;
      }
    }
}

void solve() {
    init();

    scanf("%d%d", &n, &m);
    p[0] = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        p[i] = a[i];
        p[i] += p[i - 1];
        p[i] %= mod;
    }

    h1[0] = h2[0] = 0;
    for(int i = 1; i <= n; i++) {
        ll t1 = fpow(a[i], k1);
        ll t2 = fpow(a[i], k2);
        h1[i] = (t1 + h1[i - 1]) % mod;
        h2[i] = (t2 + h2[i - 1]) % mod;
    }

    for(int j = 0; j <= k1; j++) {
        for(int i = 0; i < n; i++) {
            t1[j][i] = (C[k1][j] * fpow(i, j)) % mod;
            if(i) t1[j][i] += t1[j][i - 1];
            t1[j][i] %= mod;
        }
    }
    for(int j = 0; j <= k2; j++) {
        for(int i = 0; i < n; i++) {
            t2[j][i] = (C[k2][j] * fpow(i, j)) % mod;
            if(i) t2[j][i] += t2[j][i - 1];
            t2[j][i] %= mod;
        }
    }
    
    //sum = (2a[0] + (sz - 1) * d))

    for(int i = 0; i < m; i++) {
        int l, r, d;
        scanf("%d%d%d", &l, &r, &d);
        int sz = r - l + 1;
        ll sum = p[r] - p[l - 1];
        if(l == r) {
            printf("Yes\n");
            continue;
        }
        if(sum == 0) {
            printf("No\n");
            continue;
        }
        
        sum *= 2;
        sum %= mod;
        sum *= modInverse(sz, mod);
        sum %= mod;
        if(sum < mod) sum += mod;
        sum -= ((sz - 1ll) * d % mod);
        sum %= mod;
        if(sum < mod) sum += mod;
        //first term
        bool yes = true;
        ll x = sum * modInverse(2, mod);
        x %= mod;
        if(x < 0) x += mod;
        
        /*if(x != 0) {
            ll v1 = fpow(x, k1), v2 = fpow(x, k2);
            ll inv = modInverse(x, mod);
            ll hash1 = (h1[r] - h1[l - 1] + mod) % mod;
            ll hash2 = (h2[r] - h2[l - 1] + mod) % mod;
    
            ll X = (d * inv) % mod;
            ll cur1 = 0, cur2 = 0;
            for(int j = 0; j <= k1; j++) {
                cur1 += fpow(X, j) * t1[j][sz - 1];
                cur1 %= mod;
            }
    
            for(int j = 0; j <= k2; j++) {
                cur2 += fpow(X, j) * t2[j][sz - 1];
                cur2 %= mod;
            }
            
    
            cur1 *= v1; cur1 %= mod;
            cur2 *= v2; cur2 %= mod;
            if(cur1 != hash1 || cur2 != hash2) yes = false;
            if(yes) printf("YES\n");
            else printf("NO\n");    
        } else {
            
        }*/


        if(x == 0) {
            x += d;
            sz--;
        }
        
        ll v1 = fpow(x, k1), v2 = fpow(x, k2);
        ll inv = modInverse(x, mod);
        ll hash1 = (h1[r] - h1[l - 1] + mod) % mod;
        ll hash2 = (h2[r] - h2[l - 1] + mod) % mod;
    
        ll X = (d * inv) % mod;
        ll cur1 = 0, cur2 = 0;
        for(int j = 0; j <= k1; j++) {
            cur1 += fpow(X, j) * t1[j][sz - 1];
            cur1 %= mod;
        }
    
        for(int j = 0; j <= k2; j++) {
            cur2 += fpow(X, j) * t2[j][sz - 1];
            cur2 %= mod;
        }
            
        cur1 *= v1; cur1 %= mod;
        cur2 *= v2; cur2 %= mod;
        if(cur1 != hash1 || cur2 != hash2) yes = false;
        if(yes) printf("Yes\n");
        else printf("No\n");  
    }

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

