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





const int N = 10010, M = N * 2;
int n, m;
int h[N], e[M], w[M], ne[M], idx;
bool st[N];
int p[N], q[N];

void add(int a, int b, int c)
{
  e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

int get_size(int u, int fa)  // 求子树大小
{
    if (st[u]) return 0;
    int res = 1;
    for (int i = h[u]; ~i; i = ne[i])
        if (e[i] != fa) {
            res += get_size(e[i], u);
        }
            
    return res;
}

void get_dist(int u, int fa, int dist, int& qt)
{
    if (st[u]) return;
    q[qt ++ ] = dist;
    for (int i = h[u]; ~i; i = ne[i]) {
        if (e[i] != fa) {
            get_dist(e[i], u, dist + w[i], qt);
        }
    }
}

int get(int a[], int k)
{
    sort(a, a + k);
    int res = 0;
    int l = 0, r = k - 1;
    while(l < r) {
        if(a[l] + a[r] <= m) {
            res += (r - l);
            l++;
        } else {
            r--;
        }
    }
    
    return res;
}

int get_wc(int fa, int u, int tot, int& wc)  // 求重心
{
    if (st[u]) return 0;
    int sum = 1, ms = 0;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == fa) continue;
        int t = get_wc(u, j, tot, wc);
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
    int res = 0;
    get_wc(-1, u, get_size(u, -1), u);
    st[u] = true;  // 删除重心

    int pt = 0;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i], qt = 0;
        get_dist(j, -1, w[i], qt);
        res -= get(q, qt);
        for (int k = 0; k < qt; k ++ )
        {
            if (q[k] <= m) res ++ ;
            p[pt ++ ] = q[k];
        }
    }
    res += get(p, pt);
    for (int i = h[u]; ~i; i = ne[i]) res += calc(e[i]);
    return res;
}


void solve() {
  while (scanf("%d%d", &n, &m), n || m)
  {
      memset(st, 0, sizeof st);
      memset(h, -1, sizeof h);
      idx = 0;
      for (int i = 0; i < n - 1; i ++ ) {
          int a, b, c;
          scanf("%d%d%d", &a, &b, &c);
          add(a, b, c), add(b, a, c);
      }
      printf("%d\n", calc(0));
    }

}


int main()
{
  int t = 1;
  W (t--)
  {
    solve();
  }
  return 0;
}
