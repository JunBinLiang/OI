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


const int mod = 1e9 + 7;
const int N = 1e6 + 5;
int n, m, k;
ll fact[N];
ll s2[1010][1010];
ll fpow(ll x, int y, int mod){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % mod;
		x = (x * x) % mod;
		y >>= 1;
	}
	return res;
}  

ll C(int n,int m, int mod) {
    return fact[n] * fpow(fact[n-m], mod - 2, mod) % mod * fpow (fact[m], mod - 2, mod) % mod;
}

ll inv(ll a, ll m) {
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

ll add(ll x, ll y) {
    x += y;
    x %= mod;
    return x;
}

//https://www.lizhechen.com/2018/09/17/%E7%BB%84%E5%90%88%E6%95%B0%E5%AD%A6%E2%80%94%E2%80%94%E7%90%83%E6%94%BE%E5%85%A5%E7%9B%92%E5%AD%90%E7%9A%84%E6%96%B9%E6%A1%88%E6%95%B0/
void solve() {
    ll res = 0;
    cin >> n >> m >> k;
    fact[0] = fact[1] = 1;
    for(int i = 2; i < N; i++) {
        fact[i] = fact[i - 1] * i;
        fact[i] %= mod;
    }
    
    //第二类斯特林
    s2[0][0] = 1;
    for (int i = 1; i < 1010; i ++ ) {
        for (int j = 1; j < 1010; j ++ )
        {
            s2[i][j] = (s2[i - 1][j - 1] + j * s2[i - 1][j]) % mod;
        }
    }
    
    //球不同，盒子不同，不可以有空盒
    //把选多少数字看成盒子，可以放的row number看成球
    if(m == 1) {
        for(int i = 1; i <= min(n, k); i++) {
            ll w = C(k, i, mod);
            ll x = s2[n][i]; 
            x *= fact[i];
            x %= mod;
            x *= w;
            x %= mod;
            res += x;
            res %= mod;
        }
        cout << res << endl;
        return;   
    }
    if(m == 2) {
        for(int i = 1; i <= min(n, k); i++) {
            ll w = C(k, i, mod);
            ll x = s2[n][i];
            x *= fact[i];
            x %= mod;
            x *= w;
            x %= mod;
            x *= x;
            x %= mod;
            res += x;
            res %= mod;
        }
        cout << res << endl;
        return;
    }
    
    /*for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) cout << s2[i][j] << " ";
        cout << endl;
    }
    cout << endl << endl;*/
    

    for(int i = 1; i <= min(n, k); i++) { 
        ll w1 = C(k, i, mod);
        ll x1 = add(s2[n][i] * fact[i], 0);
        x1 *= w1;
        x1 %= mod;
        
        for(int common = 1; common <= i; common++) {
            int dif = i - common;
            if(k >= i + dif) {
                ll w2 = C(i, common, mod) * C(k - i, dif, mod);
                w2 %= mod;
                ll x2 = add(s2[n][i] * fact[i], 0);
                x2 *= w2;
                x2 %= mod;
                
                ll lr = add(x1 * x2, 0);
                ll y = lr * fpow(fpow(common, n, mod), m - 2, mod);
                y %= mod;
                res += y;
                res %= mod;
            }
        }
        
    }

    cout << res % mod << endl;
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
