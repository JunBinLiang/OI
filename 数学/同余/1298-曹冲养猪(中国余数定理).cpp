#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 10;

int n;
int A[N], B[N];

void exgcd(LL a, LL b, LL &x, LL &y)
{
    if (!b) x = 1, y = 0;
    else
    {
        exgcd(b, a % b, y, x);
        y -= a / b * x;
    }
}

int main()
{
    scanf("%d", &n);

    LL M = 1;
    for (int i = 0; i < n; i ++ )
    {
        scanf("%d%d", &A[i], &B[i]);
        M *= A[i];
    }

    LL res = 0;
    for (int i = 0; i < n; i ++ )
    {
        LL Mi = M / A[i];
        LL ti, x;
        exgcd(Mi, A[i], ti, x);
        res += B[i] * Mi * ti;
    }

    cout << (res % M + M) % M << endl;

    return 0;
}
