#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1101 * 50 + 10, M = (N + 1100 + 20 * 1101) + 10, INF = 1e8;

int n, m, k, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];
struct Ship
{
    int h, r, id[30];
}ships[30];
int p[30];

int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int get(int i, int day) //ith node, which day
{
    return day * (n + 2) + i;
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
    scanf("%d%d%d", &n, &m, &k);
    S = N - 2, T = N - 1;
    memset(h, -1, sizeof h);
    for (int i = 0; i < 30; i ++ ) p[i] = i;
    for (int i = 0; i < m; i ++ )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        ships[i] = {a, b};
        for (int j = 0; j < b; j ++ )
        {
            int id;
            scanf("%d", &id);
            if (id == -1) id = n + 1;
            ships[i].id[j] = id;
            if (j)
            {
                int x = ships[i].id[j - 1];
                int r1 = find(x), r2 = find(id);
                if(r1 != r2) {
                    p[r1] = r2;
                }
            }
        }
    }
    if (find(0) != find(n + 1)) puts("0");
    else
    {
        add(S, get(0, 0), k);
        add(get(n + 1, 0), T, INF);
        int day = 1, res = 0;
        while (true)
        {
            add(get(n + 1, day), T, INF);
            for (int i = 0; i <= n + 1; i ++ ) //stay on the same position for a day
            {
                add(get(i, day - 1), get(i, day), INF);
            }
            for (int i = 0; i < m; i ++ )
            {
                int r = ships[i].r;
                int a = ships[i].id[(day - 1) % r], b = ships[i].id[day % r];
                add(get(a, day - 1), get(b, day), ships[i].h);
            }
            res += dinic();
            if (res >= k) break;
            day ++ ;
        }

        printf("%d\n", day);
    }

    return 0;
}
