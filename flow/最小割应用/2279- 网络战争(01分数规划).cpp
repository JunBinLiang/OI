#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110, M = 810, INF = 1e8;
const double eps = 1e-8;

int n, m, S, T;
int h[N], e[M], w[M], ne[M], idx;
double f[M];
int q[N], d[N], cur[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
    e[idx] = a, w[idx] = c, ne[idx] = h[b], h[b] = idx ++ ;
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
            if (d[ver] == -1 && f[i] > 0)
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

double find(int u, double limit)
{
    if (u == T) return limit;
    double flow = 0;
    for (int i = cur[u]; ~i && flow < limit; i = ne[i])
    {
        cur[u] = i;
        int ver = e[i];
        if (d[ver] == d[u] + 1 && f[i] > 0)
        {
            double t = find(ver, min(f[i], limit - flow));
            if (t < eps) d[ver] = -1;
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}

double dinic(double mid)
{
    double res = 0;
    for (int i = 0; i < idx; i += 2)
        if (w[i] <= mid)
        {
            res += w[i] - mid;
            f[i] = f[i ^ 1] = 0;
        }
        else f[i] = f[i ^ 1] = w[i] - mid;

    double r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r + res;
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &S, &T);
    memset(h, -1, sizeof h);
    while (m -- )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }

    double l = 0, r = 1e7;
    while (r - l > eps)
    {
        double mid = (l + r) / 2;
        if (dinic(mid) < 0) r = mid;
        else l = mid;
    }

    printf("%.2lf\n", r);
    return 0;
}
