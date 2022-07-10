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




const int N = 2510, M = 6200 * 2 + 10;
int INF = 1000000000;
int n, m, S, T;
int h[N], e[M], w[M], ne[M], idx;
int dist[N], q[N];
bool st[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void spfa()
{
    
    for(int i = 0; i < N; i++) {
        dist[i] = INF;
    }
    
    dist[S] = 0;

    int hh = 0, tt = 1;
    q[0] = S, st[S] = true;

    while (hh != tt)
    {
      int root = q[hh ++];
      if(hh == N) hh = 0;
      st[root] = false;

      for (int i = h[root]; ~i; i = ne[i])
      {
          int j = e[i];
          if (dist[j] > dist[root] + w[i])
          {
            dist[j] = dist[root] + w[i];
            if (!st[j])
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
    cin >> n >> m;
    S = 1;
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; i ++ )
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }

    spfa();
    int res = 0;
    for(int i = 1; i <= n; i++) {
        res = max(res, dist[i]);
    }
    if(res == INF) res = -1;
    cout << res << endl;
}


int main()
{

  int t = 1;
  //cin >> t;
  W (t--)
  { 
    solve();
  }
  return 0;
}
