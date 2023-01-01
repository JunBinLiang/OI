#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110, M = 100200 * 2 + 10, INF = 1e8;

int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];
int w[1010], belong[1010];

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
    while (bfs())
    {
        r += find(S, INF);
        flow = find(S, INF);
        if (flow) puts("!");
        r += flow;
    }
    return r;
}

int main()
{
    scanf("%d%d", &m, &n);
    S = 0, T = n + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= m; i ++ ) scanf("%d", &w[i]);
    for (int i = 1; i <= n; i ++ )
    {
        int a, b;
        scanf("%d", &a);
        while (a -- )
        {
            int t;
            scanf("%d", &t);
            if (!belong[t]) add(S, i, w[t]);
            else add(belong[t], i, INF);
            belong[t] = i;
        }
        scanf("%d", &b);
        add(i, T, b);
    }

    printf("%d\n", dinic());
    return 0;
}
