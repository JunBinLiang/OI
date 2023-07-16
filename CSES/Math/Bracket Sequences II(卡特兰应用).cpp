#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>
#include <fstream>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
using namespace std;
 

const int MOD = 1e9 + 7;
const int N = 2e6 + 10;
ll fact[N];

ll fpow(ll x, int y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
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

ll C(int n,int m) {
    return fact[n] * fpow(fact[n - m], MOD - 2) % MOD * fpow (fact[m], MOD - 2) % MOD;
}

//https://codeforces.com/blog/entry/87585 
void solve() {
    int n;
    string s;
    cin >> n >> s;
    if(n % 2 == 1) {
        cout << 0 << endl;
        return;
    }
    
    int open = 0, close = 0, cnt = 0;
    for(char& c : s) {
        if(c == '(') {
            open++;
            cnt++;
        } else {
            close++;
            cnt--;
            if(cnt < 0) {
                cout << 0 << endl;
                return;
            }
        }
    }
    
    fact[0] = 1;
    for(int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i; fact[i] %= MOD;
    }

    
    if(open > n / 2 || close > n / 2) {
        cout << 0 << endl;
        return;
    }

    int k = cnt;
    n = n / 2 - open;
    
    ll x = (k + 1), y = inv(n + k + 1, MOD);
    x *= y; x %= MOD;
    ll res = x * C(2 * n + k, n);
    res %= MOD;
    cout << res << endl;
}

int main()
{
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
