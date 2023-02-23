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
#include<fstream>
 

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector

//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");


const int N = 1e5 + 10, M = 2e5 + 5;
const ll INF = 10000000000000000ll;
int n, m, S, T;
int h[N], e[M], ne[M], idx;
ll f[N];
int q[N], d[N], cur[N];
int a[N];

void add(int a, int b, ll c)
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

ll find(int u, int limit)
{
    if (u == T) return limit;
    ll flow = 0;
    for (int i = cur[u]; ~i && flow < limit; i = ne[i])
    {
        cur[u] = i;
        int ver = e[i];
        if (d[ver] == d[u] + 1 && f[i])
        {
            ll t = find(ver, min(f[i], limit - flow));
            if (!t) d[ver] = -1;
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}

ll dinic()
{
    ll r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}


void solve() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    S = 0;
    T = n + m + 1;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        add(i, T, a[i]);
    }

    ll tot = 0;
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        tot += w;
        add(S, n + i, w);
        add(n + i, u, INF);
        add(n + i, v, INF);
    }
    
    cout << max(0ll, tot - dinic());
} 


int main() {
	// your code goes here
	int t = 1;
	//cin >> t;
	while(t--) {
	    solve();
	}
	return 0;
}  
