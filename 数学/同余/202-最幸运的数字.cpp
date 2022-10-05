#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

LL qmul(LL a, LL k, LL b)
{
    LL res = 0;
    while (k)
    {
        if (k & 1) res = (res + a) % b;
        a = (a + a) % b;
        k >>= 1;
    }
    return res;
}

LL qmi(LL a, LL k, LL b)
{
    LL res = 1;
    while (k)
    {
        if (k & 1) res = qmul(res, a, b);
        a = qmul(a, a, b);
        k >>= 1;
    }
    return res;
}

LL get_euler(LL C)
{
    LL res = C;
    for (LL i = 2; i <= C / i; i ++ )
        if (C % i == 0)
        {
            while (C % i == 0) C /= i;
            res = res / i * (i - 1);
        }
    if (C > 1) res = res / C * (C - 1);
    return res;
}

int main()
{
    int T = 1;
    LL L;
    while (cin >> L, L)
    {
        int d = 1;
        while (L % (d * 2) == 0 && d * 2 <= 8) d *= 2;

        LL C = 9 * L / d;

        LL phi = get_euler(C);

        LL res = 1e18;
        if (C % 2 == 0 || C % 5 == 0) res = 0;
        else
        {
            for (LL d = 1; d * d <= phi; d ++ )
                if (phi % d == 0)
                {
                    if (qmi(10, d, C) == 1) res = min(res, d);
                    if (qmi(10, phi / d, C) == 1) res = min(res, phi / d);
                }
        }

        printf("Case %d: %lld\n", T ++, res);
    }

    return 0;
}
