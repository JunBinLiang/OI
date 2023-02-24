#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 5010, M = (50000 + N * 2) * 2 + 10, INF = 1e8;

int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];
int dg[N], p[N];

void add(int a, int b, int c1, int c2)
{
    e[idx] = b, f[idx] = c1, ne[idx] = h[a], h[a] = idx ++ ;
    e[idx] = a, f[idx] = c2, ne[idx] = h[b], h[b] = idx ++ ;
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
    scanf("%d%d", &n, &m);
    S = 0, T = n + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &p[i]), p[i] *= -1;
    while (m -- )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c, c);
        dg[a] += c, dg[b] += c;
    }
    int U = 0;
    for (int i = 1; i <= n; i ++ ) U = max(U, 2 * p[i] + dg[i]);
    for (int i = 1; i <= n; i ++ )
    {
        add(S, i, U, 0);
        add(i, T, U - 2 * p[i] - dg[i], 0);
    }

    printf("%d\n", (U * n - dinic()) / 2);

    return 0;
}

