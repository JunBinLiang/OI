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

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int N = 200010, M = N * 16, INF = 1e9;

int n, m, new_n;
int h1[N], h2[N], e[M], w[M], ne[M], idx;
int dfn[N], low[N], cnt;
int fu[N], fw[N], fe[N];
int prefix[2 * N], sums[2 * N];
int sub[2 * N], d[2 * N];
ll res = 0;

void add(int h[], int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void build(int x, int y, int z) {
  int sum = z;
  for(int k = y; k != x; k = fu[k]) {
    prefix[k] = sum;
    sum += fw[k];
  }
  prefix[x] = sums[x] = sum;
  new_n++;
  add(h2, x, new_n, 0);
  for(int k = y; k != x; k = fu[k]) {
    sums[k] = sum;
    add(h2, new_n, k, min(prefix[k], sum - prefix[k]));
  }
}

void tarjan(int u, int from)
{
    dfn[u] = low[u] = ++ cnt;
    for (int i = h1[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            fu[j] = u, fw[j] = w[i], fe[j] = i;
            tarjan(j, i);
            low[u] = min(low[u], low[j]);
            if (dfn[u] < low[j]) add(h2, u, j, w[i]); //bridge
        }
        else if (i != (from ^ 1)) {
          low[u] = min(low[u], dfn[j]);
        }
    }
    
    for (int i = h1[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (dfn[u] < dfn[j] && fe[j] != i) {
              build(u, j, w[i]);
        }
    }
}

int dfs(int u) {
   sub[u] = (u <= n ? 1 : 0);
   for(int i = h2[u]; ~i; i = ne[i]) {
       int j = e[i];
       sub[u] += dfs(j);
   } 
   
   if(u <= n) { //real node
        for(int i = h2[u]; ~i; i = ne[i]) {
          int j = e[i];
          if(w[i]) {
              res += ((sub[j] + 0ll) * (n - sub[j]));
          }
       }
   } else { //virtual node
      int sz = 0;
      d[sz++] = u;
      for(int i = h2[u]; ~i; i = ne[i]) {
          int j = e[i];
          res += ((sub[j] + 0ll) * (n - sub[u]) * w[i]);
          d[sz ++ ] = j;
      }
      
      int temp = sub[u];
      sub[u] = 0;
      
      for (int i = 0; i < sz; i ++ ) d[sz + i] = d[i]; //flatten the circle
      ll addTot = 0;

      int k = sz / 2;
      ll presum = 0;
      ll tot = 0;
      for(int i = 0, j = 0; i < sz * 2; i++) {
        if(d[i] != u && i >= sz) {
          ll add = tot * sub[d[i]];
          addTot += add;
        }
        
        presum += sub[d[i]];
        tot += presum;
        if(i >= k) {
          presum -= sub[d[j]];
          tot -= ((sub[d[j]] + 0ll) * (i - j + 1));
          j++;
        }
      }

      presum = 0;
      tot = 0;
      if(sz % 2 == 0) k--;
      int c = 0;
      for(int i = sz * 2 - 1, j = sz * 2 - 1; i >= 1; i--) {
        c++;
        if(d[i] != u && i < sz) {
          ll add = tot * sub[d[i]];
          addTot += add;
        }
        
        presum += sub[d[i]];
        tot += presum;
        if(c > k) {
          presum -= sub[d[j]];
          tot -= ((sub[d[j]] + 0ll) * (j - i + 1));
          j--;
        }
      }
      
      res += (addTot / 2);
      sub[u] = temp;
   }
   
   return sub[u];
}

int main()
{
    scanf("%d%d", &n, &m);
    new_n = n + 1;
    memset(h1, -1, sizeof h1);
    memset(h2, -1, sizeof h2);
    memset(sub, 0, sizeof sub);
    
    while (m -- )
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(h1, u, v, 1); add(h1, v, u, 1);
    }
    
    tarjan(1, -1); 
    dfs(1);
    cout << res << endl;
    return 0;
}

