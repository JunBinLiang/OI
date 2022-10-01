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
const int mod = 200907;
ll a, b, c, k;


int qmi(ll a, ll k)
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

void solve() {
    scanf("%lld%lld%lld%lld", &a, &b, &c, &k);
    if(a + c == 2 * b) {
        cout << (a + (b - a) * (k - 1)) % mod << endl;   
    } else {
        ll r = b / a;
        cout << (a * qmi(r, k - 1)) % mod << endl;
    }
}

int main() {
    int t;
    cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}


