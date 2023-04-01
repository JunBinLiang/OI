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
    
    Complex operator+= (const Complex& t) const
    {
        return {x + t.x, y + t.y};
    }
    Complex operator-= (const Complex& t) const
    {
        return {x - t.x, y - t.y};
    }
    Complex operator*= (const Complex& t) const
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

    vector<int> stringMatch(char s[], char t[]) {
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
        
        vector<int> cc;
        for(int i = 0; i <= n + m; i++) {
            int v = (int)(c[i].x / tot + 0.5);
            cc.push_back(v);
        }
        return cc;
    }
}


const int N = 405, M = 1e6;
char s[N][N], t[N][N];
vector<string> a, b;
int n, m, r, c;
int nn, mm;
void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%s", s[i]);
    }
    scanf("%d%d", &r, &c);
    for(int i = 0; i < r; i++) {
        scanf("%s", t[i]);
    }
    nn = n;
    mm = m;

    for(int i = 0; i < n; i++) {
        string ss;
        for(int j = 0; j < m + c; j++) {
            ss += s[i][j % m];
        }
        a.push_back(ss);
    }
    
    int k = 0;
    while(a.size() < n + r) {
        a.push_back(a[k++]);
    }
    
    char S[M], T[M];
    n = a.size(); m = a[0].size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            S[i * m + j] = a[i][j];
        }
    }
    
    S[n * m] = '\0';
    for(int i = 0; i < M; i++) T[i] = '*';
    int last = -1;
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            if(t[i][j] == '?') {

            } else {
                T[j + i * m] = t[i][j];
                last = j + i * m;
            }
        }
    }
    T[last + 1] = '\0';
    int len = strlen(T);
    
    vector<int> c = FFT :: stringMatch(S, T);
    for(int i = 0; i < nn; i++) {
        for(int j = 0; j < mm; j++) {
            int idx = i * m + j;
            if(!c[idx + len - 1]) {
                printf("1");
            } else {
                printf("0");
            }
        }
        printf("\n");
    }

}

int main()
{
    solve();
    return 0;
}
