
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector



template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

typedef pair<long long, int> PII;

const int N = 6e5 + 10, M = N;
const ll INF = 10000000000000000ll;

int h[N], e[M], w[M], ne[M], idx;
ll dist[N];
int q[4 * N];
bool st[N];

int n, m1, k, m2;

void add(int a, int b, int c)  // 添加一条边a->b，边权为c
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void dij()
{
    for(int i = 0; i < N; i++) {
        dist[i] = INF;
    }
    memset(st, 0, sizeof st);

    priority_queue<PII, vector<PII>, greater<PII>> heap;
    for(int i = 1; i <= k; i++) {
        dist[i] = 0;
        heap.push({0, i});
    }

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

struct Edge {
    int u, v;
    ll w;
    bool operator < (const Edge& other) {
        return w < other.w;
    }
} edges[N];

int p[N], rnk[N];
ll f[N];
int find(int u) {
    return p[u] == u ? u : find(p[u]);
}

void solve() {
    memset(h, -1, sizeof h);
    cin >> n >> m1 >> k >> m2;
    for(int i = 0; i < m1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
        edges[i] = {u, v, w};
    }

    dij();
    for(int i = 0; i < m1; i++) {
        edges[i].w += (dist[edges[i].u] + dist[edges[i].v]);
    }

    for(int i = 0; i < N; i++) {
        rnk[i] = 1;
        p[i] = i;
    }
    
    sort(edges, edges + m1);
    for(int i = 0; i < m1; i++) {
        int u = edges[i].u, v = edges[i].v;
        int r1 = find(u), r2 = find(v);
        if(r1 != r2) {
            if(rnk[r1] > rnk[r2]) {
                swap(r1, r2);
            }
            p[r1] = r2;
            f[r1] = edges[i].w;
            
            if(rnk[r1] == rnk[r2]) {
                rnk[r2]++;
            }
        }
    }


    for(int i = 0; i < m2; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        ll res = 0;
        //LCA
        while(u != v) {
            if(rnk[u] > rnk[v]) {
                swap(u, v);
            }
            res = max(res, f[u]);
            u = p[u];
        }
        cout << res << endl;
    }
    
}   


int main()
{   
    int t = 1;
    //cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
