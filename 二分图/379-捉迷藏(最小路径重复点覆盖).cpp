#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 210, M = 30010;

int n, m;
bool d[N][N], st[N];
int match[N];

bool find(int x)
{
    for (int i = 1; i <= n; i ++ )
        if (d[x][i] && !st[i])
        {
            st[i] = true;
            int t = match[i];
            if (t == 0 || find(t))
            {
                match[i] = x;
                return true;
            }
        }

    return false;
}

int main()
{
    scanf("%d%d", &n, &m);
    while (m -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        d[a][b] = true;
    }

    // 传递闭包
    for (int k = 1; k <= n; k ++ )
        for (int i = 1; i <= n; i ++ )
            for (int j = 1; j <= n; j ++ )
                d[i][j] |= d[i][k] & d[k][j];

    int res = 0;
    for (int i = 1; i <= n; i ++ )
    {
        memset(st, 0, sizeof st);
        if (find(i)) res ++ ;
    }

    printf("%d\n", n - res);

    return 0;
}
