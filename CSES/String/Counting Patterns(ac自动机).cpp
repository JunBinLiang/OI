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
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
using namespace std;
 
 

const int N = 5e5 + 10;
char s[N], t[N];
int n, m;

int tr[N][26], idx;
int q[N], ne[N];
int ids[N], in[N]; ll cnt[N];
vector<int> g[N];

void insert(int j)
{
    int p = 0;
    int len = strlen(t);
    for (int i = 0; i < len; i ++ )
    {
        int c = t[i] - 'a';
        if (!tr[p][c]) tr[p][c] = ++ idx;
        p = tr[p][c];
    }
    ids[j] = p;
    
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
                in[ne[p]]++;
                g[p].push_back(ne[p]);
                q[ ++ tt] = p;
            }
        }
    }
}

void topo() {
    queue<int> q;
    for(int i = 0; i <= idx; i++) {
        if(!in[i]) q.push(i);
    }
    while(q.size()) {
        int u = q.front();
        q.pop();
        for(int nxt : g[u]) {
            in[nxt]--;
            cnt[nxt] += cnt[u];
            if(!in[nxt]) q.push(nxt);
        }
    }
}

void solve() {
  memset(cnt, 0, sizeof cnt);
  memset(in, 0, sizeof in);
    
  scanf("%s", s);
  n = strlen(s);
  
  scanf("%d", &m);
  for(int i = 0; i < m; i++) {
      scanf("%s", t);
      insert(i);
  }
  build();
  
  for(int i = 0, j = 0; i < n; i++) {
    int t = s[i] - 'a';
    j = tr[j][t];
    cnt[j]++;
  }
  topo();
  //for(int i = tail; i >= 0; i -- ) cnt[ne[q[i]]] += cnt[q[i]];
  for(int i = 0; i < m; i++) {
      printf("%lld\n", cnt[ids[i]]);
  }
  
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
