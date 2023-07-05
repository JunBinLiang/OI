#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 50010;

int primes[N], cnt;
bool st[N];
int mobius[N], sum[N];

// 线性筛法，求莫比乌斯函数
void init(int n)
{
    mobius[1] = 1;
    for (int i = 2; i <= n; i ++ )
    {
        if (!st[i])
        {
            primes[cnt ++ ] = i;
            mobius[i] = -1;
        }
        for (int j = 0; primes[j] * i <= n; j ++ )
        {
            int t = primes[j] * i;
            st[t] = true;
            if (i % primes[j] == 0)
            {
                mobius[t] = 0;
                break;
            }
            mobius[t] = mobius[i] * -1;
        }
    }

    for (int i = 1; i <= n; i ++ ) sum[i] = sum[i - 1] + mobius[i];
}

int main()
{
    init(N - 1);

    int T;
    scanf("%d", &T);
    while (T -- )
    {
        int a, b, d;
        scanf("%d%d%d", &a, &b, &d);
        a /= d, b /= d;
        int n = min(a, b);
        LL res = 0;
        for (int l = 1, r; l <= n; l = r + 1)
        {
            r = min(n, min(a / (a / l), b / (b / l)));
            res += (sum[r] - sum[l - 1]) * (LL)(a / l) * (b / l);
        }

        printf("%lld\n", res);
    }

    return 0;
}
