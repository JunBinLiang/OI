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
#include <bitset>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define pb push_back

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}


const int MOD = 998244353;

ll fpow(ll x, ll y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
}  

ll res = 0;
int dep = 0;
void dfs(ll a, ll b, ll s1, ll s2, ll c1, ll c2) {
    dep++;
    if(a == 0 && b == 0) {
        return;
    }

    ll a1 = (a + 1) / 2, a2 = a - a1;
    ll b1 = (b + 1) / 2, b2 = b - b1;
   
    ll x = (fpow(2, a1) - 1) * (fpow(2, a2) - 1) % MOD;
    res += (s1 * x);
    res %= MOD;
    ll y = (fpow(2, b1) - 1) * (fpow(2, b2) - 1) % MOD;
    res += (s2 * y);
    res %= MOD;
    
    
    map<ll, ll> f, g;
    if(a != 1) {
        f[a1] += 2 * s1;
        f[a1] %= MOD;
        f[a2] += (2 * s1 + c1);
        f[a2] %= MOD;
        g[a1] += c1;
        g[a1] %= MOD;
        g[a2] += c1;
        g[a2] %= MOD;
    }

    if(b != 1) {
        f[b1] += 2 * s2;
        f[b1] %= MOD;
        f[b2] += (2 * s2 + c2);
        f[b2] %= MOD;
        g[b1] += c2;
        g[b1] %= MOD;
        g[b2] += c2;
        g[b2] %= MOD; 
        
    }   
    
    if(a == 1) {
        res += s1;
        res %= MOD;
    }
    if(b == 1) {
        res += s2;
        res %= MOD;
    }
    
    
    if(f.find(0) != f.end()) f.erase(0);
    if(g.find(0) != g.end()) g.erase(0);
    
    ll x1 = 0, x2 = 0;
    if(f.size() == 1) {
        auto it = f.begin();
        x1 = it -> first;
    } else if(f.size() == 2) {
        auto it = f.begin();
        x1 = it -> first;
        it++;
        x2 = it -> first;
    }

    dfs(x1, x2, f[x1], f[x2], g[x1], g[x2]);
}

void solve() {
    ll n;
    cin >> n;

    res = 0;
    dfs(n, 0, 1, 0, 1, 0);
    cout << res << endl;
}

int main()
{

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
