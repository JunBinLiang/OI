
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
#define PII pair<long long, int>


template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}


const int N = 1e5 + 100;
const ll INF = 1000000000000000000ll;
int p1[N * 8], p2[N * 8], p3[N]; 
pair<int, int> range[N * 4];
vector<pair<int, int>> g[N * 8];

bool st[N * 4];
ll dist[N * 4];
int idx = 0;

int n, m, S;
void build1(int id, int l, int r) {
    p1[id] = idx++;
    range[id] = {l, r};
    if(l == r) {
        p3[l] =  p1[id];
        return;
    }
    int mid = l + (r - l) / 2;
    int left = id * 2 + 1, right = id * 2 + 2;
    build1(left, l, mid);
    build1(right, mid + 1, r);
    
    g[p1[id]].push_back({p1[left], 0});
    g[p1[id]].push_back({p1[right], 0});
}

void build2(int id, int l, int r) {
    p2[id] = idx++;
    range[id] = {l, r};
    if(l == r) {
        p2[id] = p1[id];
        return;
    }
    int mid = l + (r - l) / 2;
    int left = id * 2 + 1, right = id * 2 + 2;
    build2(left, l, mid);
    build2(right, mid + 1, r);
    g[p2[left]].push_back({p2[id], 0});
    g[p2[right]].push_back({p2[id], 0});
}

void add(int id, int l, int r, int s, int e, int node, int w, int op) { 
  if(l == s && r == e) {
    if(op == 2) {
        g[p3[node]].push_back({p1[id], w});
    } else {
        g[p2[id]].push_back({p3[node], w});
    }
    return;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid) {
    add(left, l, mid, s, e, node, w, op);
  } else if(s >= mid + 1) {
    add(right, mid + 1, r, s, e, node, w, op);
  } else {
    add(left, l, mid, s, mid, node, w, op);
    add(right, mid + 1, r, mid + 1, e, node, w, op);
  }
}


void dijkstra(int start)
{
    for(int i = 0; i < N * 4; i++) {
        dist[i] = INF;
    }
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
        
        for (pair<int, int>& pa : g[ver])
        {
            int j = pa.first, w = pa.second;
            if (dist[j] > dist[ver] + w)
            {
                dist[j] = dist[ver] + w;
                heap.push({dist[j], j});
            }
        }
    }
}



void solve() {
    scanf("%d%d%d", &n, &m, &S);
    build1(0, 0, n);
    build2(0, 0, n);
    
    for(int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);
        if(op == 1) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            g[p3[u]].push_back({p3[v], w});
        } else {
            int v, l, r, w;
            scanf("%d%d%d%d", &v, &l, &r, &w);
            add(0, 0, n, l, r, v, w, op);
        }
    }
    
    dijkstra(p3[S]);
    
    for(int i = 1; i <= n; i++) {
        ll d = dist[p3[i]];
        if(d == INF) cout << -1 << " ";
        else cout << d << " ";
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

