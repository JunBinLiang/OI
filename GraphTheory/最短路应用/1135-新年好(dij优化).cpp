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



const int N = 50010, M = 2e5 + 10, INF = 1e9;
int pos[6];

int n, m;
int h[N], e[M], w[M], ne[M], idx;
int dist[6][N], q[4 * N];
bool st[N];

typedef pair<int, int> PII;

void add(int a, int b, int c)  // 添加一条边a->b，边权为c
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void dijkstra(int start, int dist[])
{
    memset(dist, 0x3f, N * 4);
    dist[start] = 0;
    memset(st, 0, sizeof st);

    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, start});

    while (heap.size())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.second;
        if (st[ver]) continue;
        st[ver] = true;

        for (int i = h[ver]; ~i; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[ver] + w[i])
            {
                dist[j] = dist[ver] + w[i];
                heap.push({dist[j], j});
            }
        }
    }
}

void solve() {
    memset(h, -1, sizeof h);
    memset(st, false, sizeof st);
    
    scanf("%d%d", &n, &m);
    
    pos[0] = 1;
    for(int i = 1; i <= 5; i++) {
        scanf("%d", &pos[i]);
    }
    
    int a, b, c;
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
        add(b, a, c);
    }
    
    for(int i = 0; i <= 5; i++) {
        dijkstra(pos[i], dist[i]);
    }
    
    int cnt = 0;
    vector<int> per = {1, 2, 3, 4, 5};
    int res = INF;
    do {  
        int last = 0;
        int sum = 0;
        for(int i = 0; i < per.size(); i++) {
            sum += dist[last][pos[per[i]]];
            last = per[i];
        }    
        res = min(res, sum);
    } while(next_permutation(per.begin(), per.end())); 
    printf("%d\n", res);
}



int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
