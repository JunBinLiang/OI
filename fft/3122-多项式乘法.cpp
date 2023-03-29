#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 300010;
const double PI = acos(-1);

int n, m;
struct Complex
{
    double x, y;
    Complex operator+ (const Complex& t) const
    {
        return {x + t.x, y + t.y};
    }
    Complex operator- (const Complex& t) const
    {
        return {x - t.x, y - t.y};
    }
    Complex operator* (const Complex& t) const
    {
        return {x * t.x - y * t.y, x * t.y + y * t.x};
    }
}a[N], b[N];

int rev[N], bit, tot;
void fft(Complex a[], int inv)
{
    for (int i = 0; i < tot; i ++ )
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int mid = 1; mid < tot; mid <<= 1)
    {
        auto w1 = Complex({cos(PI / mid), inv * sin(PI / mid)});
        for (int i = 0; i < tot; i += mid * 2)
        {
            auto wk = Complex({1, 0});
            for (int j = 0; j < mid; j ++, wk = wk * w1)
            {
                auto x = a[i + j], y = wk * a[i + j + mid];
                a[i + j] = x + y, a[i + j + mid] = x - y;
            }
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i ++ ) scanf("%lf", &a[i].x);
    for (int i = 0; i <= m; i ++ ) scanf("%lf", &b[i].x);
    while ((1 << bit) < n + m + 1) bit ++;
    tot = 1 << bit;
    for (int i = 0; i < tot; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
    fft(a, 1), fft(b, 1);
    for (int i = 0; i < tot; i ++ ) a[i] = a[i] * b[i];
    fft(a, -1);
    for (int i = 0; i <= n + m; i ++ )
        printf("%d ", (int)(a[i].x / tot + 0.5));

    return 0;
}




/* ntt
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

namespace NTT {
    const int mod = 998244353, G = 3;
    const int N = 1e6;
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
    void NTT() {
        while ((1 << bit) < n + m + 1) bit ++;
        tot = 1 << bit;
        for (int i = 0; i < tot; i ++ )
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));

        DFT(a, 1, tot);
        DFT(b, 1, tot);
        for(int i = 0; i < tot; i++) {
            c[i] = (a[i] + 0ll) * (b[i]) % mod;
        }
        
        DFT(c, -1, tot);
        int inv = qpow(tot, mod - 2);
        for(int i = 0; i <= n + m; i++) {
            printf("%d ", c[i]);
        }
    }
    
    void read() {
        scanf("%d%d", &n, &m);
        for(int i = 0; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        for(int i = 0; i <= m; i++) {
            scanf("%d", &b[i]);
        }
    }
}

int main()
{
    NTT :: read();
    NTT :: NTT();
    return 0;
}

*/
