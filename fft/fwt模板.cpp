#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;
using ll = long long;



namespace FWT {
    const int mod = 998244353;
    const int N = 1e6;
    int n, m;
    int a[N], b[N];

    ll quick(ll x, ll p)
    {
        ll ret = 1;
        while(p)
        {
            if(p & 1) ret = ret * x % mod;
            x = x * x % mod;
            p >>= 1; 
        }
        return ret;
    }

    inline void mul() {
        for (int i = 0; i < n; i++) {
            a[i] = (a[i] + 0ll) * b[i] % mod;
            if(a[i] < 0) a[i] += mod;
        }
    }

    inline void out() {
        for (int i = 0; i < n; i++) {
            printf("%d ", a[i]);
        }
        cout << endl;
    }

    void OR(int a[], int x) {
        for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
            for (int i = 0; i < n; i += o)
                for (int j = 0; j < k; j++)
                    {
                        a[i + j + k] += a[i + j] * x;
                        a[i + j + k] %= mod;
                        if(a[i + j + k] < 0) a[i + j + k] += mod;
                    }
    }

    inline void AND(int a[], int x) {
        for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
            for (int i = 0; i < n; i += o)
                for (int j = 0; j < k; j++)
                    {
                        a[i + j] += a[i + j + k] * x;
                        a[i + j] %= mod;
                        if(a[i + j] < 0) a[i + j] += mod;
                    }
    }

    void XOR(int a[], int x) {
        for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
            for (int i = 0; i < n; i += o)
                for (int j = 0; j < k; j++) {
                    a[i + j] += a[i + j + k];
                    a[i + j] %= mod;
                    if(a[i + j] < 0) a[i + j] += mod;
                    
                    
                    a[i + j + k] = (a[i + j] - a[i + j + k] + mod) - a[i + j + k];
                    a[i + j + k] %= mod;
                    if(a[i + j + k] < 0) a[i + j + k] += mod;
                    
                    a[i + j] = ((a[i + j] + 0ll) * x) % mod; 
                    a[i + j + k] =  (a[i + j + k] + 0ll) * x % mod;
                    
                    if(a[i + j] < 0) a[i + j] += mod;
                    if(a[i + j + k] < 0) a[i + j + k] += mod;
                }
    }

    void solve(int v1[], int v2[], int len1, int len2) {
        n = len1;
        m = len2;
        for(int i = 0; i < n; i++) {
            a[i] = v1[i];
        }
        for(int i = 0; i < m; i++) {
            b[i] = v2[i];
        }
        OR(a, 1);
        OR(b, 1);
        mul();
        OR(a, -1);
        out();

        for(int i = 0; i < n; i++) {
            a[i] = v1[i];
        }
        for(int i = 0; i < m; i++) {
            b[i] = v2[i];
        }
        AND(a, 1);
        AND(b, 1);
        mul();
        AND(a, -1);
        out();


        for(int i = 0; i < n; i++) {
            a[i] = v1[i];
        }
        for(int i = 0; i < m; i++) {
            b[i] = v2[i];
        }
        XOR(a, 1);
        XOR(b, 1);
        mul();
        XOR(a, quick(2ll, mod - 2));
        out();

    }
}


const int N = 1 << 18;
int a[N], b[N];
void solve() {
   int m;
   cin >> m;
   int n = (1 << m);
   for(int i = 0; i < n; i++) cin >> a[i];
   for(int i = 0; i < n; i++) cin >> b[i]; 
   FWT :: solve(a, b, n, n);

}

int main()
{
    solve();
    return 0;
}
