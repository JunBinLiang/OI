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


int n, m, S, T;
const int N = 2010, M = 400000 + 10;
int h[N], e[M], ne[M], idx;
double w[M];
int q[N];
double dist[N];
bool st[N];

void add(int a, int b, double c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void spfa()
{
    memset(dist, 0, sizeof(dist));
    dist[S] = 1;

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
          if (dist[j] < dist[root] * w[i])
          {
            dist[j] = dist[root] * w[i];
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
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    while(m--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        double z = (100.0 - c) / 100;
        add(a, b, z);
        add(b, a, z);
    }


    scanf("%d%d", &S, &T);
    spfa();
    
    printf("%.8lf\n", 100 / dist[T]);
}



int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}


/*
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2010;

int n, m, S, T;
double g[N][N];
double dist[N];
bool st[N];

void dijkstra()
{
    dist[S] = 1;
    for (int i = 1; i <= n; i ++ )
    {
        int t = -1;
        for (int j = 1; j <= n; j ++ )
            if (!st[j] && (t == -1 || dist[t] < dist[j]))
                t = j;
        st[t] = true;

        for (int j = 1; j <= n; j ++ )
            dist[j] = max(dist[j], dist[t] * g[t][j]);
    }
}

int main()
{
    scanf("%d%d", &n, &m);

    while (m -- )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        double z = (100.0 - c) / 100;
        g[a][b] = g[b][a] = max(g[a][b], z);
    }

    cin >> S >> T;

    dijkstra();

    printf("%.8lf\n", 100 / dist[T]);

    return 0;
}

*/
