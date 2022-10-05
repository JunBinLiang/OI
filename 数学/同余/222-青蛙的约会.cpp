#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

LL exgcd(LL a, LL b, LL &x, LL &y)
{
    if (!b)
    {
        x = 1, y = 0;
        return a;
    }

    LL d = exgcd(b, a % b, y, x);
    y -= a / b * x;

    return d;
}

int main()
{
    LL a, b, m, n, L;
    cin >> a >> b >> m >> n >> L;

    LL x, y;
    LL d = exgcd(m - n, L, x, y);
    if ((b - a) % d) puts("Impossible");
    else
    {
        x *= (b - a) / d;
        LL t = abs(L / d);
        cout << (x % t + t) % t << endl;
    }

    return 0;
}
