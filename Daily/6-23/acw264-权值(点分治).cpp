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



bool COMP(ve<int>& a, ve<int>& b) {
  return a[0] < b[0];
}

const int N = 200000 + 10, M = N * 2;
int n, m;
int h[N], e[M], w[M], ne[M], idx;
bool st[N];
pair<int, int> p[N], q[N];
int INF = 1000000000;
int res = INF;
int f[1000000 + 100];

void add(int a, int b, int c)
{
  e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

int get_size(int u, int fa)  // 求子树大小
{
    if (st[u]) return 0;
    int res = 1;
    for (int i = h[u]; ~i; i = ne[i])
        if (e[i] != fa)
            res += get_size(e[i], u);
    return res;
}

void get_dist(int u, int fa, int dist, int cnt, int& qt)
{
    if (st[u]) return;
    q[qt ++ ] = {dist, cnt};
    for (int i = h[u]; ~i; i = ne[i])
        if (e[i] != fa)
            get_dist(e[i], u, dist + w[i], cnt + 1, qt);
}

int get_wc(int u, int fa, int tot, int& wc)  // 求重心
{
    if (st[u]) return 0;
    int sum = 1, ms = 0;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == fa) continue;
        int t = get_wc(j, u, tot, wc);
        ms = max(ms, t);
        sum += t;
    }
    ms = max(ms, tot - sum);
    if (ms <= tot / 2) wc = u;
    return sum;
}


int calc(int u)
{
    if (st[u]) return 0;
    get_wc(u, -1, get_size(u, -1), u);
    st[u] = true;  // 删除重心
    
    int pt = 0;
    for(int i = h[u]; ~i; i = ne[i]) {
      int j = e[i]; int qt = 0;
      get_dist(j, u, w[i], 1, qt);
      for(int k = 0; k < qt; k++) {
        auto& pa = q[k];
        if(pa.first == m) res = min(res, pa.second);
        p[pt ++] = pa;
        if(pa.first <= m) {
            res = min(res, f[m - pa.first] + pa.second); 
        }
      }
      
      for(int k = 0; k < qt; k++) {
          auto& pa = q[k];
          if(pa.first <= 1000000) {
              f[pa.first] = min(f[pa.first], pa.second);
          }
      }
    }
    
    for(int i = 0; i < pt; i++) {
      if(p[i].first <= 1000000) f[p[i].first] = INF;  
    }
    for (int i = h[u]; ~i; i = ne[i]) calc(e[i]);
}


void solve() {
  scanf("%d%d", &n, &m);
  memset(st, 0, sizeof st);
  memset(h, -1, sizeof h);
  idx = 0;
  
  for(int i = 0; i < 1000000 + 5; i++) {
    f[i] = INF;
  }

  for (int i = 0; i < n - 1; i ++ ) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    add(a, b, c), add(b, a, c);
  }
  calc(0);
  res = ((res == INF) ? -1 : res);
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
