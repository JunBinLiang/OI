#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

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
};

namespace FFT {
    const int N = 1e6 + 10;
    const double PI = acos(-1);
    int rev[N], bit, tot;
    Complex a[N], b[N];
    int n, m;
    
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

    void solve(vector<Complex>& v1, vector<Complex>& v2) {
        n = v1.size() - 1;
        m = v2.size() - 1;
        tot = 0; bit = 0;
        while ((1 << bit) < n + m + 1) bit ++;
        tot = 1 << bit;
        for (int i = 0; i < tot; i ++ )
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        for(int i = 0; i < tot; i++) a[i] = {0, 0}, b[i] = {0, 0};
        for(int i = 0; i <= n; i++) a[i] = v1[i];
        for(int i = 0; i <= m; i++) b[i] = v2[i];
        fft(a, 1), fft(b, 1);
        for (int i = 0; i < tot; i ++ ) a[i] = a[i] * b[i];
        fft(a, -1);
        for (int i = 0; i <= n + m; i ++ )
            printf("%d ", (int)(a[i].x / tot + 0.5));
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<Complex> a, b;
    
    for(int i = 0; i <= n; i++) {
        int x;
        scanf("%d", &x);
        a.push_back({x, 0});
    }
    
    for(int i = 0; i <= m; i++) {
        int x;
        scanf("%d", &x);
        b.push_back({x, 0});
    }
    
    FFT :: solve(a, b);
}

int main()
{
    solve();
    return 0;
}
