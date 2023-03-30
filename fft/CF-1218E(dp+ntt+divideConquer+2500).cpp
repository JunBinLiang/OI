#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;
using ll = long long;

const int N = 2e4 + 10, mod = 998244353;
vector<int> f[N];
int n, k, q;
namespace NTT {
    int t1 = 0;
    const int mod = 998244353, G = 3;
    const int N = 1e5 + 100;
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
                    int x = a[j + k], y = 1ll * g * a[j + k + i] % mod;
                    a[j + k] = (x + y) % mod; a[j + k + i] = (x - y + mod) % mod;
                    t1++;
                }
            }
        }
        if (f == 1) return;
        int nv = qpow(tot, mod - 2); reverse(a + 1, a + tot);
        for (int i = 0; i < tot; i++) a[i] = 1ll * a[i] * nv % mod;
    }  

    int a[N], b[N], c[N];
    int n, m;
    void NTT(int idx) {
        for (int i = 0; i < tot; i ++ )
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));

        DFT(a, 1, tot);
        DFT(b, 1, tot);
        for(int i = 0; i < tot; i++) {
            c[i] = (a[i] + 0ll) * (b[i]) % mod;
        }
        
        DFT(c, -1, tot);
        int sz = min(n + m + 1, k + 1);
        f[idx].resize(sz + 1);
        for(int i = 0; i <= sz; i++) {
            f[idx][i] = c[i];
        }
    }
    
    void solve(vector<int>& v1, vector<int>& v2, int idx) {
        n = v1.size() - 1;
        m = v2.size() - 1;
        tot = 0;
        bit = 0;
        while ((1 << bit) < n + m + 1) bit ++;
            tot = 1 << bit;
        for(int i = 0; i < tot; i++) a[i] = b[i] = 0;
        for(int i = 0; i <= n; i++) a[i] = v1[i];
        for(int i = 0; i <= m; i++) b[i] = v2[i];
        NTT(idx);
    }
}

int a[N], b[N];
void divideConquer() {
    for(int i = 0; i < n; i++) f[i].clear(), f[i] = {1, b[i]};
    for(int len = 1; len <= n; len *= 2) {
        for(int i = 0; i < n; i += len * 2) {
            if(i + len < n) {
                NTT :: solve(f[i], f[i + len], i);
            }
        }
    }
}

void solve() {
    for(int i = 0; i < n; i++) {
        b[i] = a[i];
    }

    int op, q;
    scanf("%d%d", &op, &q);
    
    if(op == 1) {
        int ith, d;
        scanf("%d%d", &ith, &d);
        b[ith - 1] = d;
        b[ith - 1] %= mod;
    } else {
        int l, r, d;
        scanf("%d%d%d", &l, &r, &d);
        l--; r--;
        for(int i = l; i <= r; i++) {
            b[i] += d;
            b[i] %= mod;
        }
    }

    for(int i = 0; i < n; i++) {
        b[i] = q - b[i];
        b[i] %= mod;
        if(b[i] < 0) b[i] += mod;
    }
    NTT :: t1 = 0;
    divideConquer();
    printf("%d\n", f[0][k]);
}

int main()
{
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
