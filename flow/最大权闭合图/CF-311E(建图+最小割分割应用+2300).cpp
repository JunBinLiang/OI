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


const int N = 1e5 + 10, M = 4e5 + 5;
const ll INF = 1000000000000ll;

int n, m, g, S, T;
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

ll find(int u, ll limit)
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


ll tot = 0;
void solve() {
    scanf("%d%d%d", &n, &m, &g);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    S = 0; 
    T = n + m + 1;
    memset(h, -1, sizeof h);
    
    for(int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        if(a[i] == 0) {
            add(S, i, x);
        } else {
            add(i, T, x);
        }
    }

    for(int i = 1; i <= m; i++) {
        int ty, w, t;
        scanf("%d%d%d", &ty, &w, &t);
        tot += w;
        while(t--) {
            int j;
            scanf("%d", &j);
            if(ty == 0) {
                //假设需求是0
                //如果要满足此要求
                //保证需求的1在另一边，保证需求的0在同一边
                if(a[j] == 1) {
                    add(i + n, j, INF);
                } else {
                    add(i + n, j, INF);
                }
            } else {
                if(a[j] == 0) {
                    add(j, i + n, INF);
                } else {
                    add(j, i + n, INF);
                }
            }
        }

        int is;
        scanf("%d", &is);
        if(is == 1) {
            w += g;
        } 
        
        if(ty == 0) {
            add(S, i + n, w);
        } else {
            add(i + n, T, w);
        }
        
    }
    
    cout << tot - dinic() << endl;
    
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
