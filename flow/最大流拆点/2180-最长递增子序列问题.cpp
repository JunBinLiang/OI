#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010, M = 251010, INF = 1e8;

int n, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];
int g[N], w[N];

void add(int a, int b, int c)
{
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx ++ ;
}

bool bfs()
{
    int hh = 0, tt = 0;
    memset(d, -1, sizeof d);
    q[0] = S, d[S] = 0, cur[S] = h[S];
    while (hh <= tt)
    {
        int t = q[hh ++ ];
        for (int i = h[t]; ~i; i = ne[i])
        {
            int ver = e[i];
            if (d[ver] == -1 && f[i])
            {
                d[ver] = d[t] + 1;
                cur[ver] = h[ver];
                if (ver == T) return true;
                q[ ++ tt] = ver;
            }
        }
    }
    return false;
}

int find(int u, int limit)
{
    if (u == T) return limit;
    int flow = 0;
    for (int i = cur[u]; ~i && flow < limit; i = ne[i])
    {
        cur[u] = i;
        int ver = e[i];
        if (d[ver] == d[u] + 1 && f[i])
        {
            int t = find(ver, min(f[i], limit - flow));
            if (!t) d[ver] = -1;
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}

int dinic()
{
    int r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}

int main()
{
    scanf("%d", &n);
    S = 0, T = n * 2 + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);
    int s = 0;
    for (int i = 1; i <= n; i ++ )
    {
        add(i, i + n, 1);
        g[i] = 1;
        for (int j = 1; j < i; j ++ )
            if (w[j] <= w[i])
                g[i] = max(g[i], g[j] + 1);
        for (int j = 1; j < i; j ++ )
            if (w[j] <= w[i] && g[j] + 1 == g[i])
                add(n + j, i, 1);
        s = max(s, g[i]);
        if (g[i] == 1) add(S, i, 1);
    }

    for (int i = 1; i <= n; i ++ )
        if (g[i] == s)
            add(n + i, T, 1);

    printf("%d\n", s);
    if (s == 1) printf("%d\n%d\n", n, n);
    else
    {
        int res = dinic();
        printf("%d\n", res);
        for (int i = 0; i < idx; i += 2)
        {
            int a = e[i ^ 1], b = e[i];
            if (a == S && b == 1) f[i] = INF;
            else if (a == 1 && b == n + 1) f[i] = INF;
            else if (a == n && b == n + n) f[i] = INF;
            else if (a == n + n && b == T) f[i] = INF;
        }
        printf("%d\n", res + dinic());
    }

    return 0;
}
