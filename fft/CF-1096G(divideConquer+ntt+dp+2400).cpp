#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

namespace NTT {
    const int mod = 998244353, G = 3;
    const int N = 2e6 + 100;
    int rev[N], bit, tot;

    int qpow(int a, int b) {
        int ans=1;
        while (b) {
            if (b & 1) ans = 1ll * ans * a % mod;
            a = 1ll * a * a % mod;
            b >>= 1;
        }
        return ans;
    }

    void DFT(int a[], int f, int tot){
       for (int i = 0; i < tot; i++) if (i < rev[i]) swap(a[i],a[rev[i]]);

        for (int i = 1; i < tot; i <<= 1){
            int gn = qpow(G, (mod - 1) / (i << 1));
            for (int j = 0; j < tot; j += (i << 1)){
                int g = 1;
                for (int k = 0; k < i; k++, g = 1ll * g * gn % mod){
                    int x = a[j + k],y = 1ll * g * a[j + k + i] % mod;
                    a[j + k] = (x + y) % mod; a[j + k + i] = (x - y + mod) % mod;
                }
            }
        }
        if (f == 1) return;
        int nv = qpow(tot, mod - 2); reverse(a + 1, a + tot);
        for (int i = 0; i < tot; i++) a[i] = 1ll * a[i] * nv % mod;
    }  

    int a[N], b[N], c[N];
    int n, m;
    vector<int> NTT() {
        for (int i = 0; i < tot; i ++ )
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));

        DFT(a, 1, tot);
        DFT(b, 1, tot);
        for(int i = 0; i < tot; i++) {
            c[i] = (a[i] + 0ll) * (b[i]) % mod;
        }
        
        DFT(c, -1, tot);
        vector<int> cc(n + m + 1);
        for(int i = 0; i <= n + m; i++) {
            cc[i] = c[i];
        }
        return cc;
    }
    
    vector<int >read(vector<int>& v1, vector<int>& v2) {
        n = v1.size() - 1;
        m = v2.size() - 1;
        while ((1 << bit) < n + m + 1) bit ++;
            tot = 1 << bit;
        for(int i = 0; i < tot; i++) a[i] = b[i] = 0;
        for(int i = 0; i <= n; i++) a[i] = v1[i];
        for(int i = 0; i <= m; i++) b[i] = v2[i];
        return NTT();
    }
}

const int N = 20, mod = 998244353;
bool is[N];
const int sz = 1e5 + 10;
vector<int> dp[sz];
int n, k;
vector<int> divide(int n) {
    if(dp[n].size() > 0) return dp[n];
    if(n == 1) {
        vector<int> a(10, 0);
        for(int i = 0; i < 10; i++) {
            if(is[i]) {
                a[i] = 1;
            }
        }
        return a;
    }
    int l = n / 2;
    if(l == n - l) {
        vector<int> a = divide(l);
        return dp[n] = NTT :: read(a, a);
    } else {
        vector<int> a = divide(l);
        vector<int> b = divide(n - l); 
        return dp[n] = NTT :: read(a, b);
    }
}


void solve() {
    cin >> n >> k;
    for(int i = 0; i < k; i++) {
        int d;
        cin >> d;
        is[d] = true;
    }
    n /= 2;
    vector<int> c = divide(n);
    int res = 0;
    for(int& i : c) {
        int ways = (i + 0ll) * i % mod;
        res += ways;
        res %= mod;
    }
    cout << res << endl;
}

int main()
{
    solve();
    return 0;
}
