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

const int N = 1e7 + 10, mod = 1e9 + 7;
int mu[N], primes[N], cnt = 0;
bool st[N];


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

int n;
int cnts[N], w[N];
int p[500000 + 5], F[N], G[N];
//莫比乌斯应用 : https://blog.csdn.net/blaze003003/article/details/109755503
void solve() {
    init();
    
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        cnts[x]++;
    }

    p[0] = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = p[i - 1] * 2; 
        p[i] %= mod;
    }

    //f[i] : suitable subset with gcd() == i
    for(int i = 1; i < N; i++) {
        for(int j = i; j < N; j += i) {
            w[i] += cnts[j];
        }
        F[i] = p[w[i]] - 1;
    }
    
    /*for(int i = 1; i <= 10; i++) {
        cout << w[i] << "  ";
    } cout << endl << endl;
    for(int i = 1; i <= 10; i++) {
        cout << F[i] << "  ";
    } cout << endl << endl;*/

    
    for(int i = 1; i < N; i++) {
        G[i] = mu[i] * w[i];
    }
    
    /*for(int i = 1; i <= 10; i++) {
        cout << G[i] << "  ";
    } cout << endl << endl;*/

    for(int d = N - 1; d >= 1; d--) {
        for(int j = d + d; j < N; j += d) {
            G[j] += G[d];
        }
    }
    
    /*for(int i = 1; i <= 10; i++) {
        cout << G[i] << "  ";
    } cout << endl << endl;*/

    int res = 0;
    for(int i = 2; i < N; i++) {
        int x = 0;
        for(int d = i; d < N; d += i) {
            x += F[d] * mu[d / i];
            x %= mod;
            if(x < 0) x += mod;
        }
        
        x = (x + 0ll) * G[i] % mod;
        if(x < 0) x += mod;
        res += x;
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
