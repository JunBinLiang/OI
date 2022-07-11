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

int INF = 1000000000;
int res = 1000000000;
int n, m;
const int N = 205, M = 205 * 205;
int levels[N];
int a[N]; 
int q[N], dist[N];
bool st[N];

int h[N], e[M], w[M], ne[M], idx;
void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}


void spfa(int l1, int l2) {
    int hh = 0, tt = 1;
    memset(st, false, sizeof(st));
    for(int i = 0; i <= n; i++) {
        dist[i] = INF;
    }
    q[0] = 0;
    dist[0] = 0;
    st[0] = true;
    
    while(hh != tt) {
      int root = q[hh++];
      if(hh == N) hh = 0;
      st[root] = false;
      for (int i = h[root]; ~i; i = ne[i])
      {
        int j = e[i];
        int weight = w[i];
        
        if ((levels[j] >= l1 && levels[j] <= l2) && dist[j] > dist[root] + weight)
        {
            dist[j] = dist[root] + weight;
            if (!st[j])
            {
              q[tt ++ ] = j;
              if (tt == N) tt = 0;
              st[j] = true;
            }
        }
      }
    }
    res = min(res, dist[1]);
}

int main() {
    cin >> m >> n;
    memset(h, -1, sizeof(h));
    for(int i = 1; i <= n; i++) {
        int P, L, X;
        cin >> P >> L >> X;
        add(0, i, P);
        levels[i] = L; a[i] = P;
        for(int j = 0; j < X; j++) {
            int a, w;
            cin >> a >> w;
            add(a, i, w);
        }
    }
    
    for (int i = levels[1] - m; i <= levels[1]; i ++ ) {
        spfa(i, i + m);
    }
    
    cout << res << endl;
}
