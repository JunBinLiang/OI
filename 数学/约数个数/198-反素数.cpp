#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

int primes[9] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
int maxd, number;
int n;

void dfs(int u, int last, int p, int s)
{
    if (s > maxd || s == maxd && p < number)
    {
        maxd = s;
        number = p;
    }

    if (u == 9) return;

    for (int i = 1; i <= last; i ++ )
    {
        if ((LL)p * primes[u] > n) break;
        p *= primes[u];
        dfs(u + 1, i, p, s * (i + 1));
    }
}
//求最小拥有最多约数个数的数
int main()
{
    cin >> n;

    dfs(0, 30, 1, 1);

    cout << number << endl;

    return 0;
}
