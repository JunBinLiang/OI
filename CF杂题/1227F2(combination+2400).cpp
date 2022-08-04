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
   
using namespace std;  

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define f first
#define se second
#define W while
#define um unordered_map
#define us unordered_set
#define be begin
#define en end

//1 : 11
int n; ll k;
int mod = 998244353;
const int N = 2e5 + 10;
int a[N];
int b[N];
ll f[N];
ll fact[N];
ll res = 0;

ll fpow(ll x, int y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % mod;
		x = (x * x) %mod;
		y >>= 1;
	}
	return res;
}  

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

  ll C(int n,int m) {
      return fact[n] * fpow(fact[n - m], mod - 2) % mod * fpow (fact[m], mod - 2) % mod;
  }

  ll modInverse(ll a, int m) {
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

void solve() {
  cin >> n >> k;
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    b[(i + 1) % n] = (a[i]);
  }

  if(k == 1) {
    cout << 0 << endl;
    return;
  }

  f[0] = 1;
  for(int i = 1; i < N; i++) f[i] = (f[i - 1] * k) % mod;
  fact[0] = 1;
  for(int i = 1; i < N; i++) fact[i] = (fact[i - 1] * i) % mod;

  int cnt = 0, dif = 0;
  for(int i = 0; i < n; i++) {
    if(a[i] == b[i]) cnt++;
    else dif++;
  }

  ll inv = modInverse(2, mod);
  
  for(int i = 1; i <= dif; i++) {
    ll y = fpow((k - 2), dif - i);
    ll com = C(dif, i);
    ll sum = fpow(2, (i));
    if(i % 2 == 0) {
      sum += C(i, i / 2);
      sum %= mod;
    }
    

    sum *= inv;
    sum %= mod;
    if(i % 2 == 0) {
      sum -= C(i, i / 2);
      sum += mod;
      sum %= mod;
    }
    
    sum *= com;
    sum %= mod;

    res += (sum * y);
    res %= mod;
  }
  
  res *= f[cnt];
  res %= mod;
  cout << res << endl;
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
}

// 1 3 1
// 1 1 3

//C(1, 0)
//C(2,0) C(2, 1) C(2, 2)
