#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 50010;

int primes[N], cnt, mu[N], sum[N];
bool st[N];

void init()
{
    mu[1] = 1;
    for (int i = 2; i < N; i ++ )
    {
        if (!st[i]) primes[cnt ++ ] = i, mu[i] = -1;
        for (int j = 0; primes[j] * i < N; j ++ )
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
            mu[primes[j] * i] = -mu[i];
        }
    }
    for (int i = 1; i < N; i ++ ) sum[i] = sum[i - 1] + mu[i];
}

int g(int k, int x)
{
    return k / (k / x);
}

LL f(int a, int b, int k)
{
    a = a / k, b = b / k;
    LL res = 0;
    int n = min(a, b);
    for (int l = 1, r; l <= n; l = r + 1)
    {
        r = min(n, min(g(a, l), g(b, l)));
        res += (LL)(sum[r] - sum[l - 1]) * (a / l) * (b / l);
    }
    return res;
}

int main()
{
    init();
    int T;
    scanf("%d", &T);
    while (T -- )
    {
        int a, b, c, d, k;
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
        printf("%lld\n", f(b, d, k) - f(a - 1, d, k) - f(b, c - 1, k) + f(a - 1, c - 1, k));
    }
    return 0;
}
