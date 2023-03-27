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
#include <iostream>
   
using namespace std;  
using ll = long long;
#define pb push_back
#define ve vector

const int N = 1e6 + 10, mod = 1e9 + 7;
int mu[N], primes[N], cnts[N], cnt = 0;
ll F[N];
bool st[N];

int n;
int a[N]; ll p[N];

void init() {
    mu[1] = 1;
    for (int i = 2; i < N; i ++ )
    {
        if (!st[i]) primes[cnt ++ ] = i, mu[i] = -1;
        for (int j = 0; primes[j] * i < N; j ++ )
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
            mu[i * primes[j]] = -mu[i];
        }
    }
}

void solve() {
    memset(cnts, 0, sizeof cnts);
    memset(F, 0, sizeof F);
    init();

    scanf("%d", &n);
    int mx = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        cnts[a[i]]++;
        mx = max(mx, a[i]);
    }

    p[0] = 1;
    for(int i = 1; i < N; i++) {
        p[i] = p[i - 1] * 2; p[i] %= mod;
    }

    //F[i] : sum of all subsequesce with gcd(...) % i == 0
    for(int i = 1; i < N; i++) {
        int cnt = 0;
        for(int j = i; j < N; j += i) {
            cnt += cnts[j];
        }

        //C(n, 1) * 1 + C(n, 2) * 2 + C(n, 3) * 3 ... C(n, n) * n
        // n * pow[n - 1]
        if(cnt > 0) {
            F[i] = (cnt + 0ll) * p[cnt - 1];
            F[i] %= mod;
        }
    }

    ll res = 0;
    for(int i = 2; i < N; i++) {
        ll sum = 0;
        for(int d = i; d < N; d += i) {
            sum += (F[d] * mu[d / i]);
            sum %= mod;
        }
        sum *= i;
        sum %= mod;
        res += sum;
        res %= mod;
    }

    cout << res << endl;
    
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
