#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100010, M = N * 3, INF = 1e8;

int n, m, new_n;
int h1[N], h2[N], e[M], w[M], ne[M], idx;
int dfn[N], low[N], cnt;
int s[N], stot[N], fu[N], fw[N];
int d[N], f[N], q[N];
int ans;

void add(int h[], int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void build_circle(int x, int y, int z)
{
    int sum = z;
    for (int k = y; k != x; k = fu[k])
    {
        s[k] = sum;
        sum += fw[k];
    }
    s[x] = stot[x] = sum;
    add(h2, x, ++ new_n, 0);
    for (int k = y; k != x; k = fu[k])
    {
        stot[k] = sum;
        add(h2, new_n, k, min(s[k], sum - s[k]));
    }
}

void tarjan(int u, int from)
{
    dfn[u] = low[u] = ++ cnt;
    for (int i = h1[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            fu[j] = u, fw[j] = w[i];
            tarjan(j, i);
            low[u] = min(low[u], low[j]);
            if (dfn[u] < low[j]) add(h2, u, j, w[i]);
        }
        else if (i != (from ^ 1)) low[u] = min(low[u], dfn[j]);
    }
    for (int i = h1[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (dfn[u] < dfn[j] && fu[j] != u)
            build_circle(u, j, w[i]);
    }
}

int dfs(int u)
{
    int d1 = 0, d2 = 0;
    for (int i = h2[u]; ~i; i = ne[i])
    {
        int j = e[i];
        int t = dfs(j) + w[i];
        if (t >= d1) d2 = d1, d1 = t;
        else if (t > d2) d2 = t;
    }
    f[u] = d1;
    if (u <= n) ans = max(ans, d1 + d2);  // u是圆点
    else  // u是方点
    {
        int sz = 0;
        d[sz ++ ] = -INF;
        for (int i = h2[u]; ~i; i = ne[i])
            d[sz ++ ] = f[e[i]];
        for (int i = 0; i < sz; i ++ ) d[sz + i] = d[i];

        int hh = 0, tt = -1;
        for (int i = 0; i < sz * 2; i ++ )
        {
            if (hh <= tt && i - q[hh] > sz / 2) hh ++ ;
            if (hh <= tt) ans = max(ans, d[i] + i + d[q[hh]] - q[hh]);
            while (hh <= tt && d[q[tt]] - q[tt] <= d[i] - i) tt -- ;
            q[ ++ tt] = i;
        }
    }

    return f[u];
}

int main()
{
    scanf("%d%d", &n, &m);
    new_n = n;
    memset(h1, -1, sizeof h1);
    memset(h2, -1, sizeof h2);
    while (m -- )
    {
        int k, x, y;
        scanf("%d%d", &k, &x);
        for (int i = 0; i < k - 1; i ++ )
        {
            scanf("%d", &y);
            add(h1, x, y, 1), add(h1, y, x, 1);
            x = y;
        }
    }
    tarjan(1, -1);
    dfs(1);

    printf("%d\n", ans);
    return 0;
}
