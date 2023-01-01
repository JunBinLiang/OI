#include <iostream>
#include <cstring>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 210, M = 20410, INF = 1e8;
const double eps = 1e-8;

int n, S, T;
double D;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];
PII p[N];

bool check(PII a, PII b)
{
    double dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy < D * D + eps;
}

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
    int cases;
    scanf("%d", &cases);
    while (cases -- )
    {
        memset(h, -1, sizeof h);
        idx = 0;
        scanf("%d%lf", &n, &D);
        S = 0;

        int tot = 0;
        for (int i = 1; i <= n; i ++ )
        {
            int x, y, a, b;
            scanf("%d%d%d%d", &x, &y, &a, &b);
            p[i] = {x, y};
            add(S, i, a);
            add(i, n + i, b);
            tot += a;
        }

        for (int i = 1; i <= n; i ++ )
            for (int j = i + 1; j <= n; j ++ )
                if (check(p[i], p[j]))
                {
                    add(n + i, j, INF);
                    add(n + j, i, INF);
                }

        int cnt = 0;
        for (int i = 1; i <= n; i ++ )
        {
            T = i;
            for (int j = 0; j < idx; j += 2) //还原
            {
                f[j] += f[j ^ 1];
                f[j ^ 1] = 0;
            }
            if (dinic() == tot)
            {
                printf("%d ", i - 1);
                cnt ++ ;
            }
        }
        if (!cnt) puts("-1");
        else puts("");
    }

    return 0;
}
