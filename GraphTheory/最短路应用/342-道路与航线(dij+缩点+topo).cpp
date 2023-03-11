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



const int N = 25000 + 100, M = 2e5 + 10, INF = 1e9;
int h[N], e[M], w[M], ne[M], idx;
int dist[N];
int ids[N], in[N];
bool st[N], is[N];
vector<int> com[N];
pair<int, int> edges[50010];
queue<int> q;
int n, m1, m2, S, T;


void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}


void dfs(int root, int c) {
    ids[root] = c;
    com[c].push_back(root);
    for(int i = h[root]; ~i; i = ne[i]) {
        int j = e[i];
        if(!ids[j]) {
            dfs(j, c);
        }
    }
}

void dfs1(int root) {
    is[root] = true;
    for(int i = h[root]; ~i; i = ne[i]) {
        int j = e[i];
        if(!is[j]) {
            dfs1(j);
        }
    }
}

void dijkstra(int id)  // 求1号点到n号点的最短路距离
{
    
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    for(int u : com[id]) {
        heap.push({dist[u], u});
    }    
    
    while (heap.size())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.second, distance = t.first;

        if (st[ver]) continue;
        st[ver] = true;

        for (int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i];
            
            if(ids[ver] != ids[j]) {
                in[ids[j]]--;
                dist[j] = min(dist[j], dist[ver] + w[i]);
                if(in[ids[j]] == 0) {
                    q.push(ids[j]);
                }
                
            } else {
                if (dist[j] > dist[ver] + w[i])
                {
                    dist[j] = dist[ver] + w[i];
                    heap.push({dist[j], j});
                }
            }
        }
    }
}


void topo()
{
    q.push(ids[S]);
    dist[S] = 0;
    while(q.size()) {
        int top = q.front(); q.pop();
        dijkstra(top);
    }
}



void solve() {
    scanf("%d%d%d%d", &n, &m1, &m2, &S);
    
    
    memset(is, false, sizeof is);
    memset(st, false, sizeof st);
    
    memset(h, -1, sizeof h);
    memset(ids, 0, sizeof ids);
    memset(in, 0, sizeof in);
    
    for(int i = 0; i < N; i++) {
        dist[i] = INF;
    }
    
    
    for(int i = 0; i < m1; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        //undirect
        add(a, b, c);
        add(b, a, c);
    }
    
    int id = 1;
    for(int i = 1; i <= n; i++) {
        if(!ids[i]) {
            dfs(i, id);
            id++;
        }
    }
    
    
    for(int i = 0; i < m2; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        //direct
        add(a, b, c);
        edges[i] = {a, b};
        in[ids[b]]++;
    }
    
    dfs1(S);
    
    for(int i = 0; i < m2; i++) {
        int a = edges[i].first, b = edges[i].second;
        if(!is[a]) {
            in[ids[b]]--;
        }
    }
    
    topo();
    
    for(int i = 1; i <= n; i++) {
        if(!is[i]) {
            cout << "NO PATH" <<  endl;
        } else {
            cout << dist[i] << endl;
        }
    }
    
}



int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
