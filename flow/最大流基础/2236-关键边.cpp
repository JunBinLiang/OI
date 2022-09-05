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

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int N = 600, M = 30000, INF = 100000000;
int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];

void add(int a, int b, int c)
{
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx ++ ;
}

void bfsGo1(vector<bool>&is, int s) {
    is[s] = true;
    int hh = 0, tt = 0;
    memset(d, -1, sizeof d);
    q[0] = s, d[S] = 0;
    while (hh <= tt)
    {
        int t = q[hh ++ ];
        for (int i = h[t]; ~i; i = ne[i])
        {
            int ver = e[i];
            if (d[ver] == -1 && f[i])
            {
                is[ver] = true;
                d[ver] = d[t] + 1;
                q[++ tt] = ver;
            }
        }
    }
}

void bfsGo2(vector<bool>&is, int s) {
    is[s] = true;
    int hh = 0, tt = 0;
    memset(d, -1, sizeof d);
    q[0] = s, d[S] = 0;
    while (hh <= tt)
    {
        int t = q[hh ++ ];
        for (int i = h[t]; ~i; i = ne[i])
        {
            int ver = e[i];
            if (d[ver] == -1 && f[i ^ 1])
            {
                is[ver] = true;
                d[ver] = d[t] + 1;
                q[++ tt] = ver;
            }
        }
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
                if (ver == T)  return true;
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
        cur[u] = i;  // 当前弧优化
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
    S = 0, T = n - 1;
    for(int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }
    
    dinic();
    vector<bool> is1(n);
    vector<bool> is2(n);
    bfsGo1(is1, S);
    bfsGo2(is2, T);
    
    
    int res = 0;
    for(int i = 0; i < m * 2; i += 2) {
        int u = e[i ^ 1], v = e[i];
        if(is1[u] && is2[v] && !f[i]) {
            res ++;
        }
    } 
    printf("%d\n", res);
    return 0;
}
