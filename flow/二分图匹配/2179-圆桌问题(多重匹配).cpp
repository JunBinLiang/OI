#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <list>

   
using namespace std;  

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define f first
#define se second
#define W while
#define um unordered_map
#define us unordered_set
#define be begin
#define en end

const int N = 450 , M = N + (300 * 300), INF = 10000000;
int a[160], b[280];
int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];
int tot = 0;

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
    for (int i = h[u]; ~i && flow < limit; i = ne[i])
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

int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    S = 0, T = n + m + 1;
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]), tot += a[i];
    for(int i = 1; i <= m; i++) scanf("%d", &b[i]);
    
    
    for(int i = 1; i <= n; i++) {
        add(S, i, a[i]);
    }
    for(int i = 1; i <= m; i++) {
        add(n + i, T, b[i]);
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            add(i, n + j, 1);
        }
    }
    
    int flow = dinic();
    if(tot != flow) {
        printf("0 \n");
    } else {
        printf("1 \n");
        for(int i = 1; i <= n; i++) {
            for(int j = h[i]; ~j; j = ne[j]) {
                if(!f[j]) {
                    int v = e[j];
                    printf("%d ", v - n);
                }
            }
            printf("\n");
        }
    }
    
    
    return 0;
}

