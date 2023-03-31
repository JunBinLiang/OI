#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;
using ll = long long;


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
    const int N = 1e6 + 2e5;
    const double PI = acos(-1);
    int rev[N], bit, tot;
    Complex a[N], b[N], c[N];
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
        //for (int i = 0; i <= n + m; i ++ )
            //printf("%d ", (int)(a[i].x / tot + 0.5));
    }

    void stringMatch(char s[], char t[]) {
        int A[N], B[N];
        memset(A, 0, sizeof A); memset(B, 0, sizeof B);
        m = strlen(t) - 1;
        n = strlen(s) - 1;

        tot = 0; bit = 0;
        while ((1 << bit) < n + m + 1) bit ++;
        tot = 1 << bit;
        for (int i = 0; i < tot; i ++ )
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));

        for(int i = 0, j = m; i <= m; i++, j--) {
            if(t[i] == '*') A[j] = 0;
            else A[j] = t[i] - 'a' + 1;
        }
        for(int i = 0; i <= n; i++) {
            if(s[i] == '*') B[i] = 0;
            else B[i] = s[i] - 'a' + 1;
        }
        
        
        /*for(int i = 0; i < tot; i++) cout << A[i] << " ";
        cout << endl;
        for(int i = 0; i < tot; i++) cout << B[i] << " ";
        cout << endl;
        cout << tot << endl << endl;*/
        
        //fft 第一次
        for(int i = 0; i < tot; i++) {
            a[i].x = (double)A[i] * A[i] * A[i]; a[i].y = 0;
            b[i].x = B[i]; b[i].y = 0;
        }
        fft(a, 1); fft(b, 1);
        for(int i = 0; i < tot; i++) {
            a[i] = a[i] * b[i], c[i] = a[i];
        }
        

        //fft 第二次
        for(int i = 0; i <= tot; i++) {
            a[i].x = (double)A[i] * A[i]; a[i].y = 0;
            b[i].x = (double)B[i] * B[i]; b[i].y = 0;
        }
        fft(a, 1); fft(b, 1);
        Complex two = {2, 0};
        for(int i = 0; i < tot; i++) {
            a[i] = a[i] * b[i];
            a[i] = a[i] * two;
            c[i] = c[i] - a[i];
        }


        //fft 第三次
        for(int i = 0; i < tot; i++) {
            a[i].x = (double)A[i]; a[i].y = 0;
            b[i].x = (double)B[i] * B[i] * B[i]; b[i].y = 0;
        }
        fft(a, 1); fft(b, 1);
        for(int i = 0; i < tot; i++) a[i] = a[i] * b[i], c[i] = c[i] + a[i];

        //inverse
        fft(c, -1);
        
        vector<int> res;
        n++;
        m++;
        for(int i = 0; i <= n - m; i++) {
            int v = (int)(c[i + m - 1].x / tot + 0.5);
            if(v == 0) {
                res.push_back(i);
            }
        }

        cout << res.size() << endl;
        for(int i : res) {
            printf("%d ", i + 1);
        }
        printf("\n");
    }
}



//https://mivik.gitee.io/2019/intro/fft-string/
const int N = 3e5 + 10;
char s[N], t[N];
int n, m;
void solve() {
    scanf("%d%d", &m, &n);
    scanf("%s", t);
    scanf("%s", s);
    FFT :: stringMatch(s, t);
}

int main()
{
    solve();
    return 0;
}
