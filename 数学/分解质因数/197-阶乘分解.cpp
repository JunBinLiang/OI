#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1000010;

int primes[N], cnt;
bool st[N];

void init(int n)
{
    for (int i = 2; i <= n; i ++ )
    {
        if (!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] * i <= n; j ++ )
        {
            st[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

int main()
{
    int n;
    cin >> n;
    init(n);

    for (int i = 0; i < cnt; i ++ )
    {
        int p = primes[i];
        int s = 0;
        for (int j = n; j; j /= p) s += j / p;
        printf("%d %d\n", p, s);
    }

    return 0;
}
