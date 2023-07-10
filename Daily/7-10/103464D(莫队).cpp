#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
 
using ll = long long;
using namespace std;


const int N = 1e7 + 5, M = 1e5 + 5, MOD = 1e9 + 7;
vector<pair<int, int>> d[N];

bool vis[N], has[N];
vector<int> p[N];


int cnt[N], oldCnt[N], a[M], modify[N];
int idx = 0;
int res[M], inv[M * 24 + 1];
ll ans = 1;

int n, m, len;

struct Query
{
    int id, l, r;
} q[M];

void add(int i) {
  auto& v = d[a[i]];
  for(auto& pi : v) {
    int& x = pi.first; int& c = pi.second;
    if(oldCnt[x] == 0) {
      oldCnt[x] = cnt[x];
      modify[idx++] = x;
    }
    cnt[x] += c;
  }
}

void del(int i) {
  auto& v = d[a[i]];
  for(auto& pi : v) {
    int& x = pi.first; int& c = pi.second;
    if(oldCnt[x] == 0) {
      oldCnt[x] = cnt[x];
      modify[idx++] = x;
    }
    cnt[x] -= c;
  }
}

bool cmp(const Query& a, const Query& b)
{
  int i = a.l / len, j = b.l / len;
  if (i != j) return i < j;
  return a.r < b.r;
}

void init() {
  cnt[0] = cnt[1] = 1;
  oldCnt[0] = oldCnt[1] = 0;
  for(int i = 2; i < N; i++) {
    cnt[i] = 1;
    oldCnt[i] = 0;
    if(vis[i]) continue;
    for(int j = i; j < N; j += i) {
      vis[j] = true;
      if(has[j]) {
        p[j].push_back(i);
      }
    }
  }

  inv[1] = 1;
  for (int i = 2; i <= M * 24; ++i) {
    inv[i] = ((MOD - MOD / i + 0ll) * inv[MOD % i]) % MOD;
  }
}

void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
      has[a[i]] = true;
    }
    init();
    
    //质因数分解
    for(int i = 1; i <= n; i++) {
      int v = a[i];
      if(d[v].size() > 0) continue;
      int sz = p[v].size();
      d[v].reserve(sz);
      for(int j = 0; j < sz; j++) {
        int pri = p[a[i]][j];
        int c = 0;
        while(v % pri == 0) {
          v /= pri;
          c++;
        }
        d[a[i]].push_back({pri, c});
      }
    }

    //Mo algorithm
    len = max(1, (int)(sqrt(n)));
    for (int i = 0; i < m; i ++ )
    {
        int l, r;
        scanf("%d%d", &l, &r);
        q[i] = {i, l, r};
    }
    
    sort(q, q + m, cmp);
    for (int k = 0, i = 0, j = 1; k < m; k ++ ) {
      int& id = q[k].id; int& l = q[k].l; int& r = q[k].r;
      while (i < r) {
          add(++i);
      }
      while (i > r) {
          del(i--);
      }
      while (j < l) {
          del(j++);
      }
      while (j > l) {
          add(--j);  
      }

      for(int j = 0; j < idx; j++){
        int x = modify[j];
        if(oldCnt[x] > 1) {
          ans *= inv[oldCnt[x]];
          ans %= MOD;
        }
        if(cnt[x] > 1) {
          ans *= cnt[x];
          ans %= MOD;
        }
        oldCnt[x] = 0;
      }
      idx = 0;
      res[id] = ans;
    }

    for(int i = 0; i < m; i++) {
      printf("%d\n", res[i]);
    }
}

int main() {
  ios::sync_with_stdio(false);
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
