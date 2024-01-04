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


const int MOD = 998244353;
const int N = 3e5 + 100;
ll f[N];

unsigned long long seed = 131;
unsigned long long rands(){ return seed = (seed << 15) + (seed << 8)+( seed >> 3);}

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

ull line[N];
void add(int l, int r) {
    ull h = rands();
    line[l] ^= h;
    line[r + 1] ^= h;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> a(m);
    bool ok = true;
    for(int i = 0; i < m; i++) {
        cin >> a[i].first >> a[i].second;
    }

    for(int i = 0; i <= n + 1; i++) line[i] = 0;
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = f[i - 1] * (4 * i - 2);
        f[i] %= MOD;
        f[i] *= inv(i + 1, MOD);
        f[i] %= MOD;
    }

    add(1, n);
    for(auto p : a) {
        add(p.first, p.second);
    }
    
    ull h = 0;
    map<ull, int> ma;
    for(int i = 1; i <= n; i++) {
        h ^= line[i];
        ma[h]++;
    }
    
    ll res = 1;
    for(auto it = ma.begin(); it != ma.end(); it++) {
        int cnt = it -> second;
        if(cnt % 2 == 1) res = 0;
        res *= f[cnt / 2];
        res %= MOD;
    }
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
