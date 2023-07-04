#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 20, mod = 1e9 + 7;

LL A[N];
int down = 1;

int qmi(int a, int k, int p)
{
    int res = 1;
    while (k)
    {
        if (k & 1) res = (LL)res * a % p;
        a = (LL)a * a % p;
        k >>= 1;
    }
    return res;
}

int C(LL a, LL b)
{
    if (a < b) return 0;
    int up = 1;
    for (LL i = a; i > a - b; i -- ) up = i % mod * up % mod;

    return (LL)up * down % mod; // 费马小定理
}

int main()
{
    LL n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i ++ ) cin >> A[i];

    for (int j = 1; j <= n - 1; j ++ ) down = (LL)j * down % mod;
    down = qmi(down, mod - 2, mod);

    int res = 0;
    for (int i = 0; i < 1 << n; i ++ )
    {
        LL a = m + n - 1, b = n - 1;
        int sign = 1;
        for (int j = 0; j < n; j ++ )
            if (i >> j & 1)
            {
                sign *= -1;
                a -= A[j] + 1;
            }
        res = (res + C(a, b) * sign) % mod;
    }

    cout << (res + mod) % mod << endl;

    return 0;
}
