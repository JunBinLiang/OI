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

int n, m, k, S, T;
const int N = 230, M = 1e5, INF = 1e8;
int h[N], e[M], f[M],w[M], ne[M], idx;
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


bool check(int mid) {
    for(int i = 0; i < idx; i++) {
        if(w[i] > mid) {
            f[i] = 0;
        } else {
            f[i] = 1;
        }
    }
    int flow = dinic();
    return flow >= k;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    memset(h, -1, sizeof h);
    S = 1, T = n;
    for(int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }
    
    int l = 1, r = 1e6;
    int res = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(check(mid)) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    printf("%d\n", res);
    return 0;
}
