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
typedef pair<int, int> PII;

const int N = 1e5 + 10, M = 1e6 + 10, INF = 1e9;
int a[N];
int n, m, S, T;

int h[N], e[M], w[M], ne[M], idx;
int dist1[N], dist2[N];
bool st[N];

struct Edge {
    int a, b, c;
} edges[500000 + 10];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dijkstra1()  // 求1号点到n号点的最短路距离
{
    for(int i = 0; i < N; i++) dist1[i] = INF;
    
    dist1[S] = a[S];
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({a[S], S});

    while (heap.size())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.second, distance = t.first;

        if (distance != dist1[ver]) continue;

        for (int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (dist1[j] > min(dist1[ver], a[j]))
            {
                dist1[j] = min(dist1[ver], a[j]);
                heap.push({dist1[j], j});
            }
        }
    }
}

void dijkstra2() //反方向最大值
{
    memset(dist2, 0, sizeof dist2);
    dist2[T] = a[T];
    priority_queue<PII> heap;
    heap.push({a[T], T});
    
    while (heap.size())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.second, distance = t.first;

        if (distance != dist2[ver]) continue;

        for (int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (dist2[j] < max(dist2[ver], a[j]))
            {
                dist2[j] = max(dist2[ver], a[j]);
                heap.push({dist2[j], j});
            }
        }
    }
}



void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    S = 1; T = n;
    memset(h, -1, sizeof h);
    
    for(int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        edges[i] = {a, b, c};
        add(a, b);
        if(c == 2) add(b, a);
    }
    
    dijkstra1();
    
    memset(h, -1, sizeof h);
    idx = 0;
    for(int i = 0; i < m; i++) {
        int a = edges[i].a, b = edges[i].b, c = edges[i].c;
        add(b, a);
        if(c == 2) add(a, b);
    }
    
    dijkstra2();
    
    
    int res = 0;
    for(int i = 1; i <= n; i++) {
        res = max(res, dist2[i] - dist1[i]);
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
