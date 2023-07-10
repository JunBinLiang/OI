#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
 
using ll = long long;
using namespace std;


const int N = 5050, M = 1e6 + 10010, MOD = 1e9 + 7;
char s[N], str[M];
ll dp[N];


int tr[M][26], cnt[M], sz[M], idx;
int q[M], ne[M];
void insert(int len)
{
  int p = 0;
  for (int i = 0; i < len; i ++ )
  {
    int t = str[i] - 'a';
    if (!tr[p][t]) tr[p][t] = ++ idx;
    p = tr[p][t];
    sz[p] = i + 1;
  }
  cnt[p] ++ ;
}

void build()
{
  int hh = 0, tt = -1;
  for (int i = 0; i < 26; i ++ )
    if (tr[0][i])
      q[ ++ tt] = tr[0][i];

    while (hh <= tt)
    {
      int t = q[hh ++ ];
      for (int i = 0; i < 26; i ++ )
      {
        int p = tr[t][i];
        if (!p) tr[t][i] = tr[ne[t]][i];
        else
        {
          ne[p] = tr[ne[t]][i];
          q[ ++ tt] = p;
        }
    }
  }
}


void solve() {
  memset(dp, 0, sizeof dp);
  memset(cnt, 0, sizeof cnt);
  memset(sz, 0, sizeof sz);

  scanf("%s", str);
  int n = strlen(str);
  insert(n);

  for(int i = 0; i < n; i++) {
    s[i + 1] = str[i];
  }


  int m;
  cin >> m;
  while(m--) {
    scanf("%s", str);
    int len = strlen(str);
    insert(len);
  }
  build();


  dp[0] = 1;
  int u = 0;
  for(int i = 1; i <= n; i++) {
    int d = s[i] - 'a';
    u = tr[u][d];
    int p = u;
    while(p) {
      if(i - sz[p] >= 0) {
        dp[i] += (cnt[p] + 0ll) * dp[i - sz[p]];
        dp[i] %= MOD;
      }
      p = ne[p];
    }
  }
  
  cout << dp[n] - 1 << endl; 
}

int main() {
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
