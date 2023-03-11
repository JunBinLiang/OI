#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>


using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector



const int N = 2010, M = 20010, INF = 1e9;
int h[N], e[M], w[M], ne[M], idx;
int dist[N], q[N];
bool st[N];
int n, m, S, T;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}


struct Edge {
    int a, b, c;
} edges[10010];

void spfa()  // 求1号点到n号点的最短路距离
{
    int hh = 0, tt = 0;
    memset(st, 0, sizeof st);
    for(int i = 0; i < N; i++) {
        dist[i] = INF;
    }
    
    dist[S] = 0;
    q[tt ++ ] = 1;
    st[1] = true;

    while (hh != tt)
    {
        int t = q[hh ++ ];
        if (hh == N) hh = 0;
        st[t] = false;
        
        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                if (!st[j])     // 如果队列中已存在j，则不需要将j重复插入
                {
                    q[tt ++ ] = j;
                    if (tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
}




void solve() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    
    S = 1; T = n;
    
    for(int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        edges[i] = {a, b, c};
    }
    
    int l = 0, r = 1000000;
    int res = -1;
    
    while(l <= r) {
        int mid = l + (r - l) / 2;
        memset(h, -1, sizeof h);
        idx = 0;
        int cnt = 0;
        
        for(int i = 0; i < m; i++) {
            if(edges[i].c > mid) {
                add(edges[i].a, edges[i].b, 1);
                add(edges[i].b, edges[i].a, 1);
            } else {
                add(edges[i].a, edges[i].b, 0);
                add(edges[i].b, edges[i].a, 0);
            }
        }
        
        spfa();
    
        if(dist[T] <= k) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
        
    }
    cout << res << endl;
}



int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
