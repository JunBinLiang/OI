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
