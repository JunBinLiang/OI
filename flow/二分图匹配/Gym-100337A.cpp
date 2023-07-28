//start node must in all maximum matching

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
#include <fstream>
#include <iomanip>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}
 

const int N = 2e4 + 100, M = N * 10, INF = 1e8;
int n1, n2, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];

void add(int a, int b, int c)
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

int find(int u, int limit)
{
    if (u == T) return limit;
    int flow = 0;
    for (int i = h[u]; ~i && flow < limit; i = ne[i])
    {
        cur[u] = i;
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



vector<int> g1[N], g2[N];
int vis1[N], vis2[N];

void bfs1(int u) {
    queue<int> q;
    q.push(u);
    while(q.size()) {
        int r = q.front(); q.pop();
        for(int nxt : g1[r]) {
            if(!vis1[nxt]) {
                vis1[nxt] = true;
                q.push(nxt);
            }
        }
    }
}

void bfs2(int u) {
    queue<int> q;
    q.push(u);
    while(q.size()) {
        int r = q.front(); q.pop();
        for(int nxt : g2[r]) {
            if(!vis2[nxt]) {
                vis2[nxt] = true;
                q.push(nxt);
            }
        }
    }
}

ifstream fcin("game.in");
ofstream fcout("game.out");

void solve() { 
  memset(h, -1, sizeof h);
  memset(vis1, 0, sizeof vis1);
  memset(vis2, 0, sizeof vis2);
    
  fcin >> n1 >> n2 >> m;
  
  S = n1 + n2 + 1, T = S + 1;
  
  for(int i = 1; i <= n1; i++) add(S, i, 1);
  for(int i = 1; i <= n2; i++) add(i + n1, T, 1);
  for(int i = 0; i < m; i++) {
      int u, v;
      fcin >> u >> v;
      //cout << u << " " << n1 + v << endl;
      add(u, n1 + v, 1);
  }
  
  int flow = dinic();
  
  for(int i = 0; i < idx; i ++) {
    if(f[i]) {
        int v = e[i], u = e[i ^ 1];
        g1[u].push_back(v);
        g2[v].push_back(u);
    }
  }
  
  bfs1(S);
  bfs2(T);
  
  for(int i = 1; i <= n1; i++) {
      if(vis1[i]) fcout << 'P';
      else fcout << 'N';
  }
  fcout << endl;
  for(int i = 1; i <= n2; i++) {
      if(vis2[n1 + i]) fcout << 'P';
      else fcout << 'N';
  }
  fcout << endl;
} 
    

int main()
{
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}


/*
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
#include <fstream>
#include <iomanip>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}
 

const int N = 2e4 + 100, M = N * 10, INF = 1e8;
int n1, n2, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];

void add(int a, int b, int c)
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

int find(int u, int limit)
{
    if (u == T) return limit;
    int flow = 0;
    for (int i = h[u]; ~i && flow < limit; i = ne[i])
    {
        cur[u] = i;
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



vector<int> g1[N], g2[N];
int vis1[N], vis2[N];

void bfs1(int u) {
    queue<int> q;
    q.push(u);
    while(q.size()) {
        int r = q.front(); q.pop();
        for(int nxt : g1[r]) {
            if(!vis1[nxt]) {
                vis1[nxt] = true;
                q.push(nxt);
            }
        }
    }
}

void bfs2(int u) {
    queue<int> q;
    q.push(u);
    while(q.size()) {
        int r = q.front(); q.pop();
        for(int nxt : g2[r]) {
            if(!vis2[nxt]) {
                vis2[nxt] = true;
                q.push(nxt);
            }
        }
    }
}


vector<vector<int>> ed;
void solve() { 
  freopen("game.in", "r", stdin);
  freopen("game.out", "w", stdout);
    
  memset(h, -1, sizeof h);
  memset(vis1, 0, sizeof vis1);
    
  cin >> n1 >> n2 >> m;
  
  S = n1 + n2 + 1, T = S + 1;
  
  for(int i = 1; i <= n1; i++) add(S, i, 1);
  for(int i = 1; i <= n2; i++) add(i + n1, T, 1);
  for(int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v;
      ed.push_back({u, v});
      add(u, n1 + v, 1);
  }
  
  int flow = dinic();
  
  for(int i = 0; i < idx; i ++) {
    if(f[i]) {
        int v = e[i], u = e[i ^ 1];
        g1[u].push_back(v);
        //g2[v].push_back(u);
    }
  }
  
  bfs1(S);
 // bfs2(T);
  
  for(int i = 1; i <= n1; i++) {
      if(vis1[i]) cout << 'P';
      else cout << 'N';
  }
  cout << endl;
  
  
  for(int i = 0; i < N; i++) g1[i].clear();
  idx = 0;
  memset(h, -1, sizeof h);
  memset(vis1, 0, sizeof vis1);
  for(int i = 1; i <= n2; i++) add(S, i, 1);
  for(int i = 1; i <= n1; i++) add(n2 + i, T, 1);
  for(auto& p : ed) {
      int u = p[0], v = p[1];
      add(v, u + n2, 1);
  }
  
  
  
  
  dinic();
  for(int i = 0; i < idx; i ++) {
    if(f[i]) {
        int v = e[i], u = e[i ^ 1];
        g1[u].push_back(v);
    }
  }
  bfs1(S);
  for(int i = 1; i <= n2; i++) {
      if(vis1[i]) cout << 'P';
      else cout << 'N';
  }
  cout << endl;
} 
    

int main()
{
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}


*/

