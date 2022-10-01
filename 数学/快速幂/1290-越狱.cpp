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
const int mod = 100003;
ll qmi(ll a, ll k)
{
    ll res = 1;
    while (k)
    {
        if (k & 1) res = res * a % mod;
        a = a * a % mod;
        k >>= 1;
    }
    return res;
}

ll n, m;
void solve() {
    scanf("%lld%lld", &m, &n);
    ll tot = qmi(m, n);
    ll x = m % mod;
    x = (x * qmi(m - 1, n - 1)) % mod;
    cout << (tot - x + mod) % mod << endl;
}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
