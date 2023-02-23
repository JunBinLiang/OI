#include <iostream>
#include <cstring>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int N = 510, M = (3000 + N * 2) * 2, INF = 1e8;

int n, m, k, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];
int p[N];
PII edges[3010];

void add(int a, int b, int c1, int c2)
{
    e[idx] = b, f[idx] = c1, ne[idx] = h[a], h[a] = idx ++ ;
    e[idx] = a, f[idx] = c2, ne[idx] = h[b], h[b] = idx ++ ;
}

void build(int k)
{
    memset(h, -1, sizeof h);
    idx = 0;
    for (int i = 0; i < m; i ++ )
    {
        int a = edges[i].x, b = edges[i].y;
        add(a, b, 1, 1);
    }
    for (int i = 1; i <= n; i ++ )
        if (p[i] >= 0)
        {
            if (p[i] >> k & 1) add(i, T, INF, 0);
            else add(S, i, INF, 0);
        }
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

LL dinic(int k)
{
    build(k);
    int r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}

int main()
{
    scanf("%d%d", &n, &m);
    S = 0, T = n + 1;
    for (int i = 0; i < m; i ++ ) scanf("%d%d", &edges[i].x, &edges[i].y);
    scanf("%d", &k);
    memset(p, -1, sizeof p);
    while (k -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        p[a] = b;
    }

    LL res = 0;
    for (int i = 0; i <= 30; i ++ ) res += dinic(i) << i;
    printf("%lld\n", res);

    return 0;
}
