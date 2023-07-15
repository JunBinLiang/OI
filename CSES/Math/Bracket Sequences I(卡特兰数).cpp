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
 


const int N = 1e6 + 100, MOD = 1e9 + 7;
ll f[N];

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

void solve() {
    int n;
    cin >> n;
    if(n % 2 == 1) {
        cout << 0 << endl;
        return;
    }
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = f[i - 1] * (4 * i - 2);
        f[i] %= MOD;
        f[i] *= inv(i + 1, MOD);
        f[i] %= MOD;
    }
    cout << f[n / 2] << endl;
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
